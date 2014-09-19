#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <omp.h>

#define ITERS   5
#define SIZES   {100, 10000000/*, 4000000000*/}
#define THREADS {1, 2, 4, 6, 8, 10, 12}

int main() {
  srand(time(NULL));
  std::cout.precision(6);
  std::cout << std::fixed;

  int  iters      = ITERS;
  long sizes[2]   = SIZES;
  long threads[7] = THREADS;

  for (long size: sizes)
  {
    std::cout << "N\tTHR\tTIME    \tACC\n";
    double Tk;
    int max_threads = 1;
    double max_acc  = 0;

    for (long thread: threads)
    {
      omp_set_num_threads(thread);

      double average = 0;
      double acc = 0;
      for (int i = 0; i < iters; i++)
      {
        double start, end;
        double sum = 0;
        start = omp_get_wtime();
        #pragma omp parallel reduction(+:sum)
        {
          #pragma omp for
          for (int i = 0; i < size; i++) {
            long double x = (i + 0.5) / size;
            sum += 4 / (1 + std::pow(x, 2));
          }
        }
        double pi = sum / size;
        end = omp_get_wtime();
        average += end - start;
      }
      average /= iters;
      if (thread == 1) Tk = average;
      acc = Tk / average;

      std::cout
        << size    << "\t"
        << thread  << "\t"
        << average << "\t"
        << acc
        << std::endl;

      if (max_acc < acc) { max_acc = acc; max_threads = thread; }
    }
    std::cout << "Max acceleration " << max_acc << " with " << max_threads << " threads." << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
