#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QList>
#include "balloon.h"

class GameEngine : public QWidget
{
    Q_OBJECT

public:
    explicit GameEngine(QWidget *parent = nullptr);
    void startGame();
    void gameOver();

    // Методы для тестирования
    bool isGameActive() const { return gameActive; }
    QColor getTargetColor() const { return targetColor; }
    int getScore() const { return score; }
    QList<Balloon> getBalloons() const { return balloons; }
    void spawnTestBalloon(const QColor &color, const QPoint &position);
    void changeTargetColor(); // Переносим в public для тестирования

signals:
    void gameStarted();
    void gameOver(int score);
    void scoreChanged(int score);
    void targetColorChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void spawnBalloon();
    void removeOldBalloons();
    void spawnTargetBalloon();

private:
    void initColors();
    QColor getRandomColor();
    void checkBalloonClick(const QPoint &pos);
    void cleanup();
    void spawnBalloonWithColor(const QColor &color);

    QList<Balloon> balloons;
    QList<QColor> availableColors;
    QColor targetColor;
    int score;
    bool gameActive;

    QTimer *spawnTimer;
    QTimer *cleanupTimer;
    QTimer *colorChangeTimer;
    QTimer *targetBalloonTimer;
};

#endif // GAMEENGINE_H
