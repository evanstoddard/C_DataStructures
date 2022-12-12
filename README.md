# C_DataStructures
My implementation of basic data structures in C for learning purposes.

## Build
These data structures and not really meant to be used.  Ideally, sources would be brought directly into consuming project.  However, this project compiles to a static library.

```
cmake -S . build
cmake --build build
```

## Tests
All modules can be run with the `tests` target:
```
cmake -S . build
cd build && make tests
```