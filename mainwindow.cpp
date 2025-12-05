#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameEngine(new GameEngine(this)), timeLeft(0), gameTimer(nullptr)
{
    setupUI();

    connect(gameEngine, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));
    connect(gameEngine, SIGNAL(gameOver(int)), this, SLOT(onGameOver(int)));
    connect(gameEngine, SIGNAL(scoreChanged(int)), this, SLOT(onScoreChanged(int)));
    connect(gameEngine, SIGNAL(targetColorChanged(QColor)), this, SLOT(onTargetColorChanged(QColor)));
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Панель информации
    QHBoxLayout *infoLayout = new QHBoxLayout();

    scoreLabel = new QLabel("Счёт: 0", this);
    targetColorLabel = new QLabel("Цель: ---", this);
    timerLabel = new QLabel("Время: 2.0", this);

    // Увеличиваем шрифт для информационных надписей
    QFont infoFont = scoreLabel->font();
    infoFont.setPointSize(14);
    infoFont.setBold(true);

    scoreLabel->setFont(infoFont);
    targetColorLabel->setFont(infoFont);
    timerLabel->setFont(infoFont);

    infoLayout->addWidget(scoreLabel);
    infoLayout->addWidget(targetColorLabel);
    infoLayout->addWidget(timerLabel);
    infoLayout->addStretch();

    // Кнопка старта
    startButton = new QPushButton("Начать игру", this);

    // Увеличиваем шрифт кнопки
    QFont buttonFont = startButton->font();
    buttonFont.setPointSize(12);
    startButton->setFont(buttonFont);
    startButton->setMinimumHeight(40); // Делаем кнопку выше

    // Сообщение о конце игры
    gameOverLabel = new QLabel("", this);
    gameOverLabel->setAlignment(Qt::AlignCenter);

    // Увеличиваем шрифт для сообщения о конце игры
    QFont gameOverFont = gameOverLabel->font();
    gameOverFont.setPointSize(16);
    gameOverFont.setBold(true);
    gameOverLabel->setFont(gameOverFont);
    gameOverLabel->setStyleSheet("color: red;");
    gameOverLabel->hide();

    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(gameOverLabel);
    mainLayout->addWidget(gameEngine);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartGame);

    setMinimumSize(700, 550); // Немного увеличим минимальный размер
    setWindowTitle("Лопай шарики!");
}

void MainWindow::onStartGame()
{
    startButton->setEnabled(false);
    gameOverLabel->hide();

    if (gameTimer) {
        gameTimer->stop();
        gameTimer->deleteLater();
        gameTimer = nullptr;
    }

    gameEngine->startGame();
}

void MainWindow::onGameStarted()
{
    timeLeft = 20;
    updateTimerDisplay();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, [this]() {
        timeLeft--;
        updateTimerDisplay();
        if (timeLeft <= 0) {
            if (gameTimer) {
                gameTimer->stop();
            }
            gameEngine->gameOver();
        }
    });
    gameTimer->start(100);
}

void MainWindow::onGameOver(int score)
{
    if (gameTimer) {
        gameTimer->stop();
        gameTimer->deleteLater();
        gameTimer = nullptr;
    }

    startButton->setEnabled(true);
    gameOverLabel->setText(QString("Игра окончена! Ваш счёт: %1").arg(score));
    gameOverLabel->show();

    QMessageBox::information(this, "Конец игры",
        QString("Игра окончена!\nВаш счёт: %1").arg(score));
}

void MainWindow::onScoreChanged(int score)
{
    scoreLabel->setText(QString("Счёт: %1").arg(score));
    timeLeft = 20;
    updateTimerDisplay();
}

void MainWindow::onTargetColorChanged(const QColor &color)
{
    QString colorName;
    if (color == Qt::red) colorName = "КРАСНЫЙ";
    else if (color == Qt::blue) colorName = "СИНИЙ";
    else if (color == Qt::green) colorName = "ЗЕЛЁНЫЙ";
    else if (color == Qt::yellow) colorName = "ЖЁЛТЫЙ";
    else if (color == Qt::magenta) colorName = "ФИОЛЕТОВЫЙ";
    else colorName = "НЕИЗВЕСТНЫЙ";

    targetColorLabel->setText(QString("Цель: %1").arg(colorName));
    targetColorLabel->setStyleSheet(QString("color: %1; font-weight: bold;").arg(color.name()));
}

void MainWindow::updateTimerDisplay()
{
    timerLabel->setText(QString("Время: %1").arg(timeLeft / 10.0, 0, 'f', 1));
}
