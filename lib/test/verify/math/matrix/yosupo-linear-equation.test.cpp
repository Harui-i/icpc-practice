#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "template/template.hpp"
#include "math/matrix/matrix.hpp"
#include "math/modint.hpp"
using mint = modint998244353;

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, M; cin >> N >> M;

  Matrix<mint> A(N,M+1); for(int i=0; i<N; i++) for(int j=0; j<M; j++) cin >> A[i][j];

  for(int i=0; i<N; i++) cin >> A[i][M];

  vector<vector<mint>> ans = A.linear_equation();

  if (ans.size() == 0) {
    cout << -1 << endl;
    return 0;
  }
  else {
    cout << ans.size() - 1 << endl;
    for (vector<mint>& vec : ans) {
      for(int i=0; i<(int)vec.size(); i++) {
        cout << vec[i].val() << " \n"[i == (int)vec.size() - 1];
      }
    }
  }
  return 0;
}
