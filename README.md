# ICPC 練習環境

ICPC のチーム練習で使うための、軽めの C++ 練習環境です。

Mac を優先しつつ、Ubuntu でもそのまま使えることを目標にしています。Homebrew やインストール用スクリプトにはできるだけ依存しません。

## 最初に入れるもの

この環境では `make bundle` やライブラリ検証で `uv` / `uvx` を使うので、入っていない場合は先にインストールしてください。

```sh
curl -LsSf https://astral.sh/uv/install.sh | sh
```

VSCode で使う場合は、デバッグ用に `CodeLLDB` 拡張も必要です。

```sh
code --install-extension vadimcn.vscode-lldb
```

`code` コマンドが使えない場合は、VSCode の拡張機能画面から `CodeLLDB` をインストールしてください。(たぶんVSCodeの右下に「この拡張をインストールしますか？」のようなダイアログが出るはずです)

Mac で C++ コンパイラや `make` が入っていない場合は、Apple の開発ツールも一度だけ入れてください。

```sh
xcode-select --install
```

## 方針

- VSCode でも Vim でも同じコマンドでビルド・実行できる
- チームメイトのホームディレクトリやエディタ設定をなるべく汚さない
- ライブラリはこのリポジトリ内の `lib/` に置く
- `lib/` の中身は `github.com/Harui-i/library` をコピーしたもの
- Mac の Apple Clang でも通るように、テンプレートでは `#include <bits/stdc++.h>` を使わない

## 基本コマンド

新しいコンテスト用の問題ファイルを作る:

```sh
make new NAME=icpc2025prelim
```

`problems/icpc2025prelim/A/icpc2025prelim_A.cpp` から `problems/icpc2025prelim/Z/icpc2025prelim_Z.cpp` まで作られます。

各問題ディレクトリには `Makefile`、`sample.in`、`sample.out` も作られるので、作業中はそのディレクトリで短く実行できます。

```sh
cd problems/icpc2025prelim/A
```

デバッグ・サニタイザ付きでビルドして実行する:

```sh
make run
```

最適化付きでビルドして実行する:

```sh
make runo2
```

`sample.in` と `sample.out` でサンプルテストする:

```sh
make test
```

デバッグ・サニタイザ付きでビルドする:

```sh
make build
```

最適化付きでビルドする:

```sh
make buildo2
```

`#include "..."` を展開して提出用の1ファイルにする:

```sh
make bundle
```

問題ディレクトリで実行した場合、デフォルトでは同じディレクトリの `submit.cpp` に出力されます。

出力先を指定する:

```sh
make BUNDLE=answer.cpp bundle
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
├── problem.mk
├── template.cpp
├── vimrc.icpc
├── sample.in
├── sample.out
├── lib/
│   └── debug.hpp
├── problems/
│   └── icpc2025prelim/
│       ├── A/
│       │   ├── Makefile
│       │   ├── sample.in
│       │   ├── sample.out
│       │   └── icpc2025prelim_A.cpp
│       ├── B/
│       │   ├── Makefile
│       │   ├── sample.in
│       │   ├── sample.out
│       │   └── icpc2025prelim_B.cpp
│       └── ...
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
./vim.sh problems/icpc2025prelim/B/icpc2025prelim_B.cpp
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

使い方:

1. デバッグしたい `*.cpp` を開く
2. 必要なら同じディレクトリの `sample.in` を編集する
3. VSCode の Run and Debug から `Debug active file (CodeLLDB)` を選んで開始する

この設定では、開いているファイルをデバッグ用にビルドしてから起動します。標準入力には、開いているファイルと同じディレクトリの `sample.in` が渡されます。

Mac で必要なツールは、先頭の「最初に入れるもの」を参照してください。

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

`make bundle` は `uvx` 経由で `oj-bundle` を実行します。問題ディレクトリで実行できます。

```sh
cd problems/icpc2025prelim/A
make bundle
```

内部では次のようなコマンドを実行します。

```sh
uvx --from online-judge-verify-helper oj-bundle -I lib problems/icpc2025prelim/A/icpc2025prelim_A.cpp
```

`-I lib` を付けているので、`lib/` 以下のライブラリを展開できます。

例:

```cpp
#include "lib/graph/dijkstra.hpp"
```

`uvx` が見つからない場合は、先頭の「最初に入れるもの」を参考にして `uv` を入れてください。

参考: <https://docs.astral.sh/uv/>

## 注意

問題ディレクトリで `make test` すると、そのディレクトリの `sample.in` と `sample.out` を使います。

Mac の標準コンパイラでは `bits/stdc++.h` が使えないことが多いです。使いたい場合は GCC が必要になることがありますが、この環境では標準ヘッダを列挙する方針にしています。
<!--  -->
