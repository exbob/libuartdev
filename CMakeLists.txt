cmake_minimum_required(VERSION 3.15)

# 设置一些变量
# ----------------------------------------------------

# 定义项目名称，项目名称就是库的名称
set(LIB_NAME uartdev)

# 设置版本号，分为三段：MAJOR.MINOR.PATCH
set(MAJOR 0)  # 添加或者修改一些API
set(MINOR 1)  # API没有变化，修改了一些功能
set(PATCH 0)  # API没有变化，修复了一些缺陷

# 显示项目信息和版本号
message(STATUS "Message : lib${LIB_NAME} ${MAJOR}.${MINOR}.${PATCH}")

# 设置链接库依赖的源文件
# 源文件都放在 src 目录下，在 lib${LIB_NAME}_src 变量中列出
set(lib${LIB_NAME}_src src/libuartdev.c)
# 显示库和依赖的源文件
message(STATUS "Message : lib${LIB_NAME} : ${lib${LIB_NAME}_src}")

# 设置公共头文件
# 头文件都放在 include 目录下，调用库函数需要包括的头文件叫做公共头文件，在 lib${LIB_NAME}_inc 变量中列出
set(lib${LIB_NAME}_inc include/libuartdev.h)

# ----------------------------------------------------

# 新建项目
project(lib${LIB_NAME} VERSION ${MAJOR}.${MINOR}.${PATCH})

# 生成动态库
add_library(${LIB_NAME} SHARED ${lib${LIB_NAME}_src})

# 设置库文件的版本号
set_target_properties(${LIB_NAME} PROPERTIES 
                        VERSION ${PROJECT_VERSION} # 动态库的版本
                        SOVERSION ${PROJECT_VERSION_MAJOR} # API的版本
                        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output # 设置库文件的输出路径
                        PUBLIC_HEADER ${lib${LIB_NAME}_inc} # 设置公共头文件
)

# 设置头文件搜索路径
target_include_directories(${LIB_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 如果是 Debug 版本，就添加 __DEBUG__ 宏定义，添加 -Wall 编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Message : Add Debug")
    target_compile_definitions(${LIB_NAME} PRIVATE "__DEBUG__")
    target_compile_options(${LIB_NAME} PRIVATE -Wall)
endif()

# 安装
install(TARGETS ${LIB_NAME} 
        LIBRARY DESTINATION lib   # 库文件安装到 ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION include # 头文件安装到 ${CMAKE_INSTALL_PREFIX}/include
        )

# 添加 example
# 编译 example 下的文件
add_subdirectory(example)