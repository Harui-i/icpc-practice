#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "math/matrix/matrix.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N; cin >> N;
  ll K; cin >> K;

  Matrix<mint>A(N,N);

  for(int i=0; i<N; i++) for(int j=0; j<N; j++) cin >> A[i][j];

  A ^= K;
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      cout << A[i][j].val();
      if (j == N-1) cout << endl;
      else cout << " ";
    }
  }
}
