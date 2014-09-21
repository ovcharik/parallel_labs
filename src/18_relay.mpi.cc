#include <iostream>
#include <sstream>
#include <mpi.h>

int main(int argc, char ** argv) {
  int result = 0;

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int secret = 0;
  MPI_Status status;
  int p = (rank + 1) % size;

  if (rank == 0) {
    MPI_Send(&secret, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    MPI_Recv(&secret, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
  }
  else {
    MPI_Recv(&secret, 1, MPI_INT, rank - 1, rank, MPI_COMM_WORLD, &status);
    secret++;
    MPI_Send(&secret, 1, MPI_INT, p, p, MPI_COMM_WORLD);
    secret--;
  }

  std::stringstream ss;
  ss << "[" << rank << "] receive message '" << secret << "'" << std::endl;
  std::cout << ss.str();

  MPI_Finalize();
  return result;
}
