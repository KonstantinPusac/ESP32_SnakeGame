# Snake Game Qt Project Documentation

## Overview
This project is a modular Snake game written in C++ using the Qt framework. It is designed to be controlled by a joystick (simulated with keyboard for now) and is structured for easy integration with an ESP32 microcontroller.

---

## Main Components

### 1. MainSnake (Main Window)
- **File:** MainSnake.h / MainSnake.cpp
- **Purpose:** Central window managing all screens (menu, game, settings).
- **Key Members:**
  - `QStackedWidget *m_stackedWidget` — Holds and switches between screens.
  - `GameController *m_controller` — Handles input (joystick/keyboard).
  - `MainMenu *m_mainMenu` — Main menu screen.
  - `GameScreen *m_gameScreen` — Gameplay screen.
  - `SettingsScreen *m_settingsScreen` — Settings screen.
- **Slots:**
  - `showMenu()` — Show main menu.
  - `showGameScreen()` — Show and start the game.
  - `showSettingsScreen()` — Show settings.

### 2. MainMenu
- **File:** MainMenu.h / MainMenu.cpp
- **Purpose:** Main menu UI with Play, Settings, Exit buttons.
- **Signals:**
  - `playClicked()`
  - `settingsClicked()`
  - `exitClicked()`

### 3. GameScreen
- **File:** GameScreen.h / GameScreen.cpp
- **Purpose:** Handles the snake gameplay and rendering.
- **Key Methods:**
  - `startGame()` — Resets and starts the game.
  - `paintEvent()` — Draws the snake, food, and grid.
  - `keyPressEvent()` — Simulates joystick input with keyboard.
- **Signals:**
  - `backToMenu()`

### 4. SettingsScreen
- **File:** SettingsScreen.h / SettingsScreen.cpp
- **Purpose:** UI for adjusting volume and brightness.
- **Signals:**
  - `backToMenu()`
  - `volumeChanged(int)`
  - `brightnessChanged(int)`

### 5. GameController
- **File:** GameController.h / GameController.cpp
- **Purpose:** Abstraction for joystick input (simulated with keyboard for now).
- **Signals:**
  - `directionChanged(JoystickDirection)`
  - `buttonPressed()`
  - `buttonReleased()`
- **Methods:**
  - `simulateKeyPress(int key)` — For keyboard testing.

### 6. SnakeGame
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
  - `generateFood()` — Now checks grid size to avoid exceptions.

---

## Input Handling
- **Joystick:** To be connected via ESP32 (future work).
- **Keyboard:** Arrow keys simulate joystick; Space/Enter for button press.

---

## Game Flow
1. **App starts:** Main menu is shown.
2. **Play:** Starts the game (snake appears, food is generated).
3. **Settings:** Adjust volume/brightness (values saved with QSettings).
4. **Game Over:** Shown in game screen, return to menu with Back.

---

## Extending for ESP32
- Replace or extend `GameController` to read joystick/button state from ESP32 (e.g., via serial or USB).
- Connect signals to update game state based on real hardware input.

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
- `GameController.*` — Input abstraction
- `SnakeGame.*` — Game logic

---

## License
- See Qt licensing for framework. Project code is user-owned.
