#include "SnakeGame.h"
#include <QRandomGenerator>

SnakeGame::SnakeGame(QObject *parent) : QObject(parent), m_score(0), m_state(GameState::Paused), m_gridWidth(0), m_gridHeight(0)
{
    m_gameTimer = new QTimer(this);
    connect(m_gameTimer, &QTimer::timeout, this, &SnakeGame::onGameTick);
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::start(int gridWidth, int gridHeight, int cellSize)
{
    m_gridWidth = gridWidth;
    m_gridHeight = gridHeight;
    reset();
    
    m_state = GameState::Playing;
    emit stateChanged(m_state);
    
    // Game tick based on score to increase difficulty
    if (m_score > 50) { m_gameTimer->start(80); } 
    else if (m_score > 100) { m_gameTimer->start(60); }
    else { m_gameTimer->start(100); }
}

void SnakeGame::stop()
{
    m_gameTimer->stop();
}

void SnakeGame::reset()
{
    m_snakeBody.clear();
    m_score = 0;
    
    // Initialize snake at center with length 3
    int startX = m_gridWidth / 2;
    int startY = m_gridHeight / 2;
    m_snakeBody.append(QPoint(startX, startY));
    m_snakeBody.append(QPoint(startX - 1, startY));
    m_snakeBody.append(QPoint(startX - 2, startY));
    
    m_currentDx = 1;
    m_currentDy = 0;
    m_nextDx = 1;
    m_nextDy = 0;
    
    generateFood();
}

void SnakeGame::moveSnake(int dx, int dy)
{
    // Prevent 180-degree turns
    if (dx != 0 && m_currentDx == 0) {
        m_nextDx = dx;
        m_nextDy = 0;
    } else if (dy != 0 && m_currentDy == 0) {
        m_nextDx = 0;
        m_nextDy = dy;
    }
}

void SnakeGame::onGameTick()
{
    if (m_state != GameState::Playing) {
        return;
    }
    
    // Update direction
    m_currentDx = m_nextDx;
    m_currentDy = m_nextDy;
    
    // Calculate new head position
    QPoint newHead = m_snakeBody.first();
    newHead.rx() += m_currentDx;
    newHead.ry() += m_currentDy;
    
    // Check wall collision
    if (newHead.x() < 0 || newHead.x() >= m_gridWidth || newHead.y() < 0 || newHead.y() >= m_gridHeight) 
    {
        m_state = GameState::GameOver;
        m_gameTimer->stop();
        emit gameOver(m_score);
        emit stateChanged(m_state);
        return;
    }
    
    // Check self collision
    if (m_snakeBody.contains(newHead)) {
        m_state = GameState::GameOver;
        m_gameTimer->stop();
        emit gameOver(m_score);
        emit stateChanged(m_state);
        return;
    }
    
    // Move snake
    m_snakeBody.prepend(newHead);
    
    // Check if food eaten
    if (newHead == m_foodPos) {
        m_score += 10;
        emit foodEaten();
        generateFood();
    } else {
        m_snakeBody.removeLast();
    }
    
    emit snakeMoved();
}

void SnakeGame::generateFood()
{
    if (m_gridWidth <= 0 || m_gridHeight <= 0) {
        m_foodPos = QPoint(0, 0);
        return;
    }
    QRandomGenerator gen;
    int x = gen.bounded(m_gridWidth);
    int y = gen.bounded(m_gridHeight);
    m_foodPos = QPoint(x, y);
    // Make sure food doesn't spawn on snake
    int safety = 0;
    while (m_snakeBody.contains(m_foodPos) && safety < 1000) {
        x = gen.bounded(m_gridWidth);
        y = gen.bounded(m_gridHeight);
        m_foodPos = QPoint(x, y);
        ++safety;
    }
}

bool SnakeGame::checkCollision()
{
    return false; // Collision checking is done in onGameTick
}
