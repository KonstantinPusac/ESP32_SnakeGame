#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "SnakeGame.h"
#include "GameController.h"

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(GameController *controller, QWidget *parent = nullptr);
    ~GameScreen();

    void startGame();

signals:
    void backToMenu();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void onSnakeMoved();
    void onGameOver(int score);
    void onDirectionChanged(JoystickDirection direction);
    void onBackButtonClicked();

private:
    void setupUI();
    void drawGameArea();

    GameController *m_controller;
    SnakeGame *m_game;
    QLabel *m_scoreLabel;
    QPushButton *m_backBtn;
    int m_cellSize = 20;
};

#endif // GAMESCREEN_H
