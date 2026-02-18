#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>

class MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

signals:
    void playClicked();
    void settingsClicked();
    void statsClicked();
    void exitClicked();

private:
    void setupUI();

    QPushButton *m_playBtn;
    QPushButton *m_settingsBtn;
    QPushButton *m_statsBtn;
    QPushButton *m_exitBtn;
};

#endif // MAINMENU_H
