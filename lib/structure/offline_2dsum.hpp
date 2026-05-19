#ifndef HARUILIB_STRUCTURE_OFFLINE_2DSUM_HPP
#define HARUILIB_STRUCTURE_OFFLINE_2DSUM_HPP

#include <algorithm>
#include <cassert>
#include <vector>
#include "structure/fenwick_tree.hpp"

template <class T, class W> struct offline_2dsum {
  struct Point {
    T x, y;
    W w;
  };
  struct Query {
    T l, r, d, u;
  };

  void add_point(T x, T y, W w) {
    points.push_back({x, y, w});
  }

  void add_query(T l, T r, T d, T u) {
    assert(l <= r && d <= u);
    queries.push_back({l, r, d, u});
  }

  std::vector<W> solve() {
    int n = points.size();
    int q = queries.size();
    std::vector<W> res(q, 0);

    std::vector<T> ys;
    ys.reserve(n);
    for (auto& p : points) ys.push_back(p.y);
    std::sort(ys.begin(), ys.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

    auto get_y = [&](T y) {
      return std::lower_bound(ys.begin(), ys.end(), y) - ys.begin();
    };

    struct Event {
      T x;
      int d, u;
      int id;
      int type; // -1 for l, 1 for r
      bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
      }
    };

    std::vector<Event> events;
    events.reserve(2 * q);
    for (int i = 0; i < q; i++) {
      assert(queries[i].l <= queries[i].r && queries[i].d <= queries[i].u);
      int d = get_y(queries[i].d);
      int u = get_y(queries[i].u);
      events.push_back({queries[i].l, d, u, i, -1});
      events.push_back({queries[i].r, d, u, i, 1});
    }

    std::sort(events.begin(), events.end());
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
      return a.x < b.x;
    });

    fenwick_tree<W> ft(ys.size());
    int pi = 0;
    for (auto& e : events) {
      while (pi < n && points[pi].x < e.x) {
        ft.add(get_y(points[pi].y), points[pi].w);
        pi++;
      }
      res[e.id] += (W)e.type * ft.sum(e.d, e.u);
    }

    return res;
  }

private:
  std::vector<Point> points;
  std::vector<Query> queries;
};

#endif // HARUILIB_STRUCTURE_OFFLINE_2DSUM_HPP
