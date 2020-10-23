cmake_minimum_required(VERSION 3.7)
project(Client)

set(EXECUTABLE Client)
set(SRC_DIR ./src)
set(INCLUDE_DIR ./include)
set(LIBRARY_DIR ./libraries)

# Setting resource path
add_definitions(-D_RESOURCES="${CMAKE_SOURCE_DIR}/resources/")
message(${CMAKE_SOURCE_DIR}/resources)

if (WIN32)
    # set(CMAKE_CXX_FLAGS "/Ox")
    include_directories(${EXECUTABLE}
            )
endif (WIN32)

set(THREADS_PREFER_PTHREAD_FLAD ON)
find_package(Threads REQUIRED)


include_directories(${EXECUTABLE}
        ${INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

file(GLOB SOURCE_FILES
        ${SRC_DIR}/*
        )

add_subdirectory(Common)

add_library(${EXECUTABLE} SHARED ${SOURCE_FILES})

set_target_properties(${EXECUTABLE} PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS ON
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

if (WIN32)
    target_link_libraries(${EXECUTABLE}
            )
endif (WIN32)

target_link_libraries(${EXECUTABLE}
        ${CMAKE_DL_LIBS}
        Common
        )