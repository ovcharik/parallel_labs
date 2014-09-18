#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>

int main() {
  int n;
  std::cin >> n;
  omp_set_num_threads(n);

  #pragma omp parallel
  {
    int curr = omp_get_thread_num();
    if (!(curr % 2)) {
      std::stringstream ss;
      ss << "I am " << curr << " thread from " << n << " threads!" << std::endl;
      std::cout << ss.str();
    }
  }
  return 0;
}
