#ifndef MAINSNAKE_H
#define MAINSNAKE_H

#include <QMainWindow>
#include <QStackedWidget>
#include "GameController.h"
#include "MainMenu.h"
#include "GameScreen.h"
#include "SettingsScreen.h"
#include "StatsScreen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainSnake;
}
QT_END_NAMESPACE

class MainSnake : public QMainWindow
{
    Q_OBJECT

public:
    MainSnake(QWidget *parent = nullptr);
    ~MainSnake();

private slots:
    void showMenu();
    void showGameScreen();
    void showSettingsScreen();
    void showStatsScreen();

private:
    Ui::MainSnake *ui;
    QStackedWidget *m_stackedWidget;
    GameController *m_controller;
    MainMenu *m_mainMenu;
    GameScreen *m_gameScreen;
    SettingsScreen *m_settingsScreen;
    StatsScreen *m_statsScreen;
};
#endif // MAINSNAKE_H
