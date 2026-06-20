# 競技プログラミングライブラリの検証（online-judge-verifier）と別プロジェクトからの容易な取り込みの設計（改訂版）

`git submodule` の運用負荷と、`abc123/a/main.cpp` のようなネストしたディレクトリからの相対パス記述の煩雑さを解決するため、**「グローバル共有ライブラリ ＋ VSCode インクルードパス設定」**のアプローチを提案します。

この方法により、`git submodule` を使わず、解答ファイル内でも `#include "geometry/geometry.hpp"` とシンプルに記述でき、VSCode の補完や Linter も正常に機能します。

---

## 1. 提案手法：グローバル共有ライブラリ ＋ インクルードパス指定

解答リポジトリごとにライブラリをコピー（または submodule 化）するのではなく、PCローカル上の1箇所にライブラリを配置し、各プロジェクトからそこを参照します。

### 構成の概要

```
/home/laft/procon/
  ├── procon-lib/           <-- [本リポジトリ] ライブラリ本体（ここを開発・検証する）
  │     ├── geometry/geometry.hpp
  │     └── math/...
  └── procon-solutions/     <-- [別リポジトリ] 解答用のコードを置く場所
        ├── .vscode/
        │     └── c_cpp_properties.json  <-- VSCodeのLinter設定
        └── abc123/
              └── a/
                    └── main.cpp         <-- 解答コード
```

### 実装手順

#### ① 解答コードでの記述
`abc123/a/main.cpp` からインクルードする際、相対パス（`../../` など）を使わずに、**ライブラリのルートからのパス**で記述します。
```cpp
#include "geometry/geometry.hpp"  // すっきり書ける！
```

#### ② VSCode Linter (IntelliSense) の設定
解答リポジトリ（`procon-solutions`）のルートに `.vscode/c_cpp_properties.json` を作成（または編集）し、`includePath` に `procon-lib` の絶対パスを追加します。

**設定例 (`.vscode/c_cpp_properties.json`):**
```json
{
  "configurations": [
    {
      "name": "WSL",
      "includePath": [
        "${workspaceFolder}/**",
        "/home/laft/procon/procon-lib"  // ライブラリの絶対パスを追加
      ],
      "compilerPath": "/usr/bin/g++",
      "cStandard": "c17",
      "cppStandard": "c++17",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
```
> [!TIP]
> これにより、VSCode は `/home/laft/procon/procon-lib` からヘッダーファイルを自動的に探索するため、`#include "geometry/geometry.hpp"` の赤い波線が消え、コードジャンプや入力補完が完全に動作します。

#### ③ ローカルでのコンパイル
コンパイル（または検証ツールでの実行）時、コンパイラにインクルードパスを指定する `-I` オプションを渡します。
```bash
g++ -std=c++17 -I /home/laft/procon/procon-lib main.cpp
```

#### ④ 提出用ファイルの生成 (`oj-bundle`)
提出用に1つのファイルにバンドルする際も、同様に `-I` オプションでライブラリのパスを指定します。
```bash
oj-bundle main.cpp -I /home/laft/procon/procon-lib > submission.cpp
```

---

## 2. oj-verify を想定した推奨ディレクトリ構成とヘッダー化

`oj-verify` を動かすにあたって、**「再利用するライブラリ本体」**と**「検証用のテストコード」**を綺麗に分離する構成がベストプラクティスです。

### 推奨するディレクトリ構成

以下のように、ライブラリ本体は `geometry/` や `math/` などのフォルダ配下に `.hpp` ファイルとして配置し、検証用テストは `test/` ディレクトリにまとめます。

```
procon-lib/ (本リポジトリ)
├── .github/
│     └── workflows/
│           └── verify.yml      <-- CI(GitHub Actions)の設定ファイル
├── .verify-helper/             <-- oj-verify が自動生成するキャッシュやドキュメント設定
├── geometry/                   <-- [ライブラリ本体] 分野別に分ける
│     └── geometry.hpp          <-- ヘッダーオンリーファイル (.hpp)
├── math/                       <-- [ライブラリ本体]
│     └── math.hpp
├── test/                       <-- [検証用テスト] oj-verify が自動で探索する
│     ├── example.test.cpp      <-- 既存のテスト
│     └── geometry.test.cpp     <-- geometry.hpp を検証するためのテストコード
├── README.md
└── PROPOSAL.md
```

### ヘッダー化（`.hpp` + `#pragma once`）にする理由と書き方

#### 1. なぜ `.hpp` にするのか？
C++で他のファイルから `#include` されることを前提としたファイル（ヘッダーファイル）は、実装ファイルである `.cpp` と区別するために `.hpp` または `.h` という拡張子を使います。

#### 2. なぜ `#pragma once` が必要なのか？
競技プログラミングでは、複数のライブラリを組み合わせることがよくあります。
例えば、`geometry.hpp` が内部で `point.hpp` をインクルードしており、`main.cpp` でも `geometry.hpp` と `point.hpp` の両方をインクルードした場合、コードが2重に展開されて「二重定義エラー」になります。

