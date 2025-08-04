# About

I am having fun building a software rasterizer from scratch... with only a little help from raylib (for creating a window and drawing pixels)

# Dependencies

1. This project uses [raylib](https://raylib.com) for window management and pixel drawing. Raylib is included in the `libs` directory. You can visit [raylib's GitHub](https://github.com/raysan5/raylib) to install the dependencies for raylib.

2. This project uses [Make](https://www.gnu.org/software/make/) for building.

# Building

From the root directory, run:

```bash
make
```

# Running

After building, you can run the software rasterizer with:

```bash
./build/main
```

Or if you are on Windows:

```bash
build\main.exe
```

# TODO
Add custom triangle rendering and a z-buffer