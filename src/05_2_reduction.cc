#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

int main() {
  int num_of_threads;
  std::cin >> num_of_threads;
  omp_set_num_threads(num_of_threads);

  int n, sum = 0;
  std::cin >> n;

  float step = n / num_of_threads;

  #pragma omp parallel reduction(+:sum)
  {
    int curr  = omp_get_thread_num();
    int start = std::round(step * curr);
    int end   = std::round(start + step);
    if (curr == num_of_threads - 1) end = n;
    for (int i = start + 1; i <= end; i++) {
      sum += i;
    }

    std::stringstream ss;
    ss << "[" << curr << "]: Sum = " << sum << std::endl;
    std::cout << ss.str();
  }

  std::cout << "Sum = " << sum << std::endl;
  return 0;
}
