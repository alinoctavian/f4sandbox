set(PROJ Common)

set(SRC_DIR ./src)
set(INCLUDE_DIR ./include)
set(LIB_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/libs)

file(GLOB SOURCE_FILES
        ${SRC_DIR}/*
        ${SRC_DIR}/GamePtr.cpp
        )

add_library (${PROJ} STATIC ${SOURCE_FILES})

include_directories(${PROJ} ${INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories (${PROJ} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/*)


target_link_libraries(${PROJ}
        ${CMAKE_DL_LIBS}
        ${LIB_DIR}/detours.lib
        )