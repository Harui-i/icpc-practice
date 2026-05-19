---
title: 決定性有限オートマトン(DFA, Deterministic Finite Automaton)
documentation_of: //dp/automaton/automaton.hpp
---

桁DPとかをわりと簡潔(?)に解くための仕組み？データ構造？

有限な状態数で、状態と入力が決まると次の状態も一意に決まりますよでおなじみの、決定性有限オートマトン(Deterministic Finite Automaton)を扱うことを考えている。
決定性じゃない(状態と入力に対して、次の状態が複数考えられるような)場合は、遷移先を集合としてみて(?)bitDPをすると有限な場合に帰着できるらしいですよ。

めちゃめちゃ参考にしました 1: [https://kuretchi.github.io/blog/entries/automaton-dp/](https://kuretchi.github.io/blog/entries/automaton-dp/)

めちゃめちゃ参考にしました 2: [https://shino16.github.io/blog/post/algo/%E3%82%AA%E3%83%BC%E3%83%88%E3%83%9E%E3%83%88%E3%83%B3/](https://shino16.github.io/blog/post/algo/%E3%82%AA%E3%83%BC%E3%83%88%E3%83%9E%E3%83%88%E3%83%B3/) 
めちゃめちゃ参考にしました 3: [https://ja.wikipedia.org/wiki/%E6%B1%BA%E5%AE%9A%E6%80%A7%E6%9C%89%E9%99%90%E3%82%AA%E3%83%BC%E3%83%88%E3%83%9E%E3%83%88%E3%83%B3](https://ja.wikipedia.org/wiki/%E6%B1%BA%E5%AE%9A%E6%80%A7%E6%9C%89%E9%99%90%E3%82%AA%E3%83%BC%E3%83%88%E3%83%9E%E3%83%88%E3%83%B3)


定義は3に書いてある。 1は"~な数の個数"だけではなくて"~な数についてxxした総和"みたいなものも扱えることを取り上げている(実際、ジグザグ数の総和を(個数ではなく!!)求めている)が、ちょっとよくわからない部分も多い。

2は実装の参考になった。

オートマトンで考えることの嬉しさは、状態の管理が比較的らくになったり、「２つのオートマトンが受理する文字列のみを受理するオートマトン」などを簡単に[^1]扱えるところにあるんじゃないか。

Verify用の問題をどうすればいいかに悩んでいる。実装例があったほうがわかりやすいだろうし。AtCoderの問題をVerifyに使うにはDropboxのAPIキーがないといけないし、yukicoderは使ったことがないし、AOJにある問題はジグザグ数(苦行)しか知らない。

[^1]: 要出典
