cmake_minimum_required(VERSION 3.0.0)
project(Lab7Task1 VERSION 0.1.0)

include(CTest)
find_package(OpenCV REQUIRED)

enable_testing()

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(Lab7Task1 main.cpp panoramic_utils.cpp)
target_include_directories(Lab7Task1 PUBLIC header/)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
