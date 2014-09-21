#include <iostream>
#include <mpi.h>

int main(int argc, char ** argv) {
  int result = 0;

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Status status;
  int secret;

  if (rank == 0) {
    for (int i = 0; i < size - 1; i++) {
      MPI_Recv(&secret, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      std::cout << "receive message '" << secret << "'" << std::endl;
    }
  }
  else {
    MPI_Send(&rank, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return result;
}
