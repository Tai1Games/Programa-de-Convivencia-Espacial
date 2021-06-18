cmake_minimum_required(VERSION 2.8.11)
project(PCE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake/)


set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE "SourceFiles/*.cpp" "SourceFiles/*.h")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${PROJECT_NAME} 
                                ${SDL2_INCLUDE_DIRS} 
                                ${SDL2_IMAGE_INCLUDE_DIRS} 
                                ${SDL2_TTF_INCLUDE_DIRS} 
                                ${SDL2_NET_INCLUDE_DIRS} 
                                ${SDL2_MIXER_INCLUDE_DIRS}
                                "./json/single_include/nlohmann/"
                                )

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} 
                                ${SDL2_LIBRARIES} 
                                ${SDL2_IMAGE_LIBRARIES}
                                ${SDL2_TTF_LIBRARIES} 
                                ${SDL2_NET_LIBRARIES} 
                                ${SDL2_MIXER_LIBRARIES}) 