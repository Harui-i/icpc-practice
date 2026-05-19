#ifndef HARUILIB_GRAPH_DIAMETER_HPP
#define HARUILIB_GRAPH_DIAMETER_HPP


#include <algorithm>
#include <vector>
#include <queue>
#include "graph/graph_template.hpp"

namespace mylib {

  using std::vector;
  using std::pair;
  using std::queue;

  template <typename T>
  pair<vector<int>, T> diameter_path(const Graph<T>& graph) {
    int N = (int)graph.size();

    // first sweep
    pair<T, int> farest1 = make_pair(T(0), 0);
    {
      vector<T> dist(N, T(-1));
      dist[0] = T(0);

      queue<int> que;
      que.push(0);
      while (!que.empty()) {
        int front = que.front(); que.pop();

        for (Edge e: graph[front]) {
          if (dist[e.to] == T(-1)) {
            dist[e.to] = dist[front] + e.cost;
            que.push(e.to);
            if (farest1.first == -1 || farest1.first < dist[e.to]) {
              farest1 = make_pair(dist[e.to], e.to);
            }
          }
        }
      }
    }


    pair<T, int> farest2 = make_pair(T(0), farest1.second);
    // second sweep
    vector<int> prev(N, -1);
    {
      int start = farest1.second;
      vector<T> dist(N, T(-1));
      dist[start] = T(0);

      queue<int> que;
      que.push(start);

      while (!que.empty()) {
        int front = que.front(); que.pop();

        for (Edge e: graph[front]) {
          if (dist[e.to] == T(-1)) {
            dist[e.to] = dist[front] + e.cost;
            prev[e.to] = front;
            que.push(e.to);
          }

          if (farest2.second == -1 || farest2.first < dist[e.to]) {
            farest2 = make_pair(dist[e.to], e.to);
          }
        }
      }
    }

    vector<int> diameter_path;
    {
      int now = farest2.second;
      while (now != -1) {
        diameter_path.push_back(now);
        now = prev[now];
      }

      reverse(diameter_path.begin(), diameter_path.end());
    }

    return make_pair(diameter_path, farest2.first);
  }

} // namespace mylib

#endif // HARUILIB_GRAPH_DIAMETER_HPP
