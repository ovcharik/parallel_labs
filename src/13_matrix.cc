#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define ITERS   5
#define SIZES   {100, 1000}
#define THREADS {1, 2, 4, 6, 8, 10, 12}

#define CELL(i, j, n) i*n+j

template<typename T>
struct Matrix
{
  T* m_data;
  long m_n;

  Matrix(long n, bool r = false) : m_n(n)
  {
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

int main() {
  srand(time(NULL));
  std::cout.precision(6);
  std::cout << std::fixed;

  int  iters      = ITERS;
  long sizes[2]   = SIZES;
  long threads[7] = THREADS;

  for (long size: sizes)
  {
    std::cout << "N\tTHR\tTIME    \tACC\n";
    double Tk;
    int max_threads = 1;
    double max_acc  = 0;

    for (long thread: threads)
    {
      omp_set_num_threads(thread);

      double average = 0;
      double acc = 0;
      for (int i = 0; i < iters; i++)
      {
        double start, end;

        Matrix<char> A(size, true);
        Matrix<char> B(size, true);
        Matrix<char> C(size, false);

        start = omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
          int sum = 0;
          for (int k = 0; k < size; k++) {
            sum += A.get(i, k) * B.get(k, j);
          }
          C.set(i, j, sum);
        }
        end = omp_get_wtime();
        average += end - start;
      }
      average /= iters;
      if (thread == 1) Tk = average;
      acc = Tk / average;

      std::cout
        << size    << "\t"
        << thread  << "\t"
        << average << "\t"
        << acc
        << std::endl;

      if (max_acc < acc) { max_acc = acc; max_threads = thread; }
    }
    std::cout << "Max acceleration " << max_acc << " with " << max_threads << " threads." << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
