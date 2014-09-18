#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <omp.h>

#define TOSTR(...) #__VA_ARGS__
#define OMP_FOR(...) _Pragma(TOSTR( omp for schedule(__VA_ARGS__) ))

#define LOOP(...)                                   \
  for (int i = 1; i <= n; i++)                      \
  {                                                 \
    sum += i;                                       \
    table_mutex.lock();                             \
    table[TOSTR(__VA_ARGS__)][i - 1] = curr;        \
    table_mutex.unlock();                           \
  }

#define REDUC(type, chunk)                          \
  sum = 0;                                          \
  table[TOSTR(type,chunk)] = std::vector<int>(n);   \
  _Pragma("omp parallel reduction(+:sum)")          \
  {                                                 \
    int curr = omp_get_thread_num();                \
    if (chunk) {                                    \
      OMP_FOR(type,chunk)                           \
      LOOP(type,chunk)                              \
    }                                               \
    else {                                          \
      OMP_FOR(type)                                 \
      LOOP(type,chunk)                              \
    }                                               \
  }

typedef std::map<std::string, std::vector<int> > Table;

int main() {
  Table table;
  std::mutex table_mutex;

  int n, number_of_threads;
  int sum = 0;

  std::cin >> number_of_threads;
  std::cin >> n;

  omp_set_num_threads(number_of_threads);

  REDUC(static,  NULL)
  REDUC(static,  1)
  REDUC(static,  2)
  REDUC(dynamic, NULL)
  REDUC(dynamic, 2)
  REDUC(guided,  NULL)
  REDUC(guided,  2)

  for (auto &pair: table) {
    std::cout << pair.first << "\t";
    for (auto i: pair.second) {
      std::cout << i << "\t";
    }
    std::cout << std::endl;
  }

  return 0;
}
