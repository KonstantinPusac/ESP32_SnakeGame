#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#define VRxPin 34 // Joystick X-axis
#define VRyPin 35 // Joystick Y-axis
#define SWPin 15  // Joystick button

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
    GameController(QObject *parent = nullptr) : QObject(parent) 
    {
        connect(&serial, &QSerialPort::readyRead, this, &GameController::readData);
        openPort();
    }
    ~GameController();


    // Joystick input methods
    void setJoystickDirection(JoystickDirection direction);
    void setButtonPressed(bool pressed);

    JoystickDirection getDirection() const { return m_direction; }
    bool isButtonPressed() const { return m_buttonPressed; }

    // Simulate keyboard input for testing
    void simulateKeyPress(int key);
    
signals:
    void directionChanged(JoystickDirection direction);
    void buttonPressed();
    void buttonReleased();

private:
    QSerialPort serial;
    QByteArray buffer;

    void openPort();
    void readData();
    void processLine(const QString &line);
    int extractValue(const QString &line, const QString &key);
    QString mapDirection(int x, int y);

    JoystickDirection m_direction = JoystickDirection::None;
    bool m_buttonPressed = false;
};

#endif // GAMECONTROLLER_H
