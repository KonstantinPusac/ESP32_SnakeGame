#include "GameController.h"

GameController::GameController(QObject *parent): QObject(parent) {}

GameController::~GameController() {}

void GameController::setJoystickDirection(JoystickDirection direction)
{
    if (m_direction != direction) 
    {
        m_direction = direction;
        emit directionChanged(direction);
    }
}

void GameController::setButtonPressed(bool pressed)
{
    if (m_buttonPressed != pressed) 
    {
        m_buttonPressed = pressed;
        if (pressed) {
            emit buttonPressed();
        } else {
            emit buttonReleased();
        }
    }
}

void GameController::simulateKeyPress(int key)
{
    // For testing without ESP32
    // Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_Space
    switch (key) {
        case Qt::Key_Up:
            setJoystickDirection(JoystickDirection::Up);
            break;
        case Qt::Key_Down:
            setJoystickDirection(JoystickDirection::Down);
            break;
        case Qt::Key_Left:
            setJoystickDirection(JoystickDirection::Left);
            break;
        case Qt::Key_Right:
            setJoystickDirection(JoystickDirection::Right);
            break;
        case Qt::Key_Space:
            setButtonPressed(true);
            break;
        default:
            setJoystickDirection(JoystickDirection::None);
            break;
    }
}
