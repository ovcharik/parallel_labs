#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>

int main() {
  int n, sum = 0;
  std::cin >> n;

  int num_of_threads;
  std::cin >> num_of_threads;

  omp_set_num_threads(num_of_threads);

  int step = n / num_of_threads;

  #pragma omp parallel reduction(+:sum)
  {
    int curr = omp_get_thread_num();
    for (int i = step * curr; i <= step * (curr + 1); i++) {
      sum += i;
    }

    std::stringstream ss;
    ss << "[" << curr << "]: Sum = " << sum << std::endl;
    std::cout << ss.str();
  }

  std::cout << "Sum = " << sum << std::endl;
  return 0;
}
