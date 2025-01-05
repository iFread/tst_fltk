 cmake_minimum_required(VERSION 3.5)
 project(LIBWidgets)
 set(CMAKE_CXX_STANDARD 11)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O0 -g")

  include_directories("${PROJECT_SOURCE_DIR}/inc")

   #include_directories("${PROJECT_SOURCE_DIR}/lib/inc")
 

 file(GLOB LIB_SOURCE "${PROJECT_SOURCE_DIR}/src/*.cpp")
 file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/inc/*.h")
 
  
 #add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE})
 add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE} ${HEADERS})
 target_link_libraries(${PROJECT_NAME} fltk)
 
 
