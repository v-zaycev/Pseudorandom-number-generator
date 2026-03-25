cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ExampleProject)

file(GLOB SOURCES "examples/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        /constexpr:steps2000000
        /constexpr:depth1024
    )
endif()

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Sources: ${SOURCES}")
message(STATUS "Headers: ${HEADERS}")