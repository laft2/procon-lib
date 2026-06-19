# procon-lib

[![Actions Status](https://github.com/laft2/procon-lib/workflows/verify/badge.svg)](https://github.com/laft2/procon-lib/actions)

競技プログラミング用のC++ライブラリ集。
ヘッダーオンリーで提供されます。

## ディレクトリ構造

```
procon-lib/
├── geometry/        # 幾何学関連アルゴリズム
│   └── geometry.hpp
├── math/              # 数学関数
│   └── math.hpp
├── flow/              # ネットワークフロー関連
│   └── flow.hpp
├── string/            # 文字列関連
│   └── string.hpp
└── test/              # 各アルゴリズムのテストコード
    ├── geometry.test.cpp
    └── ...
```

## インストール・設定

### 1. リポジトリのクローン

```bash
git clone https://github.com/laft2/procon-lib
cd procon-lib
```

### 2. VSCodeのIncludeパス設定

お使いの環境に応じて `.vscode/c_cpp_properties.json` を設定します。

```json
{
    "configurations": [
        {
            "name": "WSL",
            "includePath": [
                "${workspaceFolder}/**",
                "/home/laft/procon/procon-lib" // ← リポジトリの絶対パス
            ],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c++20",
            "cppStandard": "c++20",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ]
}
```

## 使用方法

### ヘッダーのインクルード

```cpp
#include "geometry/geometry.hpp"
#include "math/math.hpp"
// ...
```

### コンパイル方法

`-I` オプションでライブラリのパスを指定します。

```bash
g++ -std=c++20 -I /home/laft/procon/procon-lib main.cpp -o main
```

### 提出用ファイルの生成

`oj-bundle` を使うと、依存ヘッダーを全て1ファイルにまとめられます。

```bash
# 解答コードが main.cpp の場合
oj-bundle main.cpp -I /home/laft/procon/procon-lib -o submission.cpp
```

## テスト

`oj-verify` を使用して各アルゴリズムをテストします。

```bash
# 全てのテストを実行
./.verify-helper/bin/oj-verify all

# 特定のカテゴリのみ実行
./.verify-helper/bin/oj-verify geometry
```

### テストの追加

1. `test/geometry.test.cpp` のようなファイルを作成
2. `@title`, `@url` を先頭に記述して AtCoderなどの問題を référence
3. `@cpp` ブロック内でテストコードを実装

**例:**

```cpp
#include <iostream>
#include <vector>
#include "geometry/geometry.hpp"
#include "math/math.hpp"
// ...
```
