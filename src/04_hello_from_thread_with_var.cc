#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>

int main() {
  int n, rank;
  std::cin >> n;
  omp_set_num_threads(n);

  #pragma omp parallel private(rank)
  {
    rank = omp_get_thread_num();
    std::stringstream ss;
    ss << "I am " << rank << " thread." << std::endl;
    std::cout << ss.str();
  }
  return 0;
}
