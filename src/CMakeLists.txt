PROJECT(hello_prog)

INCLUDE_DIRECTORIES(${exploration_SOURCE_DIR}/include)

ADD_EXECUTABLE(prog main.cxx)

TARGET_LINK_LIBRARIES(prog PRIVATE glad glfw glm stb_image)
