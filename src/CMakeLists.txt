# Project
project(datastructures)

# Compiler flags
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wnull-dereference
    -Wstrict-aliasing=3
    -Wduplicated-cond
    -Wtype-limits
    -Wsign-compare
    -Waggressive-loop-optimizations
    -Wmissing-field-initializers
    -Wcast-align
    -Wpointer-arith
    -Wcast-qual
    -Wimplicit-fallthrough=2
    -fsanitize=undefined
)

# Sources
set(datastructures_SOURCES
    linkedlist.c
)

# Headers
set(datasstructures_HEADERS
    linkedlist.h
)

# Include Paths

# Target
add_library(datastructures
    ${datastructures_SOURCES}
)