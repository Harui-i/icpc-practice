#include "automaton.hpp"

// nextは数字の右端に書き加えるイメージ。つまり、いろいろな桁数を考えられる。
// しかし、固定した桁数に対して左から埋めていくパターンで使いたい場合もありそう。
// 数字のMの倍数のみ受理するオートマトン
template <typename Alphabet> 
class RemainderAutomaton : public Dfa<Alphabet, int> {
  const int M;
  const int N_siz;

public:
  using State = int;
  RemainderAutomaton(int _N_siz, int _M) : M(_M), N_siz(_N_siz) {}

  State init() const override {
    return State(0);
  }

  State next(State s, char c, [[maybe_unused]] int i) const override {
    State ret = ((long long)s*10 + (long long)(c - '0') )%M; 

    return ret;
  }

  bool accept(State s) const override {
    return s == 0;
  }

  bool successful ([[maybe_unused]] State  s) const override {
    return false;
  }

  bool unsuccessful([[maybe_unused]] State s) const override {
    return false;
  }
  
};