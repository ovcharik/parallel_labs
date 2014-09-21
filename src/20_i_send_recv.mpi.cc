#include <iostream>
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
  MPI_Request request;

  if (rank == 0) {
    secret = 45;
    MPI_Isend(&secret, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
  }
  else if (rank == 1) {
    MPI_Irecv(&secret, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
    std::cout << "receive message '" << secret << "'" << std::endl;
  }

  MPI_Finalize();
  return result;
}
