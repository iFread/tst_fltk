cmake_minimum_required(VERSION 3.5)

project(test_fltk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wpedantic -pedantic-errors -Wall -O0  -g ")

include_directories("${PROJECT_SOURCE_DIR}/inc")
 include_directories("${PROJECT_SOURCE_DIR}/lib/inc")
 

 file(GLOB CPP1 "${PROJECT_SOURCE_DIR}/src/*.cpp")
 file(GLOB CPP2 "${PROJECT_SOURCE_DIR}/lib/src/*.cpp")
  file(GLOB CHP1 "${PROJECT_SOURCE_DIR}/inc/*.h")
 file(GLOB HPP2 "${PROJECT_SOURCE_DIR}/lib/**/*.h")

 add_executable(${PROJECT_NAME} main.cpp ${CPP1} ${CHP1} ${HPP2} )
 
# target_include_directories(${PROJECT_NAME} PUBLIC
 #                         "${PROJECT_SOURCE_DIR}/lib/inc")
 add_subdirectory(lib)
 target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/lib/inc")
  target_link_libraries(${PROJECT_NAME} LIBWidgets)
  #target_link_libraries(${PROJECT_NAME} GraphWidget)

 
#  add_executable(${PROJECT_NAME} ${LIB_SOURSE}  main.cpp )
  target_link_libraries(${PROJECT_NAME} fltk)
