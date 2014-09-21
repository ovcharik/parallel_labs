#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <mpi.h>

int main(int argc, char ** argv) {
  int result = 0;
  int rank, size;
  int newrank = -1, newsize = -1;

  int length;
  char* buff = NULL;

  std::vector<int> ranks;
  std::string message;

  MPI_Group oldgroup, group;
  MPI_Comm  newcomm;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  for (int i = 0; i < size; i += 2) ranks.push_back(i);

  MPI_Comm_group(MPI_COMM_WORLD, &oldgroup);
  MPI_Group_incl(oldgroup, ranks.size(), &ranks[0], &group);
  MPI_Comm_create(MPI_COMM_WORLD, group, &newcomm);

  if (newcomm != MPI_COMM_NULL) {
    MPI_Comm_rank(newcomm, &newrank);
    MPI_Comm_size(newcomm, &newsize);

    if (newrank == 0) {
      std::cin >> message;
      length = message.length();
      buff = &message[0];
    }
    MPI_Bcast(&length, 1, MPI_INT, 0, newcomm);
    if (newrank != 0) buff = new char[length + 1];
    MPI_Bcast(buff, length, MPI_CHAR, 0, newcomm);
    if (newrank != 0) buff[length] = 0;
  }

  std::string msg = (newrank >= 0) ? buff : "no";
  std::string nr  = (newrank >= 0) ? std::to_string(newrank) : "no";
  std::string ns  = (newrank >= 0) ? std::to_string(newsize) : "no";
  std::stringstream ss;
  ss << "MPI_COMM_WORLD: " << rank << " from " << size << ". New comm: " << nr << " from " << ns << ". Message = " << msg << std::endl;
  std::cout << ss.str();

  if (newrank > 0) delete[] buff;
  MPI_Group_free(&group);
  MPI_Group_free(&oldgroup);
  if (newcomm != MPI_COMM_NULL) MPI_Comm_free(&newcomm);

  MPI_Finalize();
  return result;
}
