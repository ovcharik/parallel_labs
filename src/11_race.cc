#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

int main() {
  int num_of_threads;
  std::cin >> num_of_threads;
  omp_set_num_threads(num_of_threads);

  int n;
  int main_sum = 0;
  std::cin >> n;

  #pragma omp parallel
  {
    int sum = 0;

    #pragma omp for
    for (int i = 1; i <= n; i++) {
      sum += i;
    }

    int curr = omp_get_thread_num();
    std::stringstream ss;
    ss << "[" << curr << "]: Sum = " << sum << std::endl;
    std::cout << ss.str();

    #pragma omp atomic
    main_sum += sum;
  }

  std::cout << "Sum = " << main_sum << std::endl;
  return 0;
}
