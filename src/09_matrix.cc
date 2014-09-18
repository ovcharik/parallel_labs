#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

typedef std::vector< std::vector<int> > Matrix;

void init_matrix(int n, Matrix &matrix) {
  for (int i = 0; i < n; i++) matrix.push_back(std::vector<int>(n));
}

void read_matrix(int n, Matrix &matrix) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];
    }
  }
}

void write_matrix(Matrix &matrix) {
  for (auto row: matrix) {
    for (auto a: row) {
      std::cout << a << "\t";
    }
    std::cout << std::endl;
  }
}

int main() {
  int n;
  std::cin >> n;

  Matrix A, B, C;

  init_matrix(n, A);
  init_matrix(n, B);
  init_matrix(n, C);

  read_matrix(n, A);
  read_matrix(n, B);

  #pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  write_matrix(C);

  return 0;
}
