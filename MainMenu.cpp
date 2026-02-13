#include "MainMenu.h"
#include <QVBoxLayout>
#include <QLabel>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

MainMenu::~MainMenu()
{
}

void MainMenu::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 40, 20, 40);
    
    // Title
    QLabel *titleLabel = new QLabel("SNAKE GAME");
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #000000;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    
    layout->addStretch();
    
    // Play Button
    m_playBtn = new QPushButton("PLAY");
    m_playBtn->setFixedHeight(60);
    m_playBtn->setStyleSheet(
        "QPushButton { "
        "font-size: 18px; "
        "font-weight: bold; "
        "background-color: #000000; "
        "color: white; "
        "border: none; "
        "border-radius: 5px; "
        "} "
        "QPushButton:hover { background-color: #00DD00; } "
    );
    connect(m_playBtn, &QPushButton::clicked, this, &MainMenu::playClicked);
    layout->addWidget(m_playBtn);
    
    // Settings Button
    m_settingsBtn = new QPushButton("SETTINGS");
    m_settingsBtn->setFixedHeight(60);
    m_settingsBtn->setStyleSheet(
        "QPushButton { "
        "font-size: 18px; "
        "font-weight: bold; "
        "background-color: #000000; "
        "color: white; "
        "border: none; "
        "border-radius: 5px; "
        "} "
        "QPushButton:hover { background-color: #0088FF; } "
    );
    connect(m_settingsBtn, &QPushButton::clicked, this, &MainMenu::settingsClicked);
    layout->addWidget(m_settingsBtn);

    // Stats Button
    m_statsBtn = new QPushButton("STATS");
    m_statsBtn->setFixedHeight(60);
    m_statsBtn->setStyleSheet(
        "QPushButton { "
        "font-size: 18px; "
        "font-weight: bold; "
        "background-color: #000000; "
        "color: white; "
        "border: none; "
        "border-radius: 5px; "
        "} "
        "QPushButton:hover { background-color: #ff7b00; } "
    );
    connect(m_statsBtn, &QPushButton::clicked, this, &MainMenu::statsClicked);
    layout->addWidget(m_statsBtn);
    
    // Exit Button
    m_exitBtn = new QPushButton("EXIT");
    m_exitBtn->setFixedHeight(60);
    m_exitBtn->setStyleSheet(
        "QPushButton { "
        "font-size: 18px; "
        "font-weight: bold; "
        "background-color: #000000; "
        "color: white; "
        "border: none; "
        "border-radius: 5px; "
        "} "
        "QPushButton:hover { background-color: #FF0000; } "
    );
    connect(m_exitBtn, &QPushButton::clicked, this, &MainMenu::exitClicked);
    layout->addWidget(m_exitBtn);
    
    layout->addStretch();
    
    setStyleSheet("background-color: #e0e0e0;");
}
