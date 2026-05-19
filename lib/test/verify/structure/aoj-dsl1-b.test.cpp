#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B"

#include "template/template.hpp"
#include "structure/potentialized-union-find-tree.hpp"

ll op(ll a, ll b) {
  return a + b;
}

ll invop(ll a, ll b) {
  return a - b;
}

ll e() {
  return 0LL;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, q; cin >> n >> q;

  PotentializedUnionFindTree<ll,op,invop,e> puf(n);
  for(int i=0; i<q; i++) {
    int t; cin >> t;
    int x, y; cin >> x >> y;
    if (t == 0) {
      ll z; cin >> z;
      puf.merge(x,y,-z);
    }
    else if (t == 1) {
      if (puf.same(x,y)) {
        ll diff = puf.diff(y,x);
        cout << diff << endl; 
      }
      else cout << "?" <<  endl;
    }
  }
  return 0;
}
