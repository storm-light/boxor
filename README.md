# B0X0R

## Use

From the root of the project, the executable can be run with ./v1.1.3/build/source/BOXOR

This project uses CMake, so to build from scratch, remove and create a new build dir:

```
rm -rf build
mkdir build
cd build
cmake ..
make install
```

## Dependencies

The executable will look for SDL2 and SDL2_ttf binaries in /Library/Frameworks before running. SDL2 frameworks also require dependencies usually found in /usr/lib

