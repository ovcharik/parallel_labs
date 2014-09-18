#include <iostream>
#include <omp.h>

int main() {
  omp_set_num_threads(4);

  #pragma omp parallel
  {
    std::cout << "Hello, world!\n";
  }
  return 0;
}
