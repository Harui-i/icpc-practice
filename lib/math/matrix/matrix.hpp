#ifndef HARUILIB_MATH_MATRIX_MATRIX_HPP
#define HARUILIB_MATH_MATRIX_MATRIX_HPP

#include <vector>

template <class T>
struct Matrix{
private: 
  std::vector<std::vector<T>>vec;
  int N, M;
public:

  Matrix(int _N, int _M) : vec(std::vector<std::vector<T>>(_N, std::vector<T>(_M))), N(_N), M(_M)  {
    assert(_N >= 0 && _M >= 0); // 0*0の行列を返したいときもある(逆行列なかったときとか)
  }

  Matrix<T> operator*(const Matrix<T>& rhs) const  {
    assert(M == rhs.N);
    Matrix ret(N,rhs.M);
    for (int i=0; i<N; i++) for (int k=0; k<M; k++) for(int j=0; j<rhs.M; j++) {
      ret.vec[i][j] += vec[i][k] * rhs.vec[k][j];
    } 

    return ret;
  }

  Matrix<T> operator^(unsigned long long k) const {
    assert(N == M);
    Matrix<T> ret(N, N);
    for(int i=0; i<N; i++) ret[i][i] = T(1);

    Matrix<T> base = *this;

    while (k > 0) {
      if (k & 1) {
        ret *= base;
      }

      base *= base;
      k >>= 1; 
    }

    return ret;
  }

  vector<T>& operator[](int i) {
    assert(i < N);
    return vec[i];
  }

  Matrix<T>& operator*=(const Matrix<T>& b) { return (*this) = (*this) * b; }
  Matrix<T>& operator^=(const unsigned long long k) { return (*this) = (*this) ^ k; }

  // さすがにrankを知るのに副作用があるのはヤバいので
  int rank() const {
    Matrix A = *this;
    return A.sweep(M);
  }

  // サイズを返す。N,Mをconstにしたいけどconstにすると*=や^=が面倒になるため、N,Mを非constのprivateにすることでなんとかする。
  pair<int,int> size() const {
    return make_pair(N, M);
  }

  // 逆行列を返す。なければ0*0行列を返す(これはGifted infantsのマネだが、0*0を返す嬉しさはいまいちわかっていない。変えるかも。)
  Matrix<T> inverse() const {
    assert(N == M);
    Matrix A(N, 2*N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) A[i][j] = vec[i][j];
    for(int i=0; i<N; i++) A[i][N+i] = T(1);
    int rank = A.sweep(N);
    if (rank < N) return Matrix(0,0);

    Matrix<T> ret(N, N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) ret[i][j] = A[i][N+j];

    return ret;
  }  

  // Solve Ax = b for H*W matrix A, longitudinal vector b, x.
  // x using {W-rank(A) + 1} vectors, x = x_0 + c_1 * x_1 + .... + c_{W-rank(A)} * x_{W-rank(A)} (c is an arbitrary constant), so x_0, x_1, ... , x_{W-rank(A)} is returned. 
  // if there is no solution, return an empty vector sequence.
  // ref : https://nyaannyaan.github.io/library/matrix/linear-equation.hpp
  std::vector<std::vector<T>> linear_equation() {
    int rk = sweep(M-1);
    int H = N;
    int W = M-1;

    for(int i=rk; i<N; i++) {
      if (vec[i][W] != T(0)) return std::vector<std::vector<T>>(); 
    }

    std::vector<std::vector<T>> ret(1, std::vector<T>(W));
    std::vector<int> pivot(W, -1);
    for (int i=0, j=0; i<rk; i++) {
      while (vec[i][j] == T(0)) {
        j++;
        assert(j < W);
      }

      ret[0][j] = vec[i][W];
      pivot[j] = i;
    }

    for(int j=0; j<W; j++) {
      if (pivot[j] == -1) {
        std::vector<T> x(W);
        x[j] = 1;
        for(int k=0; k<j; k++) {
          if (pivot[k] != -1) x[k] -= vec[pivot[k]][j];
        }

        ret.push_back(x);
      }
    }

    return ret;
  }

private:
// 0<= j < varなj列目について掃き出して、rankを返す

int sweep(int var) {
  assert(var <= M);
  int rank = 0;

  for(int col=0; col<var; col++) {
    int pivot = -1;
    for(int row=rank; row<N; row++) {
      // これがdoubleとかなら、
      // if ( && chmax(mx, asb(A[row][col])) ) みたいな条件を付けて、できるだけ絶対値の大きいpivotを選ぶようにする
      if (vec[row][col] != T(0)) {
        pivot = row;
        break; //double なら違う
      }
    }

    if (pivot == -1) continue;
    swap(vec[pivot], vec[rank]); // 行swapによってpivotが0,1,2,...,rank-1行目にあるようにする

    T inv = T(1) / vec[rank][col];
    // pivotの行の先頭が1になるように行を定数倍して揃える
    for(int col2=0; col2<M; col2++) {
      vec[rank][col2] *= inv;
    }

    for(int row=0; row<N; row++) {
      // doubleなら、 && A[row:[col] > EPSのときのみこの操作をする
      if (row != rank) {
        T fac = vec[row][col];
        for(int col2=0; col2<M; col2++) {
          vec[row][col2] -= vec[rank][col2] * fac;
        }
      }
    }
    rank++;
  }

  return rank;
}


};

#endif // HARUILIB_MATH_MATRIX_MATRIX_HPP