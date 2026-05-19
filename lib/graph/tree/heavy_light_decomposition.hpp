#ifndef HARUILIB_GRAPH_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP
#define HARUILIB_GRAPH_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP

#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>

#include "graph/graph_template.hpp"

namespace HaruiLib {
  // cf : https://ngtkana.hatenablog.com/entry/2024/06/24/200138
  struct Interval {
    // top_id : interval のもっとも根に近い頂点のid
    // bottom_id : interval のもっとも葉に近い頂点のid
    // last : LCAを含む interval であるかどうか
    // reverse : from → to と top → bottomが逆向きかどうか
    int top_id, bottom_id;
    bool last;
    bool reverse;
  
    Interval(int _top_id, int _bottom_id, bool _last, bool _reverse) : top_id(_top_id), bottom_id(_bottom_id), last(_last), reverse(_reverse) {
  
    }
  };
  
  using Path = std::vector<Interval>;
  
  /*
  木をいくつかのパスに分けるアルゴリズム。
  うまくDFSしてパスに分けると、同じパスの中でidが連続するので、一つのパスの中ではセグメント木などの列に対してのアルゴリズムが使えるようになる。
  
  頂点属性の問題はかんたん。
  辺属性の問題は、辺の子側の頂点にその情報をもたせて管理するといい。 そのときはLCAに注意する。
  */
  struct HLD {
  private:
    bool is_built = false;
  public:
    //vector<vector<int>>children;
    std::vector<int> parent;
    std::vector<int> id; // id[v] := 頂点vがdfs順で何番目にあるか。 HLDで分割したパスの中では、深さが浅い方から深い方へidが連続して増えていく。
    std::vector<int> id2;
    std::vector<int> head; // head[v] := 頂点vが所属する分割されたパスの、一番根に近い頂点。
    std::vector<int> depth; // depth[v] := 頂点vの深さ
    Graph<int> graph;
  
    HLD (int N) : parent(std::vector<int>(N, -1)), id(std::vector<int>(N)), id2(std::vector<int>(N)), head(std::vector<int>(N)), depth(std::vector<int>(N)), graph(N) {}
  
    void build(int root=0) {
      dfs_sz(root);
      int k = 0; dfs_hld(root, k);
      is_built = true;
    }
  
    int dfs_sz(int v) {
      int ret = 1, mx_sz = 0;
      for (Edge<int>& nxt : graph[v]) {
        if (nxt.to == parent[v]) continue;
  
        parent[nxt.to] = v;
        depth[nxt.to] = depth[v] + 1;
        int sz = dfs_sz(nxt.to);
        ret += sz;
        if (mx_sz < sz) {
          mx_sz = sz;
          std::swap(graph[v][0], nxt);
        }
      }
  
      return ret;
    }
  
    void dfs_hld(int v, int& k) {
      id[v] = k; k++;
      for (Edge e : graph[v]) {
        if (e.to == parent[v]) continue;
  
        // 今見ている辺が最大連結成分方向への辺なら,head[e.to] = head[v]
        // そうでないなら、head[e.to] = e.to;
        head[e.to] = (e == graph[v][0] ? head[v] : e.to);
        dfs_hld(e.to, k);
      }
      id2[v] = k;
    }
  
    int lca(int u, int v) {
      assert(is_built);
      while (true) {
        if (id[u] > id[v]) std::swap(u, v);
        if (head[u] == head[v]) return u;
  
        v = parent[head[v]];
      }
    }
  
    Path get_path(int u, int v) {
      assert(is_built);
      Path upath, vpath;
  
      while (head[u] != head[v]) {
  
        // ちなみにu,vのdepthの大小関係は変わり続けることもある。
        // 10 → 12など。
  
        // v's head is deeper
        if (depth[head[v]] >= depth[head[u]]) {
          assert(depth[head[v]] >= depth[head[u]]);
          /*
            /   : heavy edge
           .... : light edge
  
              head[u]
                 /
                /...
               u  ...
              /   head[v]
             /       \
            /         \
           /           v
          */
  
          // u→v なのでreverse=false
          vpath.emplace_back(id[head[v]], id[v], false, false);
          v = parent[head[v]];
        }
  
        // u's head is deeper
        else if (depth[head[v]] < depth[head[u]]) {
          /*
            /   : heavy edge
           .... : light edge
  
              head[v]
                 /
                /...
               v  ...
              /   head[u]
             /       \
            /         \
           /           u
          */
  
          //
          upath.emplace_back(id[head[u]], id[u], false, true);
          u = parent[head[u]];
        }
      }
  
      // v is deeper
      /*
         u
        /
       /  ←↓
      /
     v
  
      */
      if (depth[v] > depth[u]) {
        upath.emplace_back(id[u], id[v], true, false);
      }
  
      // u is deeper
      /*
         v
        /
       /  →↑
      /
     u
  
      */
      else {
        upath.emplace_back(id[v], id[u], true, true);
      }
      Path retpath = upath;
      std::reverse(vpath.begin(), vpath.end());
      for (Interval path : vpath) retpath.push_back(path);
  
      return retpath;
    }
  
    std::pair<int,int> subtree_query(int r) {
      assert(r < int(id.size()));
      return std::make_pair(id[r], id2[r]);
    }
  
  };

}
#endif // HARUILIB_GRAPH_TREE_HEAVY_LIGHT_DECOMPOSITION_HPP
