#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n_input; cin >> n_input;
  vector<int> a_input(n_input);
  for (int i = 0; i < n_input; i++) cin >> a_input[i];

  cout << "Hello,world!" << endl;
  cout << "n_input: " << n_input << endl;
  for (int a : a_input) cout << a << " ";
  cout << endl;

  return 0;
}
