# 设置可执行文件的名称
set(program uartecho)
# 新建一个可执行文件
add_executable(${program} uartecho.c)

# 设置头文件搜索路径
target_include_directories(${program} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 设置链接库搜索路径
target_link_directories(${program} PRIVATE ${PROJECT_BINARY_DIR}/output)
target_link_libraries(${program} PRIVATE uartdev)

# 如果是 Debug 版本，就添加 __DEBUG__ 宏定义，添加 -Wall 编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${program} PRIVATE "__DEBUG__")
    target_compile_options(${program} PRIVATE -Wall)
endif()

# 设置输出路径
set_target_properties(${program} PROPERTIES 
                        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output # 设置可执行文件的输出路径
)