#include <iostream>
#include <cmath>
#include <mpi.h>
#include <omp.h>

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int n;
  if (rank == 0) std::cin >> n;
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  long double sum = 0;
  #pragma omp parallel reduction(+:sum)
  {
    #pragma omp for
    for (int i = rank; i < n; i += size) {
      long double x = (i + 0.5) / n;
      sum += 4 / (1 + std::pow(x, 2));
    }
  }

  long double pi;
  MPI_Reduce(&sum, &pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0)
    std::cout << pi / n << std::endl;

  MPI_Finalize();
  return 0;
}
