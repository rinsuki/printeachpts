cmake_minimum_required(VERSION 3.25)
project(printeachts)

find_package(PkgConfig)
pkg_check_modules(LIBAVFORMAT REQUIRED libavformat)
include_directories(${LIBAVFORMAT_INCLUDE_DIRS})

add_executable(printeachts main.c)

link_directories()
target_link_directories(printeachts PUBLIC ${LIBAVFORMAT_LIBRARY_DIRS})
target_link_libraries(printeachts ${LIBAVFORMAT_LIBRARIES})
