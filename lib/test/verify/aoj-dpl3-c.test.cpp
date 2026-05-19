#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_C"

#include "template/template.hpp"
#include "dp/largest-rectangle-in-a-histogram.hpp"

int main() {
  int N; cin >> N;
  vector<int>h(N); for(int i=0; i<N; i++) cin >> h[i];
  cout << largest_reactangle_in_a_histogram<int>(h) << endl;
}