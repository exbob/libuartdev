#!/bin/sh

echo "Clean..."
if [ -d ./Debug ]; then
    echo "-- remove Debug"
    rm -rf Debug
fi
if [ -d ./Release ]; then
    echo "-- remove Release"
    rm -rf Release    
fi
echo " "

echo "Build Debug ..."
cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug
cmake --build Debug
echo " "

echo "Build Release ..."
cmake -S . -B Release -DCMAKE_BUILD_TYPE=Release
cmake --build Release
echo " "

# 如果是交叉编译，需要将生成的文件下载到目标板上调试
enable_download=0

if [ ${enable_download} -eq 1 ]; then
    echo "Download ..."
    LOCAL="Release"
    REMOTE="root@192.168.108.150"

    cd ${LOCAL}
    scp -p ./output/libuartdev.so.0.1.0 ${REMOTE}:/usr/local/lib/
    scp -p ./output/uartecho ${REMOTE}:/home/root/
    cd -
fi
