# B0X0R

## Use

This project utilizes frameworks; it can only be used by macOS users. To create a working executable, at the root of the project, run:   

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

