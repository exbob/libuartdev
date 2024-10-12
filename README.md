# libuartdev

## 基本用法

执行 `./build.sh` 会自动编译生成 Debug 和 Release 两个版本，生成的链接库和可执行文件位于 Debug/Release 下的 output 目录下。可以执行 `cmake --install Release` 命令，将 Release 版本的动态库和头文件安装到 `/usr/local/` 下的 lib 和 include 目录下。可以用 `--prefix` 选项改变安装路径，例如 `cmake --install Release --prefix ./install` 。

如果是交叉编译，可以用 `${CC}` 环境变量设置交叉编译工具链，可以将脚本里的 `enable_download` 设为 1 ，编译后自动下载到目标板的相应目录。

## 串口与终端

这里所说的串口（Serial port），是指 RS-232 及其衍生接口标准。这是一种非常古老的接口标准，最早是 1960 年由美国电子工业联盟（EIA）制定， 用于电传打字机与计算机的连接。

当时计算机才发明出来不久，面临人机交互的问题，而电传打字机已经存在很久，用于收发电报：

- 将接收到的电信号转化为机械运动驱动打印机将字母打印到纸上。
- 将在键盘上的输入信号编码转换为电信号发送出去。

于是，将电传打字机与计算机用专用电缆（例如 RS-232 ）连接起来，成为了计算机的终端（Terminal），用于计算机的输入和输出。电传打字机的英文是 [Teletype](https://en.wikipedia.org/wiki/Teletype_Corporation) ，这是也是一家公司的名字，因为生产电传打印机太出名，从而成为代名词。在类 Unix 系统中，tty 就是此单词的缩写。其中最著名的是 [Teletype Model 33](https://en.wikipedia.org/wiki/Teletype_Model_33#Historical_impact)，历史影响颇深。下面是用 Teletype Model 33 连接 PiDP-11 计算机的视频：

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/DRzpJyOc3bc/0.jpg)](https://www.youtube.com/watch?v=DRzpJyOc3bc)

后来，随着 CRT 显示器的发明，终端（Terminal）功能由硬件逐步变成了一种叫做虚拟终端的软件，电传打字机退出了历史舞台，但是它的很多特性对类 Unix 操作系统的影响一直持续至今，例如：

- 终端的设备文件叫做 tty ，就是一种虚拟终端。
- 逐行依次输出文本，因为电传打字机是无法修改已经打印到纸上的字符的。
- 各种 shell 都提供命令提示符，用来区分需要区分用户的输入和机器的输出，因为电传打字机是黑白，只能通过命令提示符来区分。
- 回车和换行符是两个，因为电传打字机切换行时是需要先将打字头回到开头，然后纸筒滚动一行。
- 由于电传打字机的键盘是计算机的唯一的输入端，因此通过 ctrl 加字符打印出一些特殊字符，以给正在运行程序发送信号。
- 多数库函数的打印日志均采用 print 单词，原因在于，在当时看，就是物理意义上打印到纸上。

但是 RS-232 串口并没有消失，还衍生出 TTL，RS-485 和 RS-422 等接口标准，而很多嵌入式设备，依然使用串口作为调试终端。

## 串口编程

在 Linux 下使用 C 语言进行串口编程，通常是调用 [GNU C Library](https://www.gnu.org/software/libc/) 提供的 [Low-Level Terminal Interface](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Terminal-Interface.html?spm=wolai.workspace.0.0.7bf85fdcxzdAL7)。


## License

Copyright (C) 2024 Lishaocheng <https://shaocheng.li> 

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3 as published by the Free Software Foundation.
