# procon-lib

[![Actions Status](https://github.com/laft2/procon-lib/workflows/verify/badge.svg)](https://github.com/laft2/procon-lib/actions)

競技プログラミング用の C++ ライブラリ集です。
すべてヘッダーオンリー (`.hpp`) で提供されます。

---

## ディレクトリ構造

```
procon-lib/
├── atcoder/             # AtCoder Library (ACL)
│   ├── dsu.hpp          # Disjoint Set Union
│   ├── segtree.hpp      # Segment Tree
│   └── ...              # その他 ACL 提供ヘッダー
├── geometry/            # 幾何学関連アルゴリズム
│   └── geometry.hpp     # 幾何ライブラリ
├── math/                # 数学・数論関連アルゴリズム
│   ├── factrial.hpp     # 階乗・組合せ計算（O(N) 事前計算）
│   └── modint.hpp       # 剰余付き整数（ModInt）
├── tree/                # 木構造関連アルゴリズム
│   └── lca.hpp          # 最近共通祖先 (LCA)
├── test/                # online-judge-verifier 用のテストコード
│   ├── factorial.test.cpp
│   └── lca.test.cpp
└── .github/
    └── workflows/
        └── verify.yml   # GitHub Actions (自動テスト・ドキュメント生成)
```

> [!NOTE]
> **AtCoder Library (ACL) の同梱について**
> 本リポジトリには、AtCoder 公式の [ac-library](https://github.com/atcoder/ac-library) の `atcoder` ディレクトリ内のファイル群を `atcoder/` 配下に内包しています。
> これにより、このライブラリをインクルードするだけで、ACL のデータ構造やアルゴリズム（`atcoder::dsu`, `atcoder::segtree` など）を利用したライブラリ開発や解答コードの作成が可能です。

---


## インストールと設定

### 1. ライブラリの配置（グローバル共有方式）
本リポジトリをローカルの任意の場所（例: `/home/laft/procon/procon-lib`）にクローンします。
```bash
git clone https://github.com/あなたのユーザー名/procon-lib.git
```

### 2. 解答リポジトリ側（VSCode）の設定
解答を記述する別のプロジェクトで、`.vscode/c_cpp_properties.json` を開き、`includePath` に本リポジトリの絶対パスを追加します。

**設定例 (`.vscode/c_cpp_properties.json`):**
```json
{
  "configurations": [
    {
      "name": "WSL",
      "includePath": [
        "${workspaceFolder}/**",
        "/home/laft/procon/procon-lib"  // ← クローンした本ライブラリの絶対パスを指定
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
これにより、解答プロジェクト内で `#include "geometry/geometry.hpp"` と記述するだけで、VSCode 上でのコード補完や定義ジャンプが機能するようになります。

---

## 使用方法

### コード内でのインクルード
解答コード（`main.cpp`）で必要なライブラリをインクルードします。
```cpp
#include "geometry/geometry.hpp"
#include "math/modint.hpp"
#include "math/factrial.hpp"
```

### ローカルでのコンパイル
コンパイル時に、`-I` オプションで本ライブラリの絶対パスを指定します。
```bash
g++ -std=c++17 -I /home/laft/procon/procon-lib main.cpp -o main
```

### 提出用ファイルの生成
`oj-bundle` を使用して、依存ヘッダーをすべて1つのファイルにマージします。
```bash
oj-bundle main.cpp -I /home/laft/procon/procon-lib > submission.cpp
```

---

## 自動検証 (online-judge-verify-helper)

本リポジトリは GitHub Actions と連携しており、リポジトリにプッシュすると自動で `oj-verify` が走り、検証ステータスが更新されます。

### 1. ローカルでのインストール
依存パッケージのバージョン競合やクラッシュを防ぐため、最新のパッケージマネージャーである **`uv`** を使用した隔離インストールを推奨します。
```bash
uv tool install --with "setuptools<82.0.0" online-judge-verify-helper
```

### 2. ローカルでのテスト実行
```bash
# すべての検証テストを実行
oj-verify all
```

### 3. テスト（検証コード）の追加方法
1. `test/` ディレクトリ内に `.test.cpp` という拡張子でファイルを作成します（例: `test/my_algorithm.test.cpp`）。
2. ファイルの先頭行に、検証先（オンラインジャッジ）の問題の URL を記述します。
3. ライブラリ本体をインクルードし、問題を解くコードを実装します。

**テストファイルの作成例:**
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/4/ALDS1_4_B"

#include "../math/factrial.hpp" // 相対パスでライブラリをインクルード
#include <iostream>

using namespace std;

int main() {
    // 検証用の解答コード
    return 0;
}
```