これを防ぐため、**すべてのライブラリファイル（.hpp）の最初の1行目**に以下を記述します。これにより、同じファイルが複数回インクルードされるのを自動的に防ぎます。

**ライブラリの実装例 (`geometry/geometry.hpp`):**
```cpp
#pragma once  // <-- これを必ず先頭に書く

#include <complex>
#include <vector>
#include <cassert>
#include <algorithm>

// ライブラリの本体コード...
```

#### 3. テストファイル（`.test.cpp`）の書き方
`test/` ディレクトリ配下に置くテストファイル（例: `test/geometry.test.cpp`）には、`#define PROBLEM` を書いて、ライブラリ本体をインクルードします。

**テストファイル例 (`test/geometry.test.cpp`):**
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/4/ALDS1_4_B" // 検証したい問題のURL

#include "../geometry/geometry.hpp" // ライブラリ本体をインクルード
#include <iostream>

using namespace std;

int main() {
    // ライブラリを呼び出して問題を解く検証コード
    return 0;
}
```

---

## 3. 実現に向けたロードマップ（道筋）

### ステップ 1: ディレクトリ構成の整理とヘッダー化
- `test/` ディレクトリを作成し、`example.test.cpp` を移動。
- `geometry/geometry.cpp` を `geometry/geometry.hpp` にリネーム。
- `geometry.hpp` の先頭に `#pragma once` を追加。
- `example.test.cpp` などからインクルードするパスを `.hpp` へ修正。

### ステップ 2: GitHub Actions ワークフロー (`verify.yml`) の更新
- アクションを最新版にアップデート。
- テストが正しく GitHub Actions 上で走ることを確認。

### ステップ 3: 解答プロジェクト側での動作確認
- 解答プロジェクト側の VSCode 設定にインクルードパスを設定し、補完や `oj-bundle` をテスト。

---

## 補足: ローカル環境で `oj-bundle` を安全にインストールする方法

ローカル（WSL等）環境でも、単に `pip install online-judge-verify-helper` を実行すると、最新の `setuptools` (バージョン82.0.0以上) が入ってしまい、CIと同様に `ModuleNotFoundError: No module named 'pkg_resources'` エラーが発生します。

これを防ぎ、高速かつ安全にインストールするために、最新の Python パッケージマネージャーである **`uv`** を使用したインストールを推奨します。

### `uv` を使用したインストール方法
`uv` を用いて隔離された環境に `oj-bundle` / `oj-verify` をインストールし、同時に `setuptools` のバージョンを固定します。これにより、他の Python 環境を汚さずにコマンドがグローバルに使えます。

```bash
# setuptools のバージョンを 82.0.0 未満に固定してインストール
uv tool install --with "setuptools<82.0.0" online-judge-verify-helper
```

---

## 4. 他のオンラインジャッジサービスへのテスト拡張

`oj-verify` は AOJ 以外の複数のサービスでのテスト実行に対応しています。それぞれの設定方法は以下の通りです。

### 1. Library Checker (yosupo judge) 【推奨】
最も強力かつ高度なアルゴリズムのテストケースが揃っているサービスです。
* **準備**: アカウントやトークンの設定は**不要**です（AOJと同様にすぐに使えます）。
* **設定方法**: テストファイル（`.test.cpp`）の先頭に Library Checker の問題 URL を指定するだけです。
  ```cpp
  #define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
  ```

### 2. YukiCoder
有志による問題が集まる日本のジャッジサービスです。
* **準備**:
  1. YukiCoder の設定ページから「APIトークン」を取得します。
  2. GitHub リポジトリの **Settings > Secrets and variables > Actions** に移動し、`YUKICODER_TOKEN` という名前の Repository Secret を作成し、トークンを登録します。
  ※ すでに `verify.yml` の `Run tests` ステップに `YUKICODER_TOKEN: ${{ secrets.YUKICODER_TOKEN }}` を設定してあるため、シークレットを登録するだけで利用可能になります。
* **設定方法**:
  ```cpp
  #define PROBLEM "https://yukicoder.me/problems/no/9000"
  ```

### 3. AtCoder
日本で最も活発な競プロサービスですが、Actions 上からの自動提出にはいくつかのハードルがあります。
* **注意点**: AtCoder は非ログインでのコード提出を受け付けないため、GHA上でログインするか、あるいはテストデータフェッチ用の `DROPBOX_TOKEN` を Secrets に登録する必要があります。また、昨今の Cloudflare によるスクレイピング保護により、GitHub Actions のランナーからのログイン提出がブロックされるケースが多く、テスト先としては安定しません。
* **対策**: 高度なデータ構造やアルゴリズムを検証したい場合は、AtCoder の代わりに **Library Checker** の問題を使うのが現在のベストプラクティスです。
* **設定方法**:
  ```cpp
  #define PROBLEM "https://atcoder.jp/contests/practice/tasks/practice_1"
  ```
