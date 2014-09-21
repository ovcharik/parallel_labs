#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <mpi.h>

int main(int argc, char ** argv) {
  int result = 0;

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int az = 'z' - 'a';
  int start = 'a' + az / size * rank;
  int end   = 'a' + az / size * (rank + 1);
  if (rank == size - 1) end = 'a' + az;

  char* buff;
  int length;

  if (rank == 0) {
    std::string str;
    std::cin >> str;

    length = str.length();
    buff   = &str[0];
  }
  MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0) buff = new char[length];
  MPI_Bcast(buff, length, MPI_CHAR, 0, MPI_COMM_WORLD);

  std::map<char, int> counter;
  for (int i = 0; i < length; i++) {
    if (start <= buff[i] && buff[i] < end) {
      counter[buff[i]]++;
    }
  }

  if (rank != 0) delete[] buff;

  for (auto c: counter) {
    std::stringstream ss;
    ss << "[" << rank << "]: " << c.first << " = " << c.second << std::endl;
    std::cout << ss.str();
  }

  MPI_Finalize();
  return result;
}
