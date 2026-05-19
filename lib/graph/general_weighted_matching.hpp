#ifndef HARUILIB_GRAPH_GENERAL_WEIGHTED_MATCHING_HPP
#define HARUILIB_GRAPH_GENERAL_WEIGHTED_MATCHING_HPP

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

namespace mylib {

struct GeneralWeightedMatching {
  int n;
  std::vector<std::vector<long long>> w;

  explicit GeneralWeightedMatching(int n_) : n(n_), w(n_, std::vector<long long>(n_, 0)) {}

  void add_edge(int u, int v, long long cost) {
    if (u == v) return;
    if (w[u][v] < cost) w[u][v] = w[v][u] = cost;
  }

  std::pair<long long, std::vector<int>> solve() const {
    if (n == 0) return {0, {}};

    struct Edge {
      int u, v;
      long long w;
      Edge(int u_ = 0, int v_ = 0, long long w_ = 0) : u(u_), v(v_), w(w_) {}
    };

    const int N = n;
    const int max_nodes = 2 * N;
    int nodes = N;

    std::vector<std::vector<Edge>> g(max_nodes + 1, std::vector<Edge>(max_nodes + 1));
    for (int i = 1; i <= max_nodes; i++) {
      for (int j = 1; j <= max_nodes; j++) {
        g[i][j] = Edge(i, j, 0);
      }
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        g[i][j].w = w[i - 1][j - 1];
      }
    }

    std::vector<int> match(max_nodes + 1), slack(max_nodes + 1), st(max_nodes + 1), parent(max_nodes + 1);
    std::vector<int> state(max_nodes + 1), vis(max_nodes + 1);
    std::vector<long long> label(max_nodes + 1);
    std::vector<std::vector<int>> blossom_from(max_nodes + 1, std::vector<int>(N + 1));
    std::vector<std::vector<int>> blossom(max_nodes + 1);
    std::queue<int> q;
    int vis_timer = 0;

    auto delta = [&](const Edge &e) {
      return label[e.u] + label[e.v] - e.w * 2;
    };

    auto update_slack = [&](int u, int x) {
      if (!slack[x] || delta(g[u][x]) < delta(g[slack[x]][x])) {
        slack[x] = u;
      }
    };

    auto set_slack = [&](int x) {
      slack[x] = 0;
      for (int u = 1; u <= N; u++) {
        if (g[u][x].w > 0 && st[u] != x && state[st[u]] == 0) update_slack(u, x);
      }
    };

    std::function<void(int)> q_push = [&](int x) {
      if (x <= N) {
        q.push(x);
      } else {
        for (int v : blossom[x]) q_push(v);
      }
    };

    std::function<void(int, int)> set_st = [&](int x, int b) {
      st[x] = b;
      if (x > N) {
        for (int v : blossom[x]) set_st(v, b);
      }
    };

    auto get_pr = [&](int b, int xr) {
      int pr = std::find(blossom[b].begin(), blossom[b].end(), xr) - blossom[b].begin();
      if (pr % 2 == 1) {
        std::reverse(blossom[b].begin() + 1, blossom[b].end());
        return (int)blossom[b].size() - pr;
      }
      return pr;
    };

    std::function<void(int, int)> set_match = [&](int u, int v) {
      match[u] = g[u][v].v;
      if (u <= N) return;
      int xr = blossom_from[u][g[u][v].u];
      int pr = get_pr(u, xr);
      for (int i = 0; i < pr; i++) {
        set_match(blossom[u][i], blossom[u][i ^ 1]);
      }
      set_match(xr, v);
      std::rotate(blossom[u].begin(), blossom[u].begin() + pr, blossom[u].end());
    };

    auto augment = [&](int u, int v) {
      while (true) {
        int next = st[match[u]];
        set_match(u, v);
        if (!next) return;
        set_match(next, st[parent[next]]);
        u = st[parent[next]];
        v = next;
      }
    };

    auto lca = [&](int u, int v) {
      ++vis_timer;
      for (; u || v; std::swap(u, v)) {
        if (!u) continue;
        if (vis[u] == vis_timer) return u;
        vis[u] = vis_timer;
        u = st[match[u]];
        if (u) u = st[parent[u]];
      }
      return 0;
    };

    auto add_blossom = [&](int u, int l, int v) {
      int b = N + 1;
      while (b <= nodes && st[b]) b++;
      if (b > nodes) nodes++;

      label[b] = 0;
      state[b] = 0;
      match[b] = match[l];
      blossom[b].clear();
      blossom[b].push_back(l);
      for (int x = u, y; x != l; x = st[parent[y]]) {
        blossom[b].push_back(x);
        y = st[match[x]];
        blossom[b].push_back(y);
        q_push(y);
      }
      std::reverse(blossom[b].begin() + 1, blossom[b].end());
      for (int x = v, y; x != l; x = st[parent[y]]) {
        blossom[b].push_back(x);
        y = st[match[x]];
        blossom[b].push_back(y);
        q_push(y);
      }
      set_st(b, b);

      for (int x = 1; x <= nodes; x++) {
        g[b][x] = Edge(b, x, 0);
        g[x][b] = Edge(x, b, 0);
      }
      for (int x = 1; x <= N; x++) blossom_from[b][x] = 0;

      for (int x : blossom[b]) {
        for (int y = 1; y <= nodes; y++) {
          if (g[b][y].w == 0 || delta(g[x][y]) < delta(g[b][y])) {
            g[b][y] = g[x][y];
            g[y][b] = g[y][x];
          }
        }
        for (int y = 1; y <= N; y++) {
          if (blossom_from[x][y]) blossom_from[b][y] = x;
        }
      }
      set_slack(b);
    };

