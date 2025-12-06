#ifndef TESTBALLOON_H
#define TESTBALLOON_H

#include <QObject>

class Balloon;

class TestBalloon : public QObject
{
    Q_OBJECT

private slots:
    void testBalloonCreation();
    void testBalloonProperties();
    void testBalloonPosition();
    void testBalloonSize();
    void testBalloonColor();
    void testBalloonLifetime();
};

#endif
