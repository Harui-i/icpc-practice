#ifndef HARUILIB_GRAPH_DIJKSTRA_HPP
#define HARUILIB_GRAPH_DIJKSTRA_HPP

#include <queue>
#include <vector>
#include <limits>
#include <utility>

#include "graph/graph_template.hpp"

template <typename T>
std::vector<T> dijkstra(const Graph<T>& graph, int start) {
  int N = (int)graph.size();
  constexpr T INF = numeric_limits<T>::max();
  std::vector<T>dist(N, INF);
  using P = std::pair<T, int>;

  std::priority_queue<P, std::vector<P>, std::greater<P>>que;

  que.push(make_pair(T(0), start));
  dist[start] = T(0);

  while (!que.empty()) {
    P front = que.top(); que.pop();

    if (dist[front.second] < front.first) continue;

    for (Edge ed : graph[front.second]) {

      if (dist[ed.to] > front.first + ed.cost) {
        dist[ed.to] = front.first + ed.cost;
        que.emplace(dist[ed.to], ed.to);
      }
    }
  }

  return dist;
}

template <typename T>
std::pair<std::vector<T>, std::vector<int>> dijkstra_path(const Graph<T>& graph, int start) {
  int N = (int)graph.size();
  constexpr T INF = numeric_limits<T>::max();

  using P = std::pair<T, int>;
  std::vector<T>dist(N, INF);
  std::vector<int>prev(N, -1);

  std::priority_queue<P, std::vector<P>, std::greater<P>>que;
  que.push(make_pair(T(0), start));
  dist[start] = T(0);

  while (!que.empty()) {
    P front = que.top(); que.pop();

    if (dist[front.second] < front.first) continue;

    for (Edge ed : graph[front.second]) {
      if (dist[ed.to] > front.first + ed.cost) {
        dist[ed.to] = front.first + ed.cost;
        prev[ed.to] = front.second;
        que.emplace(dist[ed.to], ed.to);
      }
    }
  }

  return make_pair(dist, prev);
}

#endif // HARUILIB_GRAPH_DIJKSTRA_HPP