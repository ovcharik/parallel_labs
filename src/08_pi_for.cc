#include <iostream>
#include <cmath>
#include <omp.h>

int main() {
  long int n;
  long double sum = 0;

  std::cin >> n;

  #pragma omp parallel reduction(+:sum)
  {
    #pragma omp for
    for (int i = 0; i < n; i++) {
      long double x = (i + 0.5) / n;
      sum += 4 / (1 + std::pow(x, 2));
    }
  }

  std::cout << sum / n << std::endl;
  return 0;
}
