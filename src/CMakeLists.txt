PROJECT(hello_prog)

ADD_EXECUTABLE(prog main.cxx camera.hpp shader.hpp mesh.hpp model.hpp geometry.h simplemesh.hpp triangleSoup.cpp triangleSoup.h geometry.cpp)

TARGET_INCLUDE_DIRECTORIES(prog PRIVATE 
  ${exploration_SOURCE_DIR}/include
  ${exploration_SOURCE_DIR}/src
)

TARGET_LINK_LIBRARIES(prog PRIVATE glad assimp glfw glm stb_image)

set_target_properties(prog
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    MESSAGE("MSCV detected")
    TARGET_COMPILE_OPTIONS(prog PRIVATE /W3 /WX)
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    MESSAGE("GCC detected")
    TARGET_COMPILE_OPTIONS(prog PRIVATE -Wall -Werror) # -pedantic -Wextra
ELSEIF()
    MESSAGE(FATAL_ERROR "Neither GCC nor MSVC detected!")
ENDIF()
