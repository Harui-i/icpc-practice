#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "template/template.hpp"

void test() {
  random_device seed_gen;
  mt19937 rng(seed_gen()); 

  while (rng() % 2 == 1) {
    continue;
  }

  return;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  test();
  int A, B; cin >> A >> B;
  cout << A+B << endl;
}