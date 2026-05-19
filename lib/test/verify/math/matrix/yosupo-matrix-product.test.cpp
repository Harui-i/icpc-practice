#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "math/matrix/matrix.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, M, K; cin >> N >> M >> K;

  Matrix<mint> A(N, M);
  Matrix<mint> B(M, K);

  for(int i=0; i<N; i++) for(int j=0; j<M; j++) cin >> A[i][j];

  for(int i=0; i<M; i++) for(int j=0; j<K; j++) cin >> B[i][j];

  Matrix<mint> C = A * B; 
  for(int i=0; i<N; i++) {
    for(int j=0; j<K; j++) {
      cout << C[i][j].val();
      if (j == K-1) cout << endl;
      else cout << " ";
    }
  }

}
