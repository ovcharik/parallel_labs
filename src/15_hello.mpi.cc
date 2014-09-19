#include <iostream>
#include <sstream>
#include <mpi.h>

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::stringstream ss;
  ss << "I am " << rank << " process from " << size << " processes!" << std::endl;
  std::cout << ss.str();

  MPI_Finalize();
  return 0;
}
