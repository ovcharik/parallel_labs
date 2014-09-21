#include <iostream>
#include <cmath>
#include <mpi.h>

int main(int argc, char ** argv) {
  int result = 0;

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long int n;
  if (rank == 0) std::cin >> n;
  MPI_Bcast(&n, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);

  long int
    start = n / size * rank,
    end   = n / size * (rank + 1);
  if (rank == size - 1) end = n + 1;

  double sum = 0;
  for (int i = start; i < end; i++) {
    long double x = (i + 0.5) / n;
    sum += 4 / (1 + std::pow(x, 2));
  }

  double pi;
  MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0)
    std::cout << pi / n << std::endl;

  MPI_Finalize();
  return result;
}
