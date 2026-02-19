# SnakeGame - Qt6 CMake Project

## Overview
This is a modular Snake game written in C++ using the Qt6 framework. It supports joystick input via ESP32 (serial) or keyboard simulation, and is structured for easy hardware integration and extension.

## Build Configuration

- **Generator:** Ninja (or MinGW Makefiles)
- **Compiler:** MinGW C++ (13.1.0) from Qt Tools
- **Qt Version:** Qt 6.10.1
- **CMAKE_PREFIX_PATH:** `C:/Qt/6.10.1/mingw_64`

## VSCode Tasks

You can use these tasks from the VSCode command palette (`Ctrl+Shift+P`):

1. **CMake Configure** - Configure the CMake project
2. **CMake Build** - Compile the project
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
cmake -S . -B build -G "Ninja" -DCMAKE_PREFIX_PATH=C:/Qt/6.10.1/mingw_64

# Build
cmake --build build --config Debug

# Run
build/SnakeGame.exe
```

## Project Structure

- `main.cpp` — Application entry point
- `MainSnake.*` — Main window (manages all screens)
- `MainMenu.*` — Main menu UI
- `GameScreen.*` — Gameplay UI and logic
- `SettingsScreen.*` — Settings UI
- `StatsScreen.*` — Stats/scores UI
- `GameController.*` — Handles joystick/keyboard input
- `SnakeGame.*` — Core game logic
- `CMakeLists.txt` — CMake configuration
- `build/` — Build output directory (auto-generated)

## Input Handling

- **Joystick:** Connects via ESP32 (serial COM port). GameController parses X/Y/button data and emits direction signals.
- **Keyboard:** Arrow keys simulate joystick; Space for button press.

## How to Play

1. **Start the app:** Main menu is shown.
2. **Play:** Starts the game (snake appears, food is generated).
3. **Settings:** Adjust volume/brightness (values saved with QSettings).
4. **Stats:** View previous scores.
5. **Game Over:** Shown in game screen, return to menu with Back.

## Extending for ESP32

- GameController reads serial data from ESP32 and emits direction/button signals.
- For custom hardware, update serial port name and parsing logic in GameController.

## License

See Qt licensing for framework. Project code is user-owned.
