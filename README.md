# Beer Wanter

<!-- markdownlint-disable MD013 --><!-- Badges cannot be split up over lines, hence will break 80 characters per line -->

[![Check build](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_build.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_build.yaml)
[![check_links](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_links.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_links.yaml)
[![Check markdown](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_markdown.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_markdown.yaml)
[![Check spelling](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_spelling.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/check_spelling.yaml)
[![codecov](https://codecov.io/gh/richelbilderbeek/beer_wanter/branch/main/graph/badge.svg)](https://codecov.io/gh/richelbilderbeek/beer_wanter)
[![Create Zensical website](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/create_zensical_website.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/beer_wanter/actions/workflows/create_zensical_website.yaml)

<!-- markdownlint-enable MD013 -->

[Game](https://github.com/richelbilderbeek/Games) in which you have to click on the beer, written in C++ using Qt6.

[Play it in your browser](https://richelbilderbeek.github.io/beer_wanter/play/).

![BeerWanter menu v7.4](docs/screenshots/BeerWanterMenu_7_4.png)

![BeerWanter v7.4](docs/screenshots/BeerWanter_7_4.png)

## Building

The [build workflow](.github/workflows/build.yml) produces a Linux version
(artifact `BeerWanter-linux-x86_64`) and a WebAssembly version
(artifact `BeerWanter-wasm`), and puts the game on the website.

Desktop, which needs Qt6 and Boost.Test:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build
build/BeerWanterDesktop
```

WebAssembly, which needs Qt6 for WebAssembly, the desktop Qt6 of the same
version and the matching [Emscripten](https://doc.qt.io/qt-6/wasm.html):

```bash
/path/to/Qt/6.8.3/wasm_singlethread/bin/qt-cmake -S . -B build-wasm \
  -DCMAKE_BUILD_TYPE=Release -DQT_HOST_PATH=/path/to/Qt/6.8.3/gcc_64
cmake --build build-wasm
```

## External links

* [Richel Bilderbeek's games](https://github.com/richelbilderbeek/Games)
