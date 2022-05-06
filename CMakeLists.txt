cmake_minimum_required(VERSION 3.14)

# ---- Project ----

project(ccfake VERSION 1.0.0)

set(TARGET_LIB ${PROJECT_NAME})

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Options for project ----

option(SHARED      "Generate shared library otherwise static" OFF)
option(EXECUTABLE  "Generate executable target" OFF)
option(ENABLE_TEST "Build tests" ON)
option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(ENABLE_ASON "Enable AddressSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)

# ---- ASON & TSON config ----
if(ENABLE_ASON)
    message(STATUS "AddressSanitizer enabled")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address") 
endif()

if(ENABLE_TSAN)
    message(STATUS "ThreadSanitizer enabled")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1 -fsanitize=thread -fno-omit-frame-pointer -fPIC -fPIE")
endif()


# ---- Using CPM to add dependencies for project ----

include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)

# ---- Add source folder for project ----

add_subdirectory("src")

# ---- Add test for project ----

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
