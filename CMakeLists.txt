cmake_minimum_required(VERSION 3.0.0)
project(PixelFormat VERSION 0.1.0)

include(CTest)
enable_testing()

list(APPEND INC Include)

list(APPEND CSRC Source/main.c)
list(APPEND CSRC Source/bitmap.c)
list(APPEND CSRC Source/image.c)


# list(APPEND LIBS z)

add_executable(${CMAKE_PROJECT_NAME} ${CSRC})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${INC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
