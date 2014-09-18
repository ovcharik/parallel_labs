#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>

int main() {
  int n, sum = 0;
  std::cin >> n;

  int num_of_threads = 2;
  omp_set_num_threads(num_of_threads);

  int step = n / num_of_threads;

  #pragma omp parallel reduction(+:sum)
  {
    int curr = omp_get_thread_num();
    int start = step * curr;
    int end = start + step;
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
