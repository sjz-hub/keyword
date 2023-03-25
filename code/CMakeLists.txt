cmake_minimum_required(VERSION 3.23)
project(acauto)

set(CMAKE_CXX_STANDARD 11)

add_executable(acauto main.cpp acNode.cpp acNode.h closeness.cpp closeness.h LinkList.cpp LinkList.h Hash.cpp Hash.h pageRank.cpp pageRank.h pageRankList.cpp pageRankList.h LinkMatrix.cpp LinkMatrix.h LinkThreeDimMatrix.cpp LinkThreeDimMatrix.h ELL.cpp ELL.h)
