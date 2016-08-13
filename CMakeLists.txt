project(TSP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_FILES main.cpp tspGreedy.cpp inputOutputConversion.cpp tspOpt2.cpp)
set(FILES)
add_executable(TSP ${SOURCE_FILES})
