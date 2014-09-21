#include <iostream>
#include <sstream>
#include <vector>
#include <mpi.h>

int main(int argc, char ** argv) {
  int result = 0;

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int count = (size - 1) * 2;
  int* secrets = new int[size];
  MPI_Status* statuses = new MPI_Status[count];
  MPI_Request* requests = new MPI_Request[count];

  for (int i = 0, j = 0; i < size; i++) {
    if (i == rank) continue;

    int s = size * rank + i;
    int r = size * i + rank;

    MPI_Isend(&rank,         1, MPI_INT, i, s, MPI_COMM_WORLD, &requests[j++]);
    MPI_Irecv(&(secrets[i]), 1, MPI_INT, i, r, MPI_COMM_WORLD, &requests[j++]);
  }
  MPI_Waitall(count, requests, statuses);

  for (int i = 0; i < size; i++) {
    if (i == rank) continue;

    std::stringstream ss;
    ss << "[" << rank << "] receive message '" << secrets[i] << "'" << std::endl;
    std::cout << ss.str();
  }

  delete[] secrets;
  delete[] statuses;
  delete[] requests;

  MPI_Finalize();
  return result;
}
