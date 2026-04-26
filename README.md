# 基于Qt6的音乐播放器

## 项目构建

### 1. 生成构建目录（只需执行一次，或当 CMake 配置变动时）

生成 `cmake-build-clang` 目录和 `compile_commands.json`，并配置好 Ninja+Clang+Qt6 的编译环境。

```bash
cmake -B cmake-build-clang -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH="C:/dev/Qt/qt-6.10/6.10.2/mingw_64" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

### 2. 编译项目

用 Ninja 和 Clang 编译你的项目，输出可执行文件（如 `cmake-build-clang/musicplayer.exe`）。

```bash
cmake --build cmake-build-clang
```

### 3. 运行项目

```bash
cmake-build-clang/musicplayer.exe
```
