#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "template/template.hpp"
#include "math/modint.hpp"
#include <random>

#include "convolution/multiple-zeta-moebius-transform.hpp"
#include "convolution/divisor-zeta-moebius-transform.hpp"

using mint = modint998244353;

mint op(mint a, mint b) {
  return a + b;
}

mint invop(mint a, mint b) {
  return a - b;
}

// mapで倍数のゼータ変換とメビウス変換やるやつのテスト
void test() {
  random_device seed_gen;
  mt19937 rng(seed_gen());


  auto map_transform = [&rng](int N) {
    map<ll, mint> multiple_map;
    map<ll, mint> divisor_map;

    vector<mint> multiple_vec(N + 1);
    vector<mint> divisor_vec(N + 1);

    for (ll i = 1; i * i <= N; i++) {
      if (N % i == 0) {
        int r1 = rng();
        int r2 = rng();
        multiple_map[i] = r1;
        multiple_vec[i] = r1;

        multiple_map[N / i] = r2;
        multiple_vec[N / i] = r2;
      }
    }

    divisor_map = multiple_map;
    divisor_vec = multiple_vec;

    // multiple
    {
      map<ll, mint> multiple_map2 = multiple::zeta_transform<ll,mint,op>(multiple_map);
      vector<mint> multiple_vec2 = multiple::zeta_transform_naive<mint,op>(multiple_vec);

      for (pair<ll, mint> plmi : multiple_map2) {
        assert(multiple_vec2[plmi.first] == plmi.second);
      }

      map<ll, mint> multiple_map3 = multiple::moebius_transform<ll,mint,invop>(multiple_map2);
      vector<mint> multiple_vec3 = multiple::moebius_transform_naive<mint,invop>(multiple_vec2);

      assert(multiple_map == multiple_map3 && "multiple transform for map");
      assert(multiple_vec == multiple_vec3 && "multiple transform for vector");

      for (pair<ll, mint> plmi : multiple_map3) {
        assert(multiple_vec3[plmi.first] == plmi.second);
      }
    }

    // divisor
    {
      map<ll, mint> divisor_map2 = divisor::zeta_transform<ll,mint,op>(divisor_map);
      vector<mint> divisor_vec2 = divisor::zeta_transform_naive<mint,op>(divisor_vec);

      for (pair<ll, mint> plmi : divisor_map2) {
        assert(divisor_vec2[plmi.first] == plmi.second && "divisor zeta transform");
      }

      map<ll, mint> divisor_map3 = divisor::moebius_transform<ll,mint,invop>(divisor_map2);
      vector<mint> divisor_vec3 = divisor::moebius_transform_naive<mint,invop>(divisor_vec2);

      assert(divisor_map == divisor_map3 && "multiple transform for map");
      assert(divisor_vec == divisor_vec3 && "multiple transform for vector");

      for (pair<ll, mint> plmi : divisor_map3) {
        assert(divisor_vec3[plmi.first] == plmi.second && "divisor moebius transform");
      }
    }

    };

  for (int i = 0; i < 1000; i++) {
    map_transform(rng() % 10000 + 1);
  }
  return;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  test();
  int A, B; cin >> A >> B;
  cout << A + B << endl;
}