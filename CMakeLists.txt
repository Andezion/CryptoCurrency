cmake_minimum_required(VERSION 3.10)
project(CodeForce)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED COMPONENTS core base gl net)
include(${wxWidgets_USE_FILE})
include_directories(${wxWidgets_INCLUDE_DIRS})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_executable(CodeForce main.cpp)

target_link_libraries(CodeForce
        ${wxWidgets_LIBRARIES}
        ${CURL_LIBRARIES}
)
