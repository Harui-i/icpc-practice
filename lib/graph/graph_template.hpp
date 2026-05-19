#ifndef HARUILIB_GRAPH_TEMPLATE_HPP
#define HARUILIB_GRAPH_TEMPLATE_HPP

#include <vector>

template <typename T>
struct Edge {
  int from; int to;
  T cost;

  // default constructor
  Edge () : from(-1), to(-1), cost(T(0)) {}

  Edge(int _from, int _to, T _cost) : from(_from), to(_to), cost(_cost) {}

  // unweighted
  Edge(int _from, int _to) : from(_from), to(_to), cost(T(1)) {}

  bool operator==(const Edge& rhs) const {
    return from == rhs.from && to == rhs.to && cost == rhs.cost;
  }

  bool operator<(const Edge& rhs) const {
    return cost < rhs.cost;
  }
  
  bool operator>(const Edge& rhs) const {
    return cost > rhs.cost;
  }

};


template <typename T>
struct Graph : std::vector<std::vector<Edge<T>>> {

  using std::vector<std::vector<Edge<T>>>::vector; // inherit constructors

  void add_edge(int i, Edge<T> e) {
    (*this)[i].push_back(e);
  }

  void add_edge(Edge<T> e) {
    (*this)[e.from].push_back(e);
  }

  // weighted
  void add_edge(int _from, int _to, T _cost) {
    (*this)[_from].push_back(Edge(_from, _to, _cost));
  }

  // unweighted
  void add_edge(int _from, int _to) {
    (*this)[_from].push_back(Edge(_from, _to, T(1)));
  }

};

#endif // HARUILIB_GRAPH_TEMPLATE_HPP