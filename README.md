# ICPC 練習環境

ICPC のチーム練習で使うための、軽めの C++ 練習環境です。

Mac を優先しつつ、Ubuntu でもそのまま使えることを目標にしています。Homebrew やインストール用スクリプトにはできるだけ依存しません。

## 方針

- VSCode でも Vim でも同じコマンドでビルド・実行できる
- チームメイトのホームディレクトリやエディタ設定をなるべく汚さない
- ライブラリはこのリポジトリ内の `lib/` に置く
- `lib/` の中身は `github.com/Harui-i/library` をコピーしたもの
- Mac の Apple Clang でも通るように、テンプレートでは `#include <bits/stdc++.h>` を使わない

## 基本コマンド

新しい問題ファイルを作る:

```sh
make new NAME=problems/a.cpp
```

デバッグ・サニタイザ付きでビルドして実行する:

```sh
make SRC=problems/a.cpp run
```

最適化付きでビルドして実行する:

```sh
make SRC=problems/a.cpp runo2
```

`sample.in` と `sample.out` でサンプルテストする:

```sh
make SRC=problems/a.cpp test
```

デバッグ・サニタイザ付きでビルドする:

```sh
make SRC=problems/a.cpp build
```

最適化付きでビルドする:

```sh
make SRC=problems/a.cpp buildo2
```

`#include "..."` を展開して提出用の1ファイルにする:

```sh
make SRC=problems/a.cpp bundle
```

デフォルトでは `.build/bundled.cpp` に出力されます。

出力先を指定する:

```sh
make SRC=problems/a.cpp BUNDLE=submit.cpp bundle
```

生成物を消す:

```sh
make clean
```

## ファイル構成

```text
.
├── Makefile
├── README.md
├── template.cpp
├── vimrc.icpc
├── sample.in
├── sample.out
├── lib/
│   └── debug.hpp
├── problems/
│   └── a.cpp
└── .vscode/
    ├── tasks.json
    ├── launch.json
    ├── settings.json
    └── extensions.json
```

## Vim で使う

このリポジトリ用の Vim 設定だけを読み込んで起動します。

```sh
./vim.sh
```

ファイルを指定して開く:

```sh
./vim.sh problems/b.cpp
./vim.sh sample.in
```

`vimrc.icpc` では、プラグインに依存しない最低限の設定だけを入れています。

## VSCode で使う

このディレクトリを VSCode で開けば使えます。

使えるタスク:

- `build active file`: 開いている C++ ファイルをビルド
- `run active file`: 開いている C++ ファイルをビルドして実行
- `runo2 active file`: 最適化付きでビルドして実行
- `sample test active file`: `sample.in` と `sample.out` でテスト
- `buildo2 active file`: 最適化付きでビルド
- `bundle active file`: 開いている C++ ファイルを提出用に bundle

デバッグは `Debug active file (CodeLLDB)` を使います。

Mac で VSCode デバッグを使う場合、VSCode 拡張の `CodeLLDB` が必要です。VSCode の拡張機能画面から入れられるので、Homebrew は不要です。

## ライブラリ

共通ライブラリは `lib/` に置きます。

例:

```cpp
#include "lib/debug.hpp"
```

`Makefile` で `-I.` を付けているので、リポジトリのルートからの相対パスで include できます。

## デバッグ出力

`lib/debug.hpp` の `dbg(x)` は、`LOCAL` が定義されているときだけ出力します。

```cpp
int x = 3;
vector<int> a = {1, 2, 3};
dbg(x);
dbg(a);
```

`make build` と `make run` では `-DLOCAL` が付くので出力されます。

`make buildo2` と `make runo2` では `-DLOCAL` が付かず、`-O2 -DNDEBUG` が付くので、提出に近い設定でビルド・実行できます。

## 提出用ファイルを作る

`make bundle` は `uvx` 経由で `oj-bundle` を実行します。

```sh
make SRC=problems/a.cpp bundle
```

内部では次のようなコマンドを実行します。

```sh
uvx --from online-judge-verify-helper oj-bundle -I lib problems/a.cpp
```

`-I lib` を付けているので、`lib/` 以下のライブラリを展開できます。

例:

```cpp
#include "lib/graph/dijkstra.hpp"
```

`uvx` が見つからない場合は、先に `uv` を入れてください。

参考: https://docs.astral.sh/uv/

## 注意

`sample.in` と `sample.out` は共通のサンプル用ファイルです。別の問題を解くときは、必要に応じて中身を書き換えてください。

Mac の標準コンパイラでは `bits/stdc++.h` が使えないことが多いです。使いたい場合は GCC が必要になることがありますが、この環境では標準ヘッダを列挙する方針にしています。
<!--  -->
