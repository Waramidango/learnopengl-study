# LearnOpenGL Study

[LearnOpenGL](https://learnopengl.com/) を用いたOpenGL・リアルタイムレンダリングの学習リポジトリ。

Visual StudioなどのIDEに依存した環境ではなく、**WSL上でCMakeを使ってビルドできる開発環境を自分で構築すること**を目的とする。

単にLearnOpenGLのコードを動かすだけではなく、C++、CMake、GLFW、OpenGL、GLAD、GLSLなど、それぞれがどの役割を持ち、どのように連携しているのかを理解することを重視する。

---

## Goals

* OpenGLの基本的な描画パイプラインを理解する
* C++からOpenGLを利用する方法を理解する
* シェーダー（GLSL）の仕組みを理解する
* CMakeによるC++プロジェクトのビルド方法を理解する
* 外部ライブラリの依存関係を把握し、自分で管理できるようにする
* CPU側のC++とGPU側のGLSLがどのように連携するのか理解する
* 最終的に、リアルタイムレンダリングの仕組みを自分で実装・改造できるようにする

---

## Development Environment

### OS

* Windows 11
* WSL2
* Ubuntu
* WSLg

WSLgを利用することで、WSL上で実行したGUIアプリケーションのウィンドウをWindows側に表示する。

今回の環境では、WSL上のOpenGLアプリケーションからWindows側のGPUを利用できることも確認している。

---

## Development Tools

| Tool / Package  | Version / Description      |
| --------------- | -------------------------- |
| build-essential | UbuntuのC/C++開発に必要な基本パッケージ群 |
| g++             | 15.2.0                     |
| CMake           | 4.2.3                      |
| Git             | 2.53.0                     |
| GLFW            | 3.4                        |

### build-essential

`build-essential` は、UbuntuでC/C++開発を行うための基本的なパッケージ群。

主に以下のようなツールが含まれる。

```text
build-essential

├── gcc
├── g++
├── make
└── その他、C/C++開発に必要な基本パッケージ
```

C++のコンパイルには `g++` を使用する。

---

### g++

C++のソースコードをコンパイルするためのコンパイラ。

例えば、

```text
main.cpp
   ↓
  g++
   ↓
実行可能ファイル
```

という形で、C++のソースコードをコンピュータが実行できる形式へ変換する。

このプロジェクトでは、CMakeからg++を利用してC++をビルドする。

---

### CMake

C++プロジェクトのビルド設定を管理するためのツール。

このプロジェクトでは、

```text
CMakeLists.txt
      ↓
CMake
      ↓
ビルドシステム
      ↓
g++ / gcc
      ↓
実行可能ファイル
```

という関係になる。

CMakeそのものがC++コンパイラというわけではなく、**「どのソースコードを、どのライブラリと組み合わせ、どのようにビルドするか」を設定する役割**を持つ。

このプロジェクトではC++だけでなく、GLADの `gl.c` をコンパイルするためC言語も使用する。

基本的なビルド方法：

```bash
cmake -S . -B build
cmake --build build
```

---

## OpenGL Environment

このプロジェクトでは、複数のソフトウェア・ライブラリがそれぞれ異なる役割を担当している。

大まかな関係は以下の通り。

```text
              ┌──────────────┐
              │   C++ code   │
              │   main.cpp   │
              └──────┬───────┘
                     │
                     ↓
              ┌──────────────┐
              │    GLFW      │
              │ Window/Input │
              │   Context    │
              └──────┬───────┘
                     │
                     ↓
              ┌──────────────┐
              │   OpenGL     │
              │ Graphics API │
              └──────┬───────┘
                     │
             ┌───────┴────────┐
             ↓                ↓
      ┌─────────────┐  ┌─────────────┐
      │    GLAD     │  │    GLSL     │
      │ OpenGL      │  │   Shader    │
      │ function    │  │   program   │
      │ loader      │  │             │
      └─────────────┘  └─────────────┘
```

---

### GLFW

GLFWは、OpenGLアプリケーションのための**ウィンドウ・入力・OpenGLコンテキスト管理ライブラリ**。

主な役割：

* ウィンドウの作成
* キーボード・マウス入力の処理
* OpenGLコンテキストの作成
* ウィンドウイベントの処理
* バッファの交換

例えば、

```cpp
GLFWwindow* window = glfwCreateWindow(
    800,
    600,
    "LearnOpenGL Study",
    nullptr,
    nullptr
);
```

によって800×600のウィンドウを作成できる。

**GLFWそのものがグラフィックスを描画するライブラリではない。**

GLFWは主に、

> 「OpenGLを使って描画するためのウィンドウや実行環境を用意する」

役割を担当する。

---

### OpenGL

OpenGLは、GPUを利用して2D・3Dグラフィックスを描画するための**グラフィックスAPI**。

例えば、

* 頂点データをGPUへ送る
* バッファを作成する
* シェーダーを使用する
* テクスチャを扱う
* 描画命令を発行する

といった処理を行う。

GLFWとは役割が異なる。

```text
GLFW

↓

「描画するためのウィンドウ・コンテキストを用意する」

OpenGL

↓

「その環境で実際にグラフィックス処理を行う」
```

現在の環境では、実行時に以下のOpenGLバージョンを確認している。

```text
OpenGL version: 4.1 (Compatibility Profile)
Mesa 26.0.8-1ubuntu0.3
```

---

### GLAD

GLADは、OpenGLの関数をプログラムから利用できるようにする**OpenGLローダー**。

OpenGLでは、実行時にOpenGLドライバから関数のアドレスを取得して利用する必要がある。

GLADはその処理を担当する。

```text
C++ program
     ↓
   GLAD
     ↓
OpenGL functions
     ↓
GPU driver
     ↓
GPU
```

このプロジェクトではGLAD 2を使用している。

```cpp
#include <glad/gl.h>
```

OpenGLコンテキストをGLFWで作成した後、

```cpp
gladLoadGL((GLADloadfunc)glfwGetProcAddress);
```

によってOpenGL関数をロードする。

その結果、例えば、

```cpp
glGetString(GL_VERSION)
```

をC++から呼び出してOpenGLのバージョンを取得できることを確認している。

そのため、

* GLFW = ウィンドウやコンテキスト
* GLAD = OpenGL関数を利用するためのローダー
* OpenGL = グラフィックスAPI

という関係になる。

---

### GLSL

GLSL（OpenGL Shading Language）は、OpenGLで使用する**シェーダーを記述するための言語**。

例えば、

```text
C++ program
    ↓
OpenGL API
    ↓
GPU
    ↓
GLSL shader
    ↓
画面上のピクセル
```

という形で利用する。

GLSLはC++とは別の言語であり、主にGPU上で実行される処理を記述する。

今後、

* Vertex Shader
* Fragment Shader
* 座標変換
* ライティング
* テクスチャ
* ポストプロセス

などを学習する。

---

## WSLg / Graphics Environment

WSLgは、WSL上でLinuxのGUIアプリケーションをWindows側に表示するための環境。

今回のプロジェクトでは、

```text
Windows
   │
   ├── GPU
   │
   └── WSLg
        │
        ↓
       WSL
        │
        ├── C++ program
        ├── GLFW
        └── OpenGL
```

という構成になっている。

WSL上で作成したGLFWウィンドウがWindows側に表示されることを確認済み。

また、WSL上のOpenGL環境からWindows側のGPUを利用できることも確認している。

現在の実行では、

```bash
GALLIUM_DRIVER=d3d12 ./build/learnopengl-study
```

を使用している。

---

## OpenGL Dependencies

現在導入済みの主なOpenGL関連環境：

| Library / API |                        Version | Purpose                     |
| ------------- | -----------------------------: | --------------------------- |
| GLFW          |                            3.4 | ウィンドウ作成、入力処理、OpenGLコンテキスト管理 |
| OpenGL        | 4.1 Compatibility Profileを確認済み | グラフィックスAPI                  |
| GLAD          |                         GLAD 2 | OpenGL APIの関数ローダー           |
| GLSL          |                OpenGL 4.1環境で利用 | GPU上で実行するシェーダー言語            |

### GLFWの導入

Ubuntuのパッケージマネージャから導入した。

```bash
sudo apt update
sudo apt install libglfw3-dev
```

`libglfw3-dev` は、GLFWを利用したプログラムを開発するためのヘッダーファイルや開発用ファイルを提供する。

また、GLFW本体の実行時ライブラリも依存関係として導入される。

---

### GLADの導入

GLAD 2でOpenGLのローダーを生成し、プロジェクト内に配置している。

```text
external/glad/

├── include/
│   ├── glad/
│   │   └── gl.h
│   └── KHR/
│       └── khrplatform.h
│
└── src/
    └── gl.c
```

`gl.c` はC言語のソースコードであるため、CMakeではC言語も有効にしている。

```cmake
project(learnopengl-study LANGUAGES C CXX)
```

---

## Project Structure

現在の構成：

```text
learnopengl-study/

├── .gitignore
├── README.md
├── CMakeLists.txt
│
├── src/
│   └── main.cpp
│
├── external/
│   └── glad/
│       ├── include/
│       │   ├── glad/
│       │   │   └── gl.h
│       │   └── KHR/
│       │       └── khrplatform.h
│       └── src/
│           └── gl.c
│
├── shaders/
│
└── build/
```

`build/` はCMakeによって生成されるため、Gitでは管理しない。

`shaders/` には今後、GLSLのVertex ShaderやFragment Shaderを配置する予定。

---

## Build System

CMakeを使用してプロジェクトをビルドする。

現在の `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.20)

project(learnopengl-study LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(learnopengl-study
    src/main.cpp
    external/glad/src/gl.c
)

target_include_directories(learnopengl-study
    PRIVATE
    external/glad/include
)

target_link_libraries(learnopengl-study
    PRIVATE
    glfw
)
```

### CMakeでのGLADの扱い

GLADはこのプロジェクト内の `external/glad/` に配置しているため、CMakeから直接ソースファイルを指定してビルドする。

```text
CMake
 │
 ├── src/main.cpp
 │       ↓
 │      C++
 │
 └── external/glad/src/gl.c
         ↓
        C
```

また、

```cmake
target_include_directories(learnopengl-study
    PRIVATE
    external/glad/include
)
```

によって、

```cpp
#include <glad/gl.h>
```

からGLADのヘッダーファイルを参照できるようにしている。

### ビルド

```bash
cmake -S . -B build
cmake --build build
```

実行：

```bash
./build/learnopengl-study
```

WSL上のOpenGL環境を明示して実行する場合：

```bash
GALLIUM_DRIVER=d3d12 ./build/learnopengl-study
```


---

## Learning Policy

このリポジトリでは、単にLearnOpenGLのコードをコピーして動かすのではなく、

* 何をインストールしているのか
* それぞれのライブラリが何を担当しているのか
* GLFWとOpenGLは何が違うのか
* GLADはなぜ必要なのか
* CMakeが何をしているのか
* コンパイラがどのようにプログラムをビルドしているのか
* CPU側のC++とGPU側のシェーダーがどのように連携するのか
* GPU上で実際に何が実行されているのか

を確認しながら学習する。

特に、

```text
C++ / CPU
    ↓
OpenGL API
    ↓
OpenGL driver
    ↓
GPU
    ↓
GLSL shader
    ↓
画面
```

という流れを意識して学習する。

外部ライブラリについても、可能な限り「何のために存在するのか」を理解した上で導入する。

---

## Current Progress

### Environment

* [x] WSL2 Ubuntu環境の構築
* [x] WSLgによるGUI表示の確認
* [x] `build-essential` の導入
* [x] g++の導入
* [x] CMakeの導入
* [x] Gitの設定
* [x] GitHub SSH認証の設定
* [x] Gitリポジトリの作成
* [x] `.gitignore` の設定
* [x] GitHubへのリモートリポジトリ設定

### GLFW / OpenGL

* [x] GLFW 3.4の導入
* [x] `CMakeLists.txt` の作成
* [x] CMakeによるプロジェクトの構成・ビルド確認
* [x] GLFWの初期化
* [x] GLFWによるウィンドウ生成
* [x] OpenGLコンテキストの作成
* [x] WSL上でウィンドウをWindows側に表示
* [x] GLAD 2の導入
* [x] GLADをCMakeプロジェクトに組み込み
* [x] GLADヘッダのinclude
* [x] GLADによるOpenGL関数のロード
* [x] `glGetString(GL_VERSION)` によるOpenGLバージョン取得
* [ ] 最初の三角形の描画

現在確認できているOpenGLバージョン：

```text
OpenGL version: 4.1 (Compatibility Profile)
Mesa 26.0.8-1ubuntu0.3
```

### Rendering

* [ ] `glClear()` による画面クリア
* [ ] GLSLシェーダーの学習
* [ ] Vertex Shader
* [ ] Fragment Shader
* [ ] VBO / VAO
* [ ] EBO
* [ ] テクスチャ
* [ ] 座標変換
* [ ] カメラ
* [ ] ライティング
* [ ] シャドウ
* [ ] ポストプロセス
* [ ] レンダリングパイプラインの理解

### Future Goals

* [ ] OpenGLでリアルタイムレンダラーを構築する
* [ ] GPU上で行われる処理を理解する
* [ ] GLSL / HLSLなどのシェーダープログラミングにつなげる
* [ ] レンダリング技術をUE / 3DGSなどの研究・制作へ応用する

---

## Current Status

現在は、

```text
C++
  ↓
CMake
  ↓
GLFW
  ↓
OpenGL Context
  ↓
GLAD
  ↓
OpenGL functions
  ↓
Mesa / WSLg
  ↓
Windows側のGPU
  ↓
Windows上にウィンドウ表示
```

までの環境構築が完了している。

また、

```cpp
glGetString(GL_VERSION)
```

を使用して、実際にOpenGL関数をC++から呼び出せることを確認している。

次の段階では、まず `glClear()` を使ってOpenGLによる画面描画を確認し、その後VBO・VAO・GLSLシェーダーを使用して**最初の三角形を描画する**。
