#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"
#include "template/template.hpp"
#include "structure/rectangle_apply_point_get.hpp"

#include <algorithm>
#include <vector>

ll composition(ll f, ll g) {
  return f + g;
}

ll id() {
  return 0;
}

struct Rect {
  int l, d, r, u;
  ll w;
};

struct Query {
  int type;
  Rect rect;
  int x, y;
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int N, Q; cin >> N >> Q;
  vector<Rect> rects(N);
  for (int i=0; i<N; i++) {
    cin >> rects[i].l >> rects[i].d >> rects[i].r >> rects[i].u >> rects[i].w;
  }

  vector<Query> qs(Q);
  vector<int> xs, ys;
  for (int q=0; q<Q; q++) {
    cin >> qs[q].type;
    if (qs[q].type == 0) {
      cin >> qs[q].rect.l >> qs[q].rect.d >> qs[q].rect.r >> qs[q].rect.u >> qs[q].rect.w;
    }
    else {
      cin >> qs[q].x >> qs[q].y;
      xs.push_back(qs[q].x);
      ys.push_back(qs[q].y);
    }
  }

  if (xs.empty()) return 0;

  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  auto get_x = [&](int x) {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  };
  auto get_y = [&](int y) {
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
  };
  auto apply = [&](rectangle_apply_point_get<ll, composition, id>& g, const Rect& rect) {
    int l = get_x(rect.l);
    int r = get_x(rect.r);
    int d = get_y(rect.d);
    int u = get_y(rect.u);
    g.apply(l, r, d, u, rect.w);
  };

  rectangle_apply_point_get<ll, composition, id> g(0, (int)xs.size(), 0, (int)ys.size());
  for (auto& rect : rects) apply(g, rect);

  for (auto& q : qs) {
    if (q.type == 0) {
      apply(g, q.rect);
    }
    else {
      cout << g.get(get_x(q.x), get_y(q.y)) << "\n";
    }
  }

  return 0;
}
