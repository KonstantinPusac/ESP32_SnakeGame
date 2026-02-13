# SnakeGame - Qt6 CMake Project

## Setup Complete ✅

Your Qt6 Snake Game project is now configured and ready for development.

## Build Configuration

- **Generator**: MinGW Makefiles
- **Compiler**: MinGW C++ (13.1.0) from Qt Tools
- **Qt Version**: Qt 6.10.1
- **CMAKE_PREFIX_PATH**: `C:/Qt/6.10.1/mingw_64`

## VSCode Tasks

You can use these tasks from the VSCode command palette (`Ctrl+Shift+P`):

1. **CMake Configure** - Configure the CMake project
2. **Build Debug** (Default) - Compile the project  
3. **Run SnakeGame** - Execute the built application
4. **Clean** - Remove build directory

### Quick Build
Press `Ctrl+Shift+B` to build the project (default task).

### Debug
Press `F5` to start debugging with GDB.

## Manual Commands

If you prefer terminal commands:

```powershell
# Configure
cmake -S . -B build -G "MinGW Makefiles" `
  -DCMAKE_PREFIX_PATH=C:/Qt/6.10.1/mingw_64 `
  -DCMAKE_CXX_COMPILER=C:/Qt/Tools/mingw1310_64/bin/g++.exe `
  -DCMAKE_MAKE_PROGRAM=C:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe

# Build
cmake --build build --config Debug

# Run
build/SnakeGame.exe
```

## Project Structure

- `main.cpp` - Application entry point
- `MainSnake.h/cpp` - Main window class
- `MainSnake.ui` - Qt UI file (designer)
- `CMakeLists.txt` - CMake configuration
- `build/` - Build output directory (auto-generated)

## Next Steps

1. **Edit the UI** - Open `MainSnake.ui` in the Qt Designer
2. **Add Game Logic** - Edit `MainSnake.cpp` to implement the Snake game
3. **Build & Test** - Use `Ctrl+Shift+B` to build
4. **Debug** - Press `F5` to debug with breakpoints
