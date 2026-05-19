#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "structure/slide-window-aggregation.hpp"
#include "math/linear_function.hpp"

using mint = modint998244353;
using LF = LinearFunction<mint>;


// f_r(f_l)
LF op(LF lf, LF rf) {
  return rf.composite(lf);
}

LF e() {
  return LF::Mul_Identity();
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  FoldableDeque<LF,op,e> fdq;

  int Q; cin >> Q;

  for(int i=0; i<Q; i++) {
    int op; cin >> op;
    if (op == 0) {
      int a,b; cin >> a >> b;
      fdq.push_front(LF(mint(a), mint(b)));
    }

    else if (op == 1) {
      int a, b; cin >> a >> b;
      fdq.push_back(LF(mint(a), mint(b)));
    }
    else if (op == 2) {
      fdq.pop_front();
    }
    else if (op == 3) {
      fdq.pop_back();
    }
    else if (op == 4) {
      int x; cin >> x;
      LF all_prod = fdq.all_prod();
      cout << all_prod(x).val() << endl;
    }
  }
  return 0;
}