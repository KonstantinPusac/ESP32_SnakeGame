// Always include your own header first
#include "GameController.h"
#include <QSerialPortInfo>
#include <QDebug>

GameController::~GameController() {}

void GameController::openPort()
{
    serial.setPortName("COM9");
    serial.setBaudRate(QSerialPort::Baud115200);
    
    if (!serial.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();
    } else {
        qDebug() << "Serial port opened successfully.";
    }
}

void GameController::readData()
{
    buffer.append(serial.readAll());

    while (buffer.contains('\n')) {
        int newlineIndex = buffer.indexOf('\n');
        QString line = QString::fromUtf8(buffer.left(newlineIndex).trimmed());
        buffer.remove(0, newlineIndex + 1);
        processLine(line);
    }
}

void GameController::processLine(const QString &line)
{
    if (!line.contains("X:"))
        return;

    qDebug() << "Received line:" << line;

    int x = extractValue(line, "X:");
    int y = extractValue(line, "Y:");

    QString direction = mapDirection(x, y);

    qDebug() << "Parsed-> X:" << x << " Y:" << y << " Direction:" << direction;
}

int GameController::extractValue(const QString &line, const QString &key)
{
    int startIndex = line.indexOf(key);
    if (startIndex == -1)
        return 0;

    startIndex += key.length();
    int endIndex = line.indexOf('|', startIndex);
    if (endIndex == -1)
        endIndex = line.length();

    bool ok;
    QString value = line.mid(startIndex, endIndex - startIndex).trimmed();
    return value.toInt(&ok) ? value.toInt() : 0;
}

QString GameController::mapDirection(int x, int y)
{
    if (x < 1300) {
        setJoystickDirection(JoystickDirection::Down);
        return "Left";
    } else if (x > 2750) {
        setJoystickDirection(JoystickDirection::Up);
        return "Right";
    } else if (y < 1300) {
        setJoystickDirection(JoystickDirection::Left);
        return "Up";
    } else if (y > 2750) {
        setJoystickDirection(JoystickDirection::Right);
        return "Down";
    } else {
        setJoystickDirection(JoystickDirection::None);
        return "None";
    }
}

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