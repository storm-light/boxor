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

Temporarily, macOS users need to install header files for the SDL2 libraries. This can be done with brew:

```
brew install sdl2
brew install sdl2_ttf
brew install sdl2_image
```

