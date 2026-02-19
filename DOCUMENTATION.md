# Snake Game Qt Project Documentation

## Overview
This project is a modular Snake game written in C++ using the Qt framework. It is designed for joystick (ESP32) or keyboard input, and is structured for easy hardware integration.

---

## Main Components

### 1. MainSnake (Main Window)
- **File:** MainSnake.h / MainSnake.cpp
- **Purpose:** Central window managing all screens (menu, game, settings, stats).
- **Key Members:**
  - `QStackedWidget *m_stackedWidget` — Holds and switches between screens.
  - `GameController *m_controller` — Handles input (joystick/keyboard, serial or simulated).
  - `MainMenu *m_mainMenu` — Main menu screen.
  - `GameScreen *m_gameScreen` — Gameplay screen.
  - `SettingsScreen *m_settingsScreen` — Settings screen.
  - `StatsScreen *m_statsScreen` — Stats/score screen.
- **Slots:**
  - `showMenu()` — Show main menu.
  - `showGameScreen()` — Show and start the game.
  - `showSettingsScreen()` — Show settings.
  - `showStatsScreen()` — Show stats.

### 2. MainMenu
- **File:** MainMenu.h / MainMenu.cpp
- **Purpose:** Main menu UI with Play, Settings, Stats, Exit buttons.
- **Signals:**
  - `playClicked()`
  - `settingsClicked()`
  - `statsClicked()`
  - `exitClicked()`

### 3. GameScreen
- **File:** GameScreen.h / GameScreen.cpp
- **Purpose:** Handles the snake gameplay and rendering.
- **Key Methods:**
  - `startGame()` — Resets and starts the game.
  - `paintEvent()` — Draws the snake, food, and grid.
  - `keyPressEvent()` — Simulates joystick input with keyboard.
  - `onDirectionChanged(JoystickDirection)` — Handles input from GameController.
- **Signals:**
  - `backToMenu()`

### 4. SettingsScreen
- **File:** SettingsScreen.h / SettingsScreen.cpp
- **Purpose:** UI for adjusting volume and brightness.
- **Signals:**
  - `backToMenu()`
  - `volumeChanged(int)`
  - `brightnessChanged(int)`

### 5. StatsScreen
- **File:** StatsScreen.h / StatsScreen.cpp
- **Purpose:** Shows previous scores and stats.
- **Signals:**
  - `backToMenu()`

### 6. GameController
- **File:** GameController.h / GameController.cpp
- **Purpose:** Abstraction for joystick input (serial from ESP32, or simulated with keyboard for now).
- **Signals:**
  - `directionChanged(JoystickDirection)`
  - `buttonPressed()`
  - `buttonReleased()`
- **Methods:**
  - `simulateKeyPress(int key)` — For keyboard testing.
  - `setJoystickDirection(JoystickDirection)` — Updates direction and emits signal.
  - `setButtonPressed(bool)` — Updates button state and emits signal.
  - Serial port is opened and read automatically on construction.

### 7. SnakeGame

- **File:** SnakeGame.h / SnakeGame.cpp
- **Purpose:** Core snake game logic (movement, collision, food, score).
- **Signals:**
  - `snakeMoved()`
  - `foodEaten()`
  - `gameOver(int)`
  - `stateChanged(GameState)`
- **Key Methods:**
  - `start(int gridWidth, int gridHeight, int cellSize)`
  - `moveSnake(int dx, int dy)`
  - `reset()`
  - `generateFood()`

---

## Input Handling
- **Joystick:** Connected via ESP32 (serial, COM port). Receives X/Y/button data, mapped to directions.
- **Keyboard:** Arrow keys simulate joystick; Space for button press.

---

## Game Flow
1. **App starts:** Main menu is shown.
2. **Play:** Starts the game (snake appears, food is generated).
3. **Settings:** Adjust volume/brightness (values saved with QSettings).
4. **Stats:** View previous scores.
5. **Game Over:** Shown in game screen, return to menu with Back.

---

## Extending for ESP32
- GameController reads serial data from ESP32 and emits direction/button signals.
- For custom hardware, update serial port name and parsing logic in GameController.

---

## Build & Run
- Use CMake and Qt6 (see README.md for build instructions).
- Run with F5 in VSCode for debug output.

---

## File Structure
- `main.cpp` — Entry point
- `MainSnake.*` — Main window
- `MainMenu.*` — Menu UI
- `GameScreen.*` — Gameplay UI
- `SettingsScreen.*` — Settings UI
- `StatsScreen.*` — Stats UI
- `GameController.*` — Input abstraction
- `SnakeGame.*` — Game logic

---

## License
- See Qt licensing for framework. Project code is user-owned.
