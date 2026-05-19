#ifndef HARUILIB_GRAPH_BELLMANFORD_HPP
#define HARUILIB_GRAPH_BELLMANFORD_HPP

#include <cassert>
#include <queue>
#include <vector>
#include <limits>

#include "graph/graph_template.hpp"

// 完全にパクリました
// https://ei1333.github.io/library/graph/shortest-path/bellman-ford.hpp
template <typename T> 
std::vector<T> bellman_ford(const std::vector<Edge<T>>& edges, int N, int start) {
  assert(0 <= start && start < N);

  const int M = int(edges.size());
  constexpr T PLINF = std::numeric_limits<T>::max();
  constexpr T MNINF = std::numeric_limits<T>::min();

  std::vector<T> dist(N, PLINF);
  dist[start] = T(0);

  for (int i=0; i<N-1; i++) {
    for (int j=0; j<M; j++) {
      Edge e = edges[j];
      if (dist[e.from] >= PLINF) continue;

      if (dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
      }
    }
  }

  std::vector<bool> negative(N, false);

  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      Edge e = edges[j];

      if (dist[e.from] >= PLINF) continue;
      if (dist[e.to] > dist[e.from] + e.cost) {
        dist[e.to] = dist[e.from] + e.cost;
        negative[e.to] = true;
      }

      if (negative[e.from]) negative[e.to] = true;
    }
  }

  for (int i=0; i<N; i++) if (negative[i]) dist[i] = MNINF;

  return dist;
}

#endif // HARUILIB_GRAPH_BELLMANFORD_HPP