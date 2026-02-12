#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class SettingsScreen : public QWidget {
    Q_OBJECT

public:
    explicit SettingsScreen(QWidget *parent = nullptr);
    ~SettingsScreen();

signals:
    void backToMenu();
    void volumeChanged(int value);
    void brightnessChanged(int value);

private slots:
    void onVolumeChanged(int value);
    void onBrightnessChanged(int value);
    void onBackClicked();

private:
    void setupUI();
    void loadSettings();
    void saveSettings();

    QSlider *m_volumeSlider;
    QLabel *m_volumeLabel;
    QSlider *m_brightnessSlider;
    QLabel *m_brightnessLabel;
    QPushButton *m_backBtn;
};

#endif // SETTINGSSCREEN_H
