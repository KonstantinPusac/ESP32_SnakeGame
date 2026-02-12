#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QPoint>
#include <QList>
#include <QTimer>

enum class GameState {
    Playing,
    GameOver,
    Paused
};

class SnakeGame : public QObject {
    Q_OBJECT

public:
    explicit SnakeGame(QObject *parent = nullptr);
    ~SnakeGame();

    void start(int gridWidth, int gridHeight, int cellSize);
    void stop();
    void moveSnake(int dx, int dy);
    void reset();

    // Getters
    QList<QPoint> getSnakeBody() const { return m_snakeBody; }
    QPoint getFoodPosition() const { return m_foodPos; }
    int getScore() const { return m_score; }
    GameState getState() const { return m_state; }
    int getGridWidth() const { return m_gridWidth; }
    int getGridHeight() const { return m_gridHeight; }

signals:
    void snakeMoved();
    void foodEaten();
    void gameOver(int finalScore);
    void stateChanged(GameState state);

private slots:
    void onGameTick();

private:
    void generateFood();
    bool checkCollision();

    QTimer *m_gameTimer;
    QList<QPoint> m_snakeBody;
    QPoint m_foodPos;
    int m_score;
    GameState m_state;
    int m_gridWidth;
    int m_gridHeight;
    int m_nextDx = 1;
    int m_nextDy = 0;
    int m_currentDx = 1;
    int m_currentDy = 0;
};

#endif // SNAKEGAME_H
