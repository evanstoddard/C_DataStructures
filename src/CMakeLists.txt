# Project
project(datastructures)

# Compiler flags
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wnull-dereference
    -Wtype-limits
    -Wsign-compare
    -Wmissing-field-initializers
    -Wcast-align
    -Wpointer-arith
    -Wcast-qual
	-Wno-newline-eof
)

# Sources
set(datastructures_SOURCES
    linkedlist.c
	doubleylinkedlist.c
)

# Headers
set(datasstructures_HEADERS
    linkedlist.h
	doubleylinkedlist.h
)

# Include Paths

# Target
add_library(datastructures STATIC
	${datastructures_SOURCES}
)