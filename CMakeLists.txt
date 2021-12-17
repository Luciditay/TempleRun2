cmake_minimum_required(VERSION 3.16)

project(templeRun)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(StbImage REQUIRED)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${assimp_INCLUDE_DIR} $(SDL_TTF_INCLUDE_DIR) ${StbImage_INCLUDE_DIR} glimac/include lib/include src src/UI/include src/Render/include src/Game/include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${SDLTTF_LIBRARY} ${assimp_LIBRARIES} ${StbImage_LIBRARY} )

add_subdirectory(glimac)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})

file(COPY src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/scores DESTINATION ${CMAKE_CURRENT_BINARY_DIR})