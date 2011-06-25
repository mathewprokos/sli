file(GLOB ALL_SOURCE *.c)

include_directories(${SLI_SOURCE_DIR}/tinyscheme)
link_directories(${SLI_SOURCE_DIR}/tinyscheme)

add_executable(sli ${ALL_SOURCE})
target_link_libraries(sli tinyscheme)
