#include <iostream>
#include <sstream>
#include <cmath>
#include <mpi.h>

#define CELL(i, j, n) i*n+j

template<typename T>
struct Matrix
{
  T* m_data;
  long m_n;

  Matrix(long n, bool r = false, long size = 0) : m_n(n)
  {
    if (size)
      this->m_data = new T[size];
    else
      this->m_data = new T[n*n];
    if (r) {
      for (int i = 0; i < n * n; i++) this->m_data[i] = rand() % 100;
    }
  }

  ~Matrix() {
    delete[] m_data;
  }

  T get(long i, long j) {
    return m_data[CELL(i, j, m_n)];
  }

  T* getBuffer() {
    return m_data;
  }

  T* getRow(long i) {
    return &m_data[i * m_n];
  }

  void set(long i, long j, T value) {
    m_data[CELL(i, j, m_n)] = value;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.m_n * mat.m_n; i++) {
      if (i && !(i % mat.m_n)) {
        os << std::endl;
      }
      os << mat.m_data[i] << "\t";
    }
    os << std::endl;
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Matrix& mat) {
    for (int i = 0; i < mat.m_n * mat.m_n; i++) {
      is >> mat.m_data[i];
    }
    return is;
  }
};

int main(int argc, char ** argv) {
  int result = 0;

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int n;
  if (rank == 0) std::cin >> n;
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int count = (n % size == 0) ? n / size * n : (n / size + 1) * n;
  int rows  = count / n;

  Matrix<int> Ai(n, false, size * count);
  Matrix<int> Co(n, false, size * count);
  Matrix<int> A(n, false, size * count);
  Matrix<int> B(n, false, size * count);
  Matrix<int> C(n, false, size * count);
  if (rank == 0) std::cin >> Ai >> B;

  MPI_Bcast(B.getBuffer(), n * n, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(Ai.getBuffer(), count, MPI_INT, A.getRow(rank * rows), count, MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = rows * rank; i < rows * (rank + 1) && i < n; i++)
  for (int j = 0; j < n; j++) {
    int sum = 0;
    for (int k = 0; k < n; k++) {
      sum += A.get(i, k) * B.get(k, j);
    }
    C.set(i, j, sum);
  }

  MPI_Gather(C.getRow(rank * rows), count, MPI_INT, Co.getBuffer(), count, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0) std::cout << Co;

  MPI_Finalize();
  return result;
}
