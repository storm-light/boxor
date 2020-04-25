# B0X0R

## Use

After cloning this repo, the executable can be run with ./v1.1.3/build/source/BOXOR

This project uses CMake, so to build from scratch, remove and create a new build dir:

```
rm -rf build
mkdir build
cd build
cmake ..
make install
```

## Dependencies

The executable will look for SDL2 and SDL2_ttf binaries in /Library/Frameworks before running.

