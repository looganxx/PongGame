cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "PongGame")
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/SFML)
set(SRC_PONG_GAME_PATH ${CMAKE_SOURCE_DIR})
set(DATA_PATH ${SRC_PONG_GAME_PATH}/Data)

file(GLOB_RECURSE SRC ${SRC_PONG_GAME_PATH}/*.cpp ${SRC_PONG_GAME_PATH}/*.h)
file(GLOB_RECURSE DATA ${DATA_PONG_GAME_PATH}/*)

set(SRCS ${SRC})
set(DATA_FOLDER ${DATA})

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-system)
target_link_libraries(${PROJECT_NAME} sfml-audio)

configure_file(Data/arial.ttf Data/arial.ttf COPYONLY)
configure_file(Data/background.png Data/background.png COPYONLY)
configure_file(Data/ball.png Data/ball.png COPYONLY)
configure_file(Data/hit.wav Data/hit.wav COPYONLY)
configure_file(Data/pad.png Data/pad.png COPYONLY)
