#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/4/ALDS1_4_B"
#include "template/template.hpp"
#include <vector>
#include <algorithm>

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n; cin >> n;
  vector<int> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  int q; cin >> q;
  int cnt = 0;
  while (q--) {
    int t_i; cin >> t_i;
    cnt += binary_search(s.begin(), s.end(), t_i);
  }
  cout << cnt << endl;
  return 0;
}
