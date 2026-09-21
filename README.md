# LearnOpenGL Study

[LearnOpenGL](https://learnopengl.com/) を用いたOpenGL・リアルタイムレンダリングの学習リポジトリ。

Visual StudioなどのIDEに依存した環境ではなく、**WSL上でCMakeを使ってビルドできる開発環境を自分で構築すること**を目的とする。

## Goals

* OpenGLの基本的な描画パイプラインを理解する
* C++からOpenGLを利用する方法を理解する
* シェーダー（GLSL）の仕組みを理解する
* CMakeによるC++プロジェクトのビルド方法を理解する
* 外部ライブラリの依存関係を把握し、自分で管理できるようにする
* 最終的に、リアルタイムレンダリングの仕組みを自分で実装・改造できるようにする

## Development Environment

### OS

* Windows 11
* WSL2
* Ubuntu
* WSLg

WSLgを利用して、WSL上で作成したOpenGLアプリケーションのウィンドウをWindows側に表示する。

### Development Tools

| Tool / Package  | Version / Description      |
| --------------- | -------------------------- |
| build-essential | UbuntuのC/C++開発に必要な基本パッケージ群 |
| g++             | 15.2.0                     |
| CMake           | 4.2.3                      |
| Git             | 2.53.0                     |

`build-essential` は、UbuntuでC/C++開発を行うための基本的なパッケージ群。

主に以下のようなツールが含まれる。

```text
build-essential
├── gcc
├── g++
├── make
└── その他、C/C++開発に必要な基本パッケージ
```

C++のコンパイルには `g++`、プロジェクトのビルド設定・生成には `CMake`、バージョン管理には `Git` を使用する。

### OpenGL Dependencies

今後、以下のライブラリを導入する。

| Library | Purpose                      |
| ------- | ---------------------------- |
| OpenGL  | グラフィックスAPI                   |
| GLFW    | ウィンドウ作成、入力処理、OpenGLコンテキストの作成 |
| GLAD    | OpenGL APIの関数をロードするためのローダー   |

## Project Structure

現在の構成：

```text
learnopengl-study/
├── .gitignore
├── README.md
├── src/
│   └── main.cpp
└── shaders/
```

今後、OpenGL関連のライブラリやビルドディレクトリを追加していく。

最終的には、例えば以下のような構成を想定している。

```text
learnopengl-study/
├── .gitignore
├── README.md
├── CMakeLists.txt
├── src/
│   └── main.cpp
├── shaders/
│   ├── vertex.glsl
│   └── fragment.glsl
├── external/
│   └── glad/
└── build/
```

## Build System

CMakeを使用してプロジェクトをビルドする。

基本的なビルド方法：

```bash
cmake -S . -B build
cmake --build build
```

`build/` 以下にはCMakeによって生成されるビルド関連ファイルが保存される。

## Git

Gitを使用してソースコードや学習内容の変更を管理する。

GitHubへの接続にはSSH認証を使用する。

```text
WSL
 ↓ SSH
GitHub
```

## .gitignore

ビルド時に生成されるファイルはGitで管理しない。

現在の `.gitignore`：

```gitignore
build/
```

`build/` はCMakeによって生成されるため、リポジトリには含めない。

これにより、ソースコードや設定ファイルと、環境ごとに生成されるビルド成果物を分離する。

## Learning Policy

このリポジトリでは、単にLearnOpenGLのコードをコピーして動かすのではなく、

* 何をインストールしているのか
* それぞれのライブラリが何を担当しているのか
* CMakeが何をしているのか
* コンパイラがどのようにプログラムをビルドしているのか
* CPU側のC++とGPU側のシェーダーがどのように連携するのか

を確認しながら学習する。

そのため、外部ライブラリやビルド環境についても、可能な限り依存関係を明示して管理する。

## Current Progress

* [x] WSL Ubuntu環境の構築
* [x] `build-essential` の導入
* [x] g++の導入
* [x] CMakeの導入
* [x] Gitの設定
* [x] GitHub SSH認証の設定
* [x] Gitリポジトリの作成
* [x] `.gitignore` の設定
* [x] GitHubへのリモートリポジトリ設定
* [ ] GLFWの導入
* [ ] GLADの導入
* [ ] CMakeによるOpenGLプロジェクトの構築
* [ ] GLFWによるウィンドウ生成
* [ ] OpenGLコンテキストの作成
* [ ] 最初の三角形の描画
* [ ] GLSLシェーダーの学習
* [ ] テクスチャ
* [ ] 座標変換
* [ ] ライティング
* [ ] シャドウ
* [ ] ポストプロセス
* [ ] レンダリングパイプラインの理解
