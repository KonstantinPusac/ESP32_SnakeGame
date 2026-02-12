#include "SettingsScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>

SettingsScreen::SettingsScreen(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadSettings();
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    
    // Title
    QLabel *titleLabel = new QLabel("SETTINGS");
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #00FF00;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    mainLayout->addSpacing(30);
    
    // Volume Section
    QLabel *volumeTitleLabel = new QLabel("VOLUME:");
    volumeTitleLabel->setStyleSheet("color: #00FF00; font-size: 16px; font-weight: bold;");
    mainLayout->addWidget(volumeTitleLabel);
    
    QHBoxLayout *volumeLayout = new QHBoxLayout();
    m_volumeSlider = new QSlider(Qt::Horizontal);
    m_volumeSlider->setRange(0, 100);
    m_volumeSlider->setFixedHeight(30);
    m_volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal { "
        "background: #333333; height: 10px; } "
        "QSlider::handle:horizontal { "
        "background: #00FF00; width: 20px; margin: -5px 0; } "
    );
    connect(m_volumeSlider, QOverload<int>::of(&QSlider::valueChanged),
            this, &SettingsScreen::onVolumeChanged);
    volumeLayout->addWidget(m_volumeSlider);
    
    m_volumeLabel = new QLabel("100%");
    m_volumeLabel->setStyleSheet("color: #00FF00; font-size: 14px; width: 50px;");
    volumeLayout->addWidget(m_volumeLabel);
    mainLayout->addLayout(volumeLayout);
    
    mainLayout->addSpacing(20);
    
    // Brightness Section
    QLabel *brightnessTitleLabel = new QLabel("BRIGHTNESS:");
    brightnessTitleLabel->setStyleSheet("color: #00FF00; font-size: 16px; font-weight: bold;");
    mainLayout->addWidget(brightnessTitleLabel);
    
    QHBoxLayout *brightnessLayout = new QHBoxLayout();
    m_brightnessSlider = new QSlider(Qt::Horizontal);
    m_brightnessSlider->setRange(20, 100);
    m_brightnessSlider->setFixedHeight(30);
    m_brightnessSlider->setStyleSheet(
        "QSlider::groove:horizontal { "
        "background: #333333; height: 10px; } "
        "QSlider::handle:horizontal { "
        "background: #00FF00; width: 20px; margin: -5px 0; } "
    );
    connect(m_brightnessSlider, QOverload<int>::of(&QSlider::valueChanged),
            this, &SettingsScreen::onBrightnessChanged);
    brightnessLayout->addWidget(m_brightnessSlider);
    
    m_brightnessLabel = new QLabel("100%");
    m_brightnessLabel->setStyleSheet("color: #00FF00; font-size: 14px; width: 50px;");
    brightnessLayout->addWidget(m_brightnessLabel);
    mainLayout->addLayout(brightnessLayout);
    
    mainLayout->addStretch();
    
    // Back Button
    m_backBtn = new QPushButton("BACK");
    m_backBtn->setFixedHeight(50);
    m_backBtn->setStyleSheet(
        "QPushButton { "
        "font-size: 16px; "
        "font-weight: bold; "
        "background-color: #CC0000; "
        "color: white; "
        "border: none; "
        "border-radius: 5px; "
        "} "
        "QPushButton:hover { background-color: #FF0000; } "
    );
    connect(m_backBtn, &QPushButton::clicked, this, &SettingsScreen::onBackClicked);
    mainLayout->addWidget(m_backBtn);
    
    setStyleSheet("background-color: #000000;");
}

void SettingsScreen::loadSettings()
{
    QSettings settings("SnakeGame", "SnakeGame");
    int volume = settings.value("volume", 100).toInt();
    int brightness = settings.value("brightness", 100).toInt();
    
    m_volumeSlider->setValue(volume);
    m_brightnessSlider->setValue(brightness);
}

void SettingsScreen::saveSettings()
{
    QSettings settings("SnakeGame", "SnakeGame");
    settings.setValue("volume", m_volumeSlider->value());
    settings.setValue("brightness", m_brightnessSlider->value());
}

void SettingsScreen::onVolumeChanged(int value)
{
    m_volumeLabel->setText(QString("%1%").arg(value));
    emit volumeChanged(value);
    saveSettings();
}

void SettingsScreen::onBrightnessChanged(int value)
{
    m_brightnessLabel->setText(QString("%1%").arg(value));
    emit brightnessChanged(value);
    saveSettings();
}

void SettingsScreen::onBackClicked()
{
    emit backToMenu();
}
