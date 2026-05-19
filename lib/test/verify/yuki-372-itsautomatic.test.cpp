#define PROBLEM "https://yukicoder.me/problems/no/372"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "dp/automaton/remainder.hpp"
#include <vector>

using mint = modint1000000007;

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  string S; cin >> S;
  vector<char> svec(S.begin(), S.end());

  int M; cin >> M;

  vector<char> alphabet = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

  RemainderAutomaton<char> ra(S.size(), M);


  mint ans = 0;
  vector<mint>dp1(M), dp2(M);


  for (int i = 0; i < (int) S.size(); i++) {
    if (S[i] == '0') ans += 1;
    else {
      dp2[(S[i] - '0') % M] += 1; // only one word substring, 'S[i]' .
    }
    for (int j = 0; j < M; j++) {

      dp2[j] += dp1[j]; // the case when S[i] is not choosed

      dp2[(j * 10 + S[i] - '0') % M] += dp1[j]; // the case when S[i] is choosen and added into past substrings

    }

    swap(dp1, dp2);
    dp2.assign(M, 0);
  }
  for(int i=0; i<M; i++) {
    if (ra.accept(i)) ans += dp1[i];
  }
  cout << ans.val() << endl;


  return 0;
}