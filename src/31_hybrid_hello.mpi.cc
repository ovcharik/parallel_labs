#include <iostream>
#include <sstream>
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

  omp_set_num_threads(n);

  #pragma omp parallel
  {
    int curr = omp_get_thread_num();
    std::stringstream ss;
    ss << "I am " << curr << " thread from " << rank << " process. Number of hybrid threads = " << n * size << std::endl;
    std::cout << ss.str();
  }

  MPI_Finalize();
  return 0;
}
