#project(Hello_prog)

# All sources that also need to be tested in unit tests go into a static library
#ADD_LIBRARY(hello_lib STATIC hello.cpp hello.h)
#TARGET_INCLUDE_DIRECTORIES(hello_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
#ADD_EXECUTABLE(prog main.cpp)
#TARGET_LINK_LIBRARIES(prog PRIVATE hello_lib)
 
PROJECT(hello_prog)

INCLUDE_DIRECTORIES(${exploration_SOURCE_DIR}/thirdparty/glad/include/ ${exploration_SOURCE_DIR}/include)
LINK_DIRECTORIES(${exploration_SOURCE_DIR}/thirdparty/glad/src/)

ADD_EXECUTABLE(prog main.cxx)

#FIND_LIBRARY(GLAD_LIBRARY glad HINTS ${exploration_SOURCE_DIR}/thirdparty/glad)
TARGET_LINK_LIBRARIES(prog glfw glad_lib)
