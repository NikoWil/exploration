PROJECT(hello_prog)

ADD_EXECUTABLE(prog main.cxx camera.hpp shader.hpp mesh.hpp model.hpp plane.hpp simplemesh.hpp triangleSoup.cpp triangleSoup.h)

TARGET_INCLUDE_DIRECTORIES(prog PRIVATE 
  ${exploration_SOURCE_DIR}/include
  #${exploration_SOURCE_DIR}/src
)

TARGET_LINK_LIBRARIES(prog PRIVATE assimp glad glfw glm stb_image)

set_target_properties(prog
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
