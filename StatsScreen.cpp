#include "StatsScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QShowEvent>

StatsScreen::StatsScreen(QWidget *parent) : QWidget(parent), m_layout(nullptr)
{
    setupUI();
}

StatsScreen::~StatsScreen() {}

void StatsScreen::setupUI()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(20);
    m_layout->setContentsMargins(20, 40, 20, 40);
    
    // Title
    QLabel *titleLabel = new QLabel("GAME STATS");
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #000000;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(titleLabel);
    
    m_layout->addStretch();

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
    connect(m_backBtn, &QPushButton::clicked, this, &StatsScreen::backToMenu);
    m_layout->addWidget(m_backBtn);
    
    setStyleSheet("background-color: #e0e0e0;");
}

void StatsScreen::refreshScores()
{
    // Remove all score labels (keep title and back button)
    QLayoutItem *item;
    while ((item = m_layout->itemAt(1)) != nullptr && item->widget() != m_backBtn) {
        delete item->widget();
        m_layout->removeItem(item);
    }
    
    // Read and display scores from scores.txt
    QFile file("scores.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString line;
        int insertPosition = 1; // After title
        
        while (in.readLineInto(&line)) {
            QLabel *scoreLabel = new QLabel(line);
            scoreLabel->setStyleSheet("font-size: 18px; color: #000000; font-weight: bold;");
            m_layout->insertWidget(insertPosition, scoreLabel);
            insertPosition++;
        }
        file.close();
    } else {
        QLabel *noScoresLabel = new QLabel("No scores available.");
        noScoresLabel->setStyleSheet("font-size: 18px; color: #000000; font-weight: bold;");
        m_layout->insertWidget(1, noScoresLabel);
    }
    
    // Ensure stretch is between scores and back button
    if (m_layout->itemAt(m_layout->count() - 2)->spacerItem() == nullptr) {
        m_layout->insertStretch(m_layout->count() - 1);
    }
}

void StatsScreen::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    refreshScores();
}

