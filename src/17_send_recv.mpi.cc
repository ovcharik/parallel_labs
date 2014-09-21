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

  if (rank == 0) {
    int secret = 45;
    MPI_Send(&secret, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
  }
  else if (rank == 1) {
    int secret;
    MPI_Status status;
    int r = MPI_Recv(&secret, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    switch (r) {
      case MPI_SUCCESS: {
        std::stringstream ss;
        ss << "receive message '" << secret << "'" << std::endl;
        std::cout << ss.str();
        break;
      }
      default: {
        result = 1;
      }
    }
  }

  MPI_Finalize();
  return result;
}
