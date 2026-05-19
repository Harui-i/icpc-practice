// https://shino16.github.io/blog/post/algo/%E3%82%AA%E3%83%BC%E3%83%88%E3%83%9E%E3%83%88%E3%83%B3/
// Dfaインターフェース
template <typename Alphabet, typename State>
class Dfa {
public:
  virtual State init() const = 0; // 初期状態を返す
  virtual State next([[maybe_unused]] State s, [[maybe_unused]] Alphabet a, [[maybe_unused]]int i) const = 0; // sにaを入力として与えた時の次の状態を返す
  virtual bool accept([[maybe_unused]] State s) const = 0; // sをオートマトンが受理するかどうか
  virtual bool successful([[maybe_unused]] State s) const { return false; } // どういうふうにnextしていこうが、絶対にacceptされる状態かどうか
  virtual bool unsuccessful([[maybe_unused]] State s) const { return false; } // どういうふうにnextしていこうが、絶対にaccpetされない状態かどうか
};