#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0560"

#include "template/template.hpp"
#include "dp/cumulative-sum-2d.hpp"

int main () {
  int M, N; cin >> M >> N;
  int K; cin >> K;
  CumulativeSum2D<int>J(M,N);
  CumulativeSum2D<int>O(M,N);
  CumulativeSum2D<int>I(M,N);
  for(int i=0; i<M; i++) {
    string S; cin >> S;
    assert(S.size() == N);
    for(int j=0; j<S.size(); j++) {
      if (S[j] == 'J') J.add(i,j,1);
      if (S[j] == 'O') O.add(i,j,1);
      if (S[j] == 'I') I.add(i,j,1);
    }
  }

  J.build(); O.build(); I.build(); 

  for(int i=0; i<K; i++) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    a--; b--;
    cout << J.query(a,b,c,d) << " " << O.query(a,b,c,d) << " " << I.query(a,b,c,d) << endl;
  }
}