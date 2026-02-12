#include "MainSnake.h"
#include "ui_MainSnake.h"

MainSnake::MainSnake(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainSnake)
{
    ui->setupUi(this);
    
    // Create the stacked widget to manage screens
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);
    
    // Create game controller
    m_controller = new GameController(this);
    
    // Create screens
    m_mainMenu = new MainMenu(this);
    m_gameScreen = new GameScreen(m_controller, this);
    m_settingsScreen = new SettingsScreen(this);
    
    // Add screens to stacked widget
    m_stackedWidget->addWidget(m_mainMenu);
    m_stackedWidget->addWidget(m_gameScreen);
    m_stackedWidget->addWidget(m_settingsScreen);
    
    // Connect signals
    connect(m_mainMenu, &MainMenu::playClicked, this, &MainSnake::showGameScreen);
    connect(m_mainMenu, &MainMenu::settingsClicked, this, &MainSnake::showSettingsScreen);
    connect(m_mainMenu, &MainMenu::exitClicked, this, &QMainWindow::close);
    
    connect(m_gameScreen, &GameScreen::backToMenu, this, &MainSnake::showMenu);
    connect(m_settingsScreen, &SettingsScreen::backToMenu, this, &MainSnake::showMenu);
    
    // Set window properties
    setWindowTitle("Snake Game - ESP32");
    setGeometry(50, 50, 500, 550);
    
    // Show main menu
    showMenu();
}

MainSnake::~MainSnake()
{
    delete ui;
}

void MainSnake::showMenu()
{
    m_stackedWidget->setCurrentWidget(m_mainMenu);
}

void MainSnake::showGameScreen()
{
    m_stackedWidget->setCurrentWidget(m_gameScreen);
    m_gameScreen->startGame();
    m_gameScreen->setFocus();
}

void MainSnake::showSettingsScreen()
{
    m_stackedWidget->setCurrentWidget(m_settingsScreen);
}
