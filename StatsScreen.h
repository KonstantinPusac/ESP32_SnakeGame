#ifndef STATSSCREEN_H
#define STATSSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class StatsScreen : public QWidget {
    Q_OBJECT
    
public:
    explicit StatsScreen(QWidget *parent = nullptr);
    ~StatsScreen(); 

signals:
    void backToMenu();
    
protected:
    void showEvent(QShowEvent *event) override;
    
private:
    void setupUI();
    void refreshScores();

    QVBoxLayout *m_layout;
    QPushButton *m_backBtn; 
};

#endif // STATSSCREEN_H