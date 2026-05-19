#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "template/template.hpp"
#include <vector>

vector<ll> dat;
int sz;

// k番目(0-indexed)の値にaを加算
void update(int k, int a) {
  k += sz;
  dat[k] += a;
  while (k > 0) {
    k /= 2;
    dat[k] = dat[k * 2] + dat[k * 2 + 1];
  }
}

// [l, r)の和を求める(l, rは0-indexed)
ll query(int l, int r) {

  l += sz; r += sz;
  assert(0<=l && 0<= r && l <= r);
  int L = 0, R = 0;
  while (l < r) {
    if (l % 2 == 1) {
      L = L + dat[l];
      l++;
    }

    if (r % 2 == 1) {
      r--;
      R = dat[r] + R;
    }

    l /= 2; r /= 2;
  }
  return L + R;
}


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, q; cin >> n >> q;

  sz = 1; while (sz < n) sz *= 2;

  dat.resize(sz * 2, 0);

  while (q--) {
    int com, x, y; cin >> com >> x >> y;
    x--;
    if (com == 0) {
      update(x, y);
    }
    else {
      cout << query(x, y) << endl;
    }
  }
  return 0;
}