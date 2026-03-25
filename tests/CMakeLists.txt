cmake_minimum_required(VERSION 3.15)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF)

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# Создаём тест
add_executable(test_generators "test_constructors.cpp" "test_consistency.cpp" "test_discard.cpp")

# Подключаем библиотеки
target_link_libraries(test_generators PRIVATE gtest_main)

# Указываем где искать ваши заголовки (просто папка include)
target_include_directories(test_generators PRIVATE ${CMAKE_SOURCE_DIR}/include)

# C++23
set_target_properties(test_generators PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

# Для MSVC увеличиваем лимиты constexpr (если нужно)
if(MSVC)
    target_compile_options(test_generators PRIVATE 
        /constexpr:steps2000000
        /constexpr:depth1024
    )
endif()