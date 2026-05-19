#ifndef HARUILIB_STRUCTURE_POTENTIALIZED_UNION_FIND_TREE_HPP
#define HARUILIB_STRUCTURE_POTENTIALIZED_UNION_FIND_TREE_HPP

#include <vector>

template <typename T, T(*op)(T, T), T(*invop)(T, T), T(*e)()>
struct PotentializedUnionFindTree {
private:
  int n;
  std::vector<int> parent;
  std::vector<int> rank;
  std::vector<T> potential;

public:
  explicit PotentializedUnionFindTree(int _n) : n(_n), parent(_n), rank(_n, 0), potential(_n, e()) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }
  
  int merge(int a, int b, T d) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    int rootA = leader(a);
    int rootB = leader(b);

    if (rootA == rootB) return rootA;

    T new_potential = invop(potential[a], op(d, potential[b]));

    if (rank[rootA] < rank[rootB]) {  
      std::swap(rootA, rootB);
      new_potential = invop(e(), new_potential);
    }

    parent[rootB] = rootA;
    potential[rootB] = new_potential;

    if (rank[rootA] == rank[rootB]) {
      rank[rootA]++;
    }

    return rootA;
  }

  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return leader(a) == leader(b);
  }

  int leader(int a) {
    assert(0 <= a && a < n);
    if (parent[a] != a) {
      int root = leader(parent[a]);
      potential[a] = op(potential[a], potential[parent[a]]);
      parent[a] = root;
    }
    return parent[a];
  }

  int size(int a) {
    assert(0 <= a && a < n);
    int root = leader(a);
    int size = 0;
    for (int i = 0; i < n; ++i) {
      if (leader(i) == root) {
        ++size;
      }
    }
    return size;
  }

  T diff(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    assert(same(a,b));
    return invop(potential[a], potential[b]);
  }
};

#endif // HARUILIB_STRUCTURE_POTENTIALIZED_UNION_FIND_TREE_HPP