# libuartdev

## 基本用法

执行 `./build.sh` 会自动编译生成 Debug 和 Release 两个版本，生成的链接库和可执行文件位于 Debug/Release 下的 output 目录下。可以执行 `cmake --install Release` 命令，将 Release 版本的动态库和头文件安装到 `/usr/local/` 下的 lib 和 include 目录下。可以用 `--prefix` 选项改变安装路径，例如 `cmake --install Release --prefix ./install` 。

如果是交叉编译，可以用 `${CC}` 环境变量设置交叉编译工具链，可以将脚本里的 `enable_download` 设为 1 ，编译后自动下载到目标板的相应目录。

## License

Copyright (C) 2024 Lishaocheng <https://shaocheng.li> 

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3 as published by the Free Software Foundation.
