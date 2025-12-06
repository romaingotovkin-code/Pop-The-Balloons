#ifndef TESTGAMEENGINE_H
#define TESTGAMEENGINE_H

#include <QObject>

class GameEngine;

class TestGameEngine : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void testGameEngineCreation();
    void testGameStart();
    void testGameOver();
    void testBalloonSpawning();
    void testTargetColorChange();
    void testScoreOnCorrectClick();
    void testGameOverOnWrongClick();
    void testCleanup();
    void testBalloonRemoval();
    void testSignals();

private:
    GameEngine* engine;
};

#endif
