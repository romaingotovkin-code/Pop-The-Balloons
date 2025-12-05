#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "gameengine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onGameStarted();
    void onGameOver(int score);
    void onScoreChanged(int score);
    void onTargetColorChanged(const QColor &color);
    void onStartGame();

private:
    void setupUI();
    void updateTimerDisplay();

    GameEngine *gameEngine;
    QLabel *scoreLabel;
    QLabel *targetColorLabel;
    QLabel *timerLabel;
    QLabel *gameOverLabel;
    QPushButton *startButton;
    QTimer *gameTimer;

    int timeLeft;
};

#endif // MAINWINDOW_H
