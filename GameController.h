#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

enum class JoystickDirection {
    None,
    Up,
    Down,
    Left,
    Right
};

class GameController : public QObject {
    Q_OBJECT

public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController();

    // Joystick input methods (will be replaced with actual serial/USB input from ESP32)
    void setJoystickDirection(JoystickDirection direction);
    void setButtonPressed(bool pressed);

    JoystickDirection getDirection() const { return m_direction; }
    bool isButtonPressed() const { return m_buttonPressed; }

    // Simulate keyboard input for testing (before ESP32 arrives)
    void simulateKeyPress(int key);

signals:
    void directionChanged(JoystickDirection direction);
    void buttonPressed();
    void buttonReleased();

private:
    JoystickDirection m_direction = JoystickDirection::None;
    bool m_buttonPressed = false;
};

#endif // GAMECONTROLLER_H
