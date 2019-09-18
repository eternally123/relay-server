cmake_minimum_required(VERSION 2.8)
project(demo)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)  #指明最后可执行文件位置在bin文件夹

include_directories(${PROJECT_SOURCE_DIR}/include)  #指明头文件目录在include目录中。
# 此时，cpp文件中如果要引用头文件，直接写入include中的文件名即可。因为已经通过include_directories(../include)指明了头文件存放位置，无需在写头文件相对与cpp文件的相对路径。（例如，include中有一个tree.hpp文件。在src的main.cpp中，直接include"tree.hpp"即可找到头文件。而无需使用include"../include/tree.hpp"）

aux_source_directory(src/. SRC_LIST)


add_executable(
        main
        ${SRC_LIST}
        include/relayServerHeader.hpp) #编译所用到的文件
#
#add_executable(
#
#) #编译所用到的文件
