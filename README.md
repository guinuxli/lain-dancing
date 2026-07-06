# Lain Dancing

A simple Raylib joke that I made using C.

## Dependencies

You need Raylib on your machine for this to work properly.

If you're using Linux, just install it using your package manager.
Example for Arch-based distros:
sudo pacman -S raylib

If you're on Windows, you need to download the Raylib library from the
official Raylib GitHub page (grab the prebuilt package matching your
compiler, e.g. `raylib-5.x_win64_mingw-w64.zip` for MinGW), then extract
it so you have an `include/` and `lib/` folder available to the project.
You'll also need MinGW-w64 (with `gcc` and `mingw32-make`) installed and
on your PATH — MSYS2 (https://www.msys2.org/) is the easiest way to get this.

## Installation

This project was originally made on Linux, but it can also be compiled to
run on Windows since Raylib is cross-platform.

For Linux:
```
git clone https://github.com/guinuxli/lain-dancing.git
cd lain-dancing
make
```

For Windows:
```
git clone https://github.com/guinuxli/lain-dancing.git
cd lain-dancing
mingw32-make
```

> Make sure Raylib's `include` and `lib` folders (from the prebuilt package
> you downloaded) are placed inside the project, matching the paths expected
> by the Makefile, before running `mingw32-make`.

## Usage

After compiling you should be able to run it just by using `./lain` (or
`lain.exe` on Windows), or with `make run` / `mingw32-make run`.