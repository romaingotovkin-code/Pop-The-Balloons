#include <QtTest>
#include <QTest>
#include <QCoreApplication>
#include <QSignalSpy>
#include <QMouseEvent>
#include <QDateTime>
#include "../../src/headers/gameengine.h"
#include "../headers/test_gameengine.h"

void TestGameEngine::init()
{
    engine = new GameEngine(nullptr);
}

void TestGameEngine::cleanup()
{
    delete engine;
}

void TestGameEngine::testGameEngineCreation()
{
    QVERIFY(engine != nullptr);
    QVERIFY(engine->minimumSize().isValid());
    QCOMPARE(engine->getScore(), 0);
    QVERIFY(!engine->isGameActive());
    QVERIFY(engine->getBalloons().isEmpty());
}

void TestGameEngine::testGameStart()
{

    QSignalSpy startedSpy(engine, SIGNAL(gameStarted()));
    QSignalSpy scoreSpy(engine, SIGNAL(scoreChanged(int)));
    QSignalSpy colorSpy(engine, SIGNAL(targetColorChanged(QColor)));

    engine->startGame();

    QVERIFY(engine->isGameActive());
    QCOMPARE(startedSpy.count(), 1);
    QCOMPARE(scoreSpy.count(), 1);
    QCOMPARE(scoreSpy.first().first().toInt(), 0);
    QCOMPARE(colorSpy.count(), 1);
    QVERIFY(engine->getTargetColor().isValid());
}

void TestGameEngine::testGameOver()
{
    engine->startGame();
    QVERIFY(engine->isGameActive());

    QSignalSpy gameOverSpy(engine, SIGNAL(gameOver(int)));
    engine->gameOver();

    QVERIFY(!engine->isGameActive());
    QCOMPARE(gameOverSpy.count(), 1);
    QCOMPARE(gameOverSpy.first().first().toInt(), engine->getScore());
}

void TestGameEngine::testBalloonSpawning()
{
    engine->startGame();

    QColor testColor = Qt::red;
    QPoint testPos(100, 100);

    int initialCount = engine->getBalloons().size();
    engine->spawnTestBalloon(testColor, testPos);

    QList<Balloon> balloons = engine->getBalloons();
    QCOMPARE(balloons.size(), initialCount + 1);

    Balloon lastBalloon = balloons.last();
    QCOMPARE(lastBalloon.position(), testPos);
    QCOMPARE(lastBalloon.color(), testColor);
}

void TestGameEngine::testTargetColorChange()
{
    engine->startGame();

    QColor initialColor = engine->getTargetColor();

    QSignalSpy colorSpy(engine, SIGNAL(targetColorChanged(QColor)));
    engine->changeTargetColor();

    QColor newColor = engine->getTargetColor();
    QVERIFY(initialColor != newColor);
    QCOMPARE(colorSpy.count(), 1);
}

void TestGameEngine::testScoreOnCorrectClick()
{
    engine->startGame();

    QColor targetColor = engine->getTargetColor();
    QPoint testPos(200, 200);

    engine->spawnTestBalloon(targetColor, testPos);
    QSignalSpy scoreSpy(engine, SIGNAL(scoreChanged(int)));


    QSKIP("Требуется публичный метод для проверки кликов");
}

void TestGameEngine::testGameOverOnWrongClick()
{
    engine->startGame();

    QColor targetColor = engine->getTargetColor();
    QColor wrongColor = (targetColor == Qt::red) ? Qt::blue : Qt::red;
    QPoint testPos(200, 200);

    engine->spawnTestBalloon(wrongColor, testPos);
    QSignalSpy gameOverSpy(engine, SIGNAL(gameOver(int)));


    QSKIP("Требуется публичный метод для проверки кликов");
}

void TestGameEngine::testCleanup()
{
    engine->startGame();

    engine->spawnTestBalloon(Qt::red, QPoint(100, 100));
    engine->spawnTestBalloon(Qt::blue, QPoint(150, 150));

    QVERIFY(!engine->getBalloons().isEmpty());
    engine->gameOver();
    QVERIFY(engine->getBalloons().isEmpty());
}

void TestGameEngine::testBalloonRemoval()
{
    engine->startGame();

    QColor testColor = Qt::green;
    QPoint testPos(300, 300);

    engine->spawnTestBalloon(testColor, testPos);
    int initialCount = engine->getBalloons().size();


    QTest::qWait(3500);

    int finalCount = engine->getBalloons().size();
    QVERIFY(finalCount <= initialCount);
}

void TestGameEngine::testSignals()
{
    QSignalSpy startedSpy(engine, SIGNAL(gameStarted()));
    QSignalSpy gameOverSpy(engine, SIGNAL(gameOver(int)));
    QSignalSpy scoreSpy(engine, SIGNAL(scoreChanged(int)));
    QSignalSpy colorSpy(engine, SIGNAL(targetColorChanged(QColor)));

    engine->startGame();
    QCOMPARE(startedSpy.count(), 1);
    QCOMPARE(scoreSpy.count(), 1);
    QCOMPARE(colorSpy.count(), 1);

    engine->gameOver();
    QCOMPARE(gameOverSpy.count(), 1);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    TestGameEngine test;
    return QTest::qExec(&test, argc, argv);
}
