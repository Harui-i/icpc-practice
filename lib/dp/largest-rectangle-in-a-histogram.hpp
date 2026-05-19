#ifndef HARUILIB_DP_LARGEST_RECTANGLE_IN_A_HISTOGRAM_HPP
#define HARUILIB_DP_LARGEST_RECTANGLE_IN_A_HISTOGRAM_HPP
#include <stack>
#include <vector>

template <typename T>
long long  largest_reactangle_in_a_histogram(std::vector<T>& vec) {
  int N = vec.size();
  std::stack<T> st; // 最弱番長(をindexで表した)待機列のイメージ。卒業による引退がないため、dequeの右側しか使わず、stackで十分。
  // stackに対応するvecの値は、下から上にかけて狭義(!!)単調増加になっている。
  std::vector<int> ridx(N); // ridx[i] := i < j であって、vec[i] > vec[j] となるような jのうち最も小さいもの
  // そんなjが存在しない場合、Nにしている

  std::vector<int> lidx(N, -1); // lidx[i] := j<iであって vec[j] < vec[i]となるようなjのうち最も大きいもの 
  // そんなjが存在しない場合、-1とする
  // つまり、自分より弱い先輩のうち、一番年が近い人、みたいな

  for(int i=0; i<N; i++) {
    T vi = vec[i];
    while (st.size() > 0) {

      // 自分より強い(もしくは同じ実力の)先輩は引退する
      // 先輩が自分より強い場合は、先輩を天井とするような最大長方形は確定しているからもう出ていってもらっていいし、
      // 同じ実力のときは、自分の最大長方形と先輩の最大長方形が一致するので、先輩は引退してもらっていい。(すると、スタックが狭義単調増加になる) 
      if (vec[st.top()] >= vi) {
        ridx[st.top()] = i; 
        st.pop();
      }

      else break; 
    }
    // stには自分より弱い先輩だけが残っている。
    lidx[i] = st.empty() ? -1 : st.top();
    st.push(i);
  }

  // 自分より弱い後輩が入って来なかった人たちの処理
  while (st.size() > 0) {
    ridx[st.top()] = N;
    st.pop();
  }

  ll ans = 0;
  for(int i=0; i<N; i++) {
    chmax(ans, (ll)(ridx[i] - (lidx[i] + 1)) * vec[i]);
  }
  return ans; 
}
#endif //HARUILIB_DP_LARGEST_RECTANGLE_IN_A_HISTOGRAM_HPP