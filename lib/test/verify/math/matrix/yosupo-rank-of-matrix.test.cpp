#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "math/matrix/matrix.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, M; cin >> N >> M;
  if(N == 0 || M == 0) {
    cout << 0 << endl;
    return 0;
  }

  Matrix<mint>A(N,M);

  for(int i=0; i<N; i++) for(int j=0; j<M; j++) cin >> A[i][j];
  cout << A.rank() << endl;
}
