#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <mpi.h>

#define ITERS 5
#define SIZES {100, 10000000/*, 4000000000*/}

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::cout.precision(6);
  std::cout << std::fixed;

  int  iters    = ITERS;
  long sizes[2] = SIZES;

  if (rank == 0)
    std::cout << "N\tTHR\tTIME\n";

  for (long n: sizes)
  {

    double Tk;

    double average = 0;
    for (int i = 0; i < iters; i++)
    {
      double start, end;

      start = MPI_Wtime();
      {
        double sum = 0;
        for (int i = rank; i < n; i += size) {
          long double x = (i + 0.5) / n;
          sum += 4 / (1 + std::pow(x, 2));
        }
        double pi;
        MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        pi = pi / n;
      }
      end = MPI_Wtime();
      average += end - start;
    }
    average /= iters;

    if (rank == 0)
      std::cout
        << n       << "\t"
        << size    << "\t"
        << average
        << std::endl;
  }

  MPI_Finalize();
  return 0;
}
