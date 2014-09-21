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

  int secret;
  MPI_Status status;
  int s = (rank + 1) % size;
  int r = (rank ? rank : size) - 1;

  MPI_Send(&rank,   1, MPI_INT, s, rank, MPI_COMM_WORLD);
  MPI_Recv(&secret, 1, MPI_INT, r, r,    MPI_COMM_WORLD, &status);

  std::stringstream ss;
  ss << "[" << rank << "] receive message '" << secret << "'" << std::endl;
  std::cout << ss.str();

  MPI_Finalize();
  return result;
}
