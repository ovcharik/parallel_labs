#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>

#define SECTION                                                             \
  _Pragma("omp section")                                                    \
  {                                                                         \
    std::stringstream ss;                                                   \
    ss << "[" << omp_get_thread_num() << "]: come in section" << std::endl; \
    std::cout << ss.str();                                                  \
  }


int main() {
  int n;
  std::cin >> n;
  omp_set_num_threads(n);

  #pragma omp parallel
  {
    #pragma omp sections
    {
      SECTION
      SECTION
      SECTION
    }
    std::stringstream ss;
    ss << "[" << omp_get_thread_num() << "]: parallel region" << std::endl;
    std::cout << ss.str();
  }
  return 0;
}
