#include "GameScreen.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QFile>
#include <QDateTime>

GameScreen::GameScreen(GameController *controller, QWidget *parent) : QWidget(parent), m_controller(controller)
{
    setupUI();
    
    m_game = new SnakeGame(this);
    connect(m_game, &SnakeGame::snakeMoved, this, &GameScreen::onSnakeMoved);
    connect(m_game, &SnakeGame::gameOver, this, &GameScreen::onGameOver);
    
    connect(m_controller, &GameController::directionChanged, this, &GameScreen::onDirectionChanged);
    
    // Set focus to capture keyboard events
    setFocus();
    
    setStyleSheet("background-color: #000000;");
}

GameScreen::~GameScreen() {}

void GameScreen::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Top bar with score and back button
    QHBoxLayout *topLayout = new QHBoxLayout();
    
    m_scoreLabel = new QLabel("Score: 0");
    m_scoreLabel->setStyleSheet("color: #00FF00; font-size: 18px; font-weight: bold;");
    topLayout->addWidget(m_scoreLabel);
    
    topLayout->addStretch();
    
    m_backBtn = new QPushButton("BACK (ESC)");
    m_backBtn->setStyleSheet(
        "QPushButton { "
        "font-size: 14px; "
        "background-color: #CC0000; "
        "color: white; "
        "border: none; "
        "border-radius: 3px; "
        "padding: 5px 15px; "
        "} "
        "QPushButton:hover { background-color: #FF0000; } "
    );
    connect(m_backBtn, &QPushButton::clicked, this, &GameScreen::onBackButtonClicked);
    topLayout->addWidget(m_backBtn);
    
    mainLayout->addLayout(topLayout);
    
    // Game area will be drawn in paintEvent
    mainLayout->addStretch();
}

void GameScreen::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    drawGameArea();
}

void GameScreen::drawGameArea()
{
    QPainter painter(this);
    
    int gridWidth = m_game->getGridWidth();
    int gridHeight = m_game->getGridHeight();
    int startX = 50;
    int startY = 80;
    
    // Draw grid border
    painter.setPen(QPen(Qt::green, 2));
    painter.drawRect(startX, startY, gridWidth * m_cellSize, gridHeight * m_cellSize);
    
    // Draw snake
    painter.fillRect(0, 0, width(), height(), QColor(0, 0, 0));
    painter.setPen(QPen(Qt::green, 2));
    painter.drawRect(startX - 1, startY - 1, gridWidth * m_cellSize + 2, gridHeight * m_cellSize + 2);
    
    QList<QPoint> snakeBody = m_game->getSnakeBody();
    for (int i = 0; i < snakeBody.size(); ++i) {
        QPoint pos = snakeBody[i];
        int x = startX + pos.x() * m_cellSize;
        int y = startY + pos.y() * m_cellSize;
        
        if (i == 0) {
            // Head
            painter.fillRect(x, y, m_cellSize, m_cellSize, QColor(0, 255, 0));
        } else {
            // Body
            painter.fillRect(x, y, m_cellSize, m_cellSize, QColor(0, 200, 0));
        }
        painter.drawRect(x, y, m_cellSize, m_cellSize);
    }
    
    // Draw food
    QPoint foodPos = m_game->getFoodPosition();
    int foodX = startX + foodPos.x() * m_cellSize;
    int foodY = startY + foodPos.y() * m_cellSize;
    painter.fillRect(foodX, foodY, m_cellSize, m_cellSize, QColor(255, 0, 0));
    painter.drawRect(foodX, foodY, m_cellSize, m_cellSize);
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    
    if (event->key() == Qt::Key_Escape) {
        onBackButtonClicked();
        return;
    }
    
    m_controller->simulateKeyPress(event->key());
}

void GameScreen::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {
        m_controller->setJoystickDirection(JoystickDirection::None);
    }
}

void GameScreen::onSnakeMoved()
{
    m_scoreLabel->setText(QString("Score: %1").arg(m_game->getScore()));
    update();
}

void GameScreen::onGameOver(int score)
{
    m_backBtn->setText("GAME OVER - BACK (ESC)");
    m_scoreLabel->setText(QString("Game Over! Final Score: %1").arg(score));

    // Save score to .txt file with format: "Date, Time - Score: X, Length: Y, Time: Z seconds"
    QFile file("scores.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&file);
        QDateTime now = QDateTime::currentDateTime();
        out << "\t" << score << "\t - \t" << now.toString("yyyy-MM-dd, hh:mm:ss") << "\n";
        file.close();
    }
}

void GameScreen::onDirectionChanged(JoystickDirection direction)
{
    if (direction == JoystickDirection::Up) {
        m_game->moveSnake(0, -1);
    } else if (direction == JoystickDirection::Down) {
        m_game->moveSnake(0, 1);
    } else if (direction == JoystickDirection::Left) {
        m_game->moveSnake(-1, 0);
    } else if (direction == JoystickDirection::Right) {
        m_game->moveSnake(1, 0);
    }
}

void GameScreen::onBackButtonClicked()
{
    m_game->stop();
    emit backToMenu();
}

void GameScreen::startGame()
{
    m_game->start(50, 50, m_cellSize);
    m_scoreLabel->setText("Score: 0");
    m_backBtn->setText("BACK (ESC)");
    setFocus();
}