    auto expand_blossom = [&](int b) {
      for (int x : blossom[b]) set_st(x, x);
      int xr = blossom_from[b][g[b][parent[b]].u];
      int pr = get_pr(b, xr);
      for (int i = 0; i < pr; i += 2) {
        int xs = blossom[b][i], xns = blossom[b][i + 1];
        parent[xs] = g[xns][xs].u;
        state[xs] = 1;
        state[xns] = 0;
        slack[xs] = 0;
        set_slack(xns);
        q_push(xns);
      }
      state[xr] = 1;
      parent[xr] = parent[b];
      for (int i = pr + 1; i < (int)blossom[b].size(); i++) {
        int x = blossom[b][i];
        state[x] = -1;
        set_slack(x);
      }
      st[b] = 0;
    };

    auto on_found_edge = [&](const Edge &e) {
      int u = st[e.u], v = st[e.v];
      if (state[v] == -1) {
        parent[v] = e.u;
        state[v] = 1;
        int next = st[match[v]];
        slack[v] = slack[next] = 0;
        state[next] = 0;
        q_push(next);
      } else if (state[v] == 0) {
        int l = lca(u, v);
        if (!l) {
          augment(u, v);
          augment(v, u);
          return true;
        }
        add_blossom(u, l, v);
      }
      return false;
    };

    auto matching = [&]() {
      std::fill(state.begin(), state.end(), -1);
      std::fill(slack.begin(), slack.end(), 0);
      q = std::queue<int>();
      for (int x = 1; x <= nodes; x++) {
        if (st[x] == x && !match[x]) {
          parent[x] = 0;
          state[x] = 0;
          q_push(x);
        }
      }
      if (q.empty()) return false;

      while (true) {
        while (!q.empty()) {
          int u = q.front();
          q.pop();
          if (state[st[u]] == 1) continue;
          for (int v = 1; v <= N; v++) {
            if (g[u][v].w > 0 && st[u] != st[v]) {
              if (delta(g[u][v]) == 0) {
                if (on_found_edge(g[u][v])) return true;
              } else {
                update_slack(u, st[v]);
              }
            }
          }
        }

        long long d = std::numeric_limits<long long>::max();
        for (int u = 1; u <= N; u++) {
          if (state[st[u]] == 0) d = std::min(d, label[u]);
        }
        for (int b = N + 1; b <= nodes; b++) {
          if (st[b] == b && state[b] == 1) d = std::min(d, label[b] / 2);
        }
        for (int x = 1; x <= nodes; x++) {
          if (st[x] == x && slack[x]) {
            if (state[x] == -1) d = std::min(d, delta(g[slack[x]][x]));
            else if (state[x] == 0) d = std::min(d, delta(g[slack[x]][x]) / 2);
          }
        }
        if (d == std::numeric_limits<long long>::max()) return false;

        for (int u = 1; u <= N; u++) {
          if (state[st[u]] == 0) {
            if (label[u] == d) return false;
            label[u] -= d;
          } else if (state[st[u]] == 1) {
            label[u] += d;
          }
        }
        for (int b = N + 1; b <= nodes; b++) {
          if (st[b] == b) {
            if (state[b] == 0) label[b] += d * 2;
            else if (state[b] == 1) label[b] -= d * 2;
          }
        }

        q = std::queue<int>();
        for (int x = 1; x <= nodes; x++) {
          if (st[x] == x && slack[x] && st[slack[x]] != x && delta(g[slack[x]][x]) == 0) {
            if (on_found_edge(g[slack[x]][x])) return true;
          }
        }
        for (int b = N + 1; b <= nodes; b++) {
          if (st[b] == b && state[b] == 1 && label[b] == 0) expand_blossom(b);
        }
      }
    };

    long long max_weight = 0;
    for (int u = 1; u <= N; u++) {
      st[u] = u;
      blossom[u].clear();
      for (int v = 1; v <= N; v++) {
        blossom_from[u][v] = (u == v ? u : 0);
        max_weight = std::max(max_weight, g[u][v].w);
      }
    }
    for (int u = 1; u <= N; u++) label[u] = max_weight;

    while (matching()) {}

    std::vector<int> mate(n, -1);
    long long total = 0;
    for (int i = 1; i <= N; i++) {
      if (match[i] && match[i] <= N) mate[i - 1] = match[i] - 1;
    }
    for (int i = 0; i < n; i++) {
      if (mate[i] > i) total += w[i][mate[i]];
    }
    return {total, mate};
  }
};

} // namespace mylib

#endif
