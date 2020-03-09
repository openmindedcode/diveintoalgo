#include <iostream>
#include <vector>

int n, k, length[50];
double T[50][50];

class SquareMatrix {
 public:
  SquareMatrix(int n) : n_(n) {
    vec_.resize(n, std::vector<double>(n, 0));
  }
  std::vector<double>& operator[](int index) {
    return vec_[index];
  }
  SquareMatrix operator*(SquareMatrix &b) {
    SquareMatrix ret(n_);
    for (int i = 0; i < n_; ++i)
      for (int j = 0; j < n_; ++j)
        for (int k = 0; k < n_; ++k)
          ret.vec_[j][k] += vec_[j][i] * b.vec_[i][k];
    return ret;
  }
  SquareMatrix identity() {
    SquareMatrix ret(n_);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (i == j)
          ret[i][j] = 1;
    return ret;
  }
  SquareMatrix pow(int k) {
    if (k == 0)
      return identity();
    if (k % 2 == 1)
      return pow(k - 1) * (*this);
    SquareMatrix half = pow(k / 2);
    return half * half;
  }
 private:
  int n_;
  std::vector<std::vector<double>> vec_;
};

std::vector<double> getProb2() {
  SquareMatrix w(4 * n);

  for (int i = 0; i < 3 * n; ++i) {
    w[i][i + n] = 1.0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      w[3 * n + i][(4 - length[j]) * n + j] = T[j][i];
    }
  }
  SquareMatrix wk = w.pow(k);
  std::vector<double> ret(n);

  for (int song = 0; song < n; ++song) {
    for (int start = 0; start < length[song]; ++start) {
      ret[song] += wk[(3 - start) * n + song][3 * n];
    }
  }
  return ret;
}

int main() {
  n = 3, k = 6;
  length[0] = 4;
  length[1] = 4;
  length[2] = 2;
  T[0][0] = 0.18;
  T[0][1] = 0.40;
  T[0][2] = 0.42;
  T[1][0] = 0.15;
  T[1][1] = 0.46;
  T[1][2] = 0.39;
  T[2][0] = 0.58;
  T[2][1] = 0.23;
  T[2][2] = 0.19;

  std::vector<double> ret = getProb2();
  std::cout << ret[0] << " " << ret[3] << " " << ret[2] << std::endl;
  return 0;
}
