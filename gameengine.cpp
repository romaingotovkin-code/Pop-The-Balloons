#include "gameengine.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDateTime>
#include <QRandomGenerator>
#include <QDebug>

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent), score(0), gameActive(false)
{
    setMinimumSize(600, 400);
    setFocusPolicy(Qt::StrongFocus);

    initColors();

    spawnTimer = new QTimer(this);
    spawnTimer->setInterval(300);
    connect(spawnTimer, &QTimer::timeout, this, &GameEngine::spawnBalloon);

    cleanupTimer = new QTimer(this);
    cleanupTimer->setInterval(100);
    connect(cleanupTimer, &QTimer::timeout, this, &GameEngine::removeOldBalloons);

    colorChangeTimer = new QTimer(this);
    colorChangeTimer->setInterval(10000);
    connect(colorChangeTimer, &QTimer::timeout, this, &GameEngine::changeTargetColor);

    targetBalloonTimer = new QTimer(this);
    targetBalloonTimer->setInterval(1500);
    connect(targetBalloonTimer, &QTimer::timeout, this, &GameEngine::spawnTargetBalloon);
}

void GameEngine::startGame()
{
    cleanup();
    score = 0;
    gameActive = true;

    targetColor = getRandomColor();
    emit targetColorChanged(targetColor);
    emit scoreChanged(score);
    emit gameStarted();

    spawnTimer->start();
    cleanupTimer->start();
    colorChangeTimer->start();
    targetBalloonTimer->start();
}

void GameEngine::gameOver()
{
    if (!gameActive) return;

    gameActive = false;
    spawnTimer->stop();
    cleanupTimer->stop();
    colorChangeTimer->stop();
    targetBalloonTimer->stop();

    emit gameOver(score);
}

void GameEngine::initColors()
{
    availableColors << Qt::red << Qt::blue << Qt::green << Qt::yellow << Qt::magenta;
}

QColor GameEngine::getRandomColor()
{
    int index = QRandomGenerator::global()->bounded(availableColors.size());
    return availableColors[index];
}

void GameEngine::spawnBalloon()
{
    if (!gameActive) return;

    int size = QRandomGenerator::global()->bounded(30, 61);
    int x = QRandomGenerator::global()->bounded(size, width() - size);
    int y = QRandomGenerator::global()->bounded(size, height() - size);

    QColor color = getRandomColor();
    qint64 spawnTime = QDateTime::currentMSecsSinceEpoch();
    int lifetime = QRandomGenerator::global()->bounded(2000, 4000);

    Balloon balloon(QPoint(x, y), size, color, spawnTime, lifetime);
    balloons.append(balloon);

    update();
}

void GameEngine::spawnBalloonWithColor(const QColor &color)
{
    if (!gameActive) return;

    int size = QRandomGenerator::global()->bounded(40, 71);
    int x = QRandomGenerator::global()->bounded(size, width() - size);
    int y = QRandomGenerator::global()->bounded(size, height() - size);

    qint64 spawnTime = QDateTime::currentMSecsSinceEpoch();
    int lifetime = QRandomGenerator::global()->bounded(2500, 3500);

    Balloon balloon(QPoint(x, y), size, color, spawnTime, lifetime);
    balloons.append(balloon);

    update();
}

void GameEngine::spawnTargetBalloon()
{
    if (!gameActive) return;

    spawnBalloonWithColor(targetColor);

    if (QRandomGenerator::global()->bounded(100) < 50) {
        spawnBalloon();
    }
}

void GameEngine::spawnTestBalloon(const QColor &color, const QPoint &position)
{
    if (!gameActive) return;

    int size = 40;
    qint64 spawnTime = QDateTime::currentMSecsSinceEpoch();
    int lifetime = 3000;

    Balloon balloon(position, size, color, spawnTime, lifetime);
    balloons.append(balloon);

    update();
}

void GameEngine::removeOldBalloons()
{
    if (!gameActive) return;

    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    bool needsUpdate = false;

    for (int i = balloons.size() - 1; i >= 0; --i) {
        if (currentTime - balloons[i].spawnTime() > balloons[i].lifetime()) {
            balloons.removeAt(i);
            needsUpdate = true;
        }
    }

    if (needsUpdate) {
        update();
    }
}

// Теперь этот метод публичный
void GameEngine::changeTargetColor()
{
    if (!gameActive) return;

    QColor newColor;
    do {
        newColor = getRandomColor();
    } while (newColor == targetColor && availableColors.size() > 1);

    targetColor = newColor;
    emit targetColorChanged(targetColor);

    spawnBalloonWithColor(targetColor);
}

void GameEngine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(240, 240, 240));

    for (const Balloon &balloon : balloons) {
        painter.setBrush(balloon.color());

        if (balloon.color() == targetColor) {
            painter.setPen(QPen(Qt::black, 3));
        } else {
            painter.setPen(QPen(Qt::black, 2));
        }

        painter.drawEllipse(balloon.position(), balloon.size(), balloon.size());
    }
}

void GameEngine::mousePressEvent(QMouseEvent *event)
{
    if (!gameActive) return;

    checkBalloonClick(event->pos());
}

void GameEngine::checkBalloonClick(const QPoint &pos)
{
    for (int i = balloons.size() - 1; i >= 0; --i) {
        const Balloon &balloon = balloons[i];
        QPoint center = balloon.position();
        int radius = balloon.size() / 2;

        int dx = pos.x() - center.x();
        int dy = pos.y() - center.y();

        if (dx * dx + dy * dy <= radius * radius) {
            if (balloon.color() == targetColor) {
                score++;
                emit scoreChanged(score);
            } else {
                gameOver();
                return;
            }

            balloons.removeAt(i);
            update();
            break;
        }
    }
}

void GameEngine::cleanup()
{
    balloons.clear();
    update();
}
