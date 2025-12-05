#include <QtTest>
#include <QtGui> // Включаем все Gui компоненты
#include "balloon.h"

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

void TestBalloon::testBalloonCreation()
{
    QPoint position(50, 50);
    int size = 40;
    QColor color(Qt::red);
    qint64 spawnTime = QDateTime::currentMSecsSinceEpoch();
    int lifetime = 2000;

    Balloon balloon(position, size, color, spawnTime, lifetime);

    QVERIFY(balloon.position() == position);
    QCOMPARE(balloon.size(), size);
    QVERIFY(balloon.color() == color);
    QCOMPARE(balloon.spawnTime(), spawnTime);
    QCOMPARE(balloon.lifetime(), lifetime);
}

void TestBalloon::testBalloonProperties()
{
    QPoint position(100, 100);
    int size = 60;
    QColor color(Qt::blue);
    qint64 spawnTime = 123456789;
    int lifetime = 3000;

    Balloon balloon(position, size, color, spawnTime, lifetime);

    QCOMPARE(balloon.position().x(), 100);
    QCOMPARE(balloon.position().y(), 100);
    QCOMPARE(balloon.size(), 60);
    QVERIFY(balloon.color() == Qt::blue);
    QCOMPARE(balloon.spawnTime(), 123456789);
    QCOMPARE(balloon.lifetime(), 3000);
}

void TestBalloon::testBalloonPosition()
{
    QPoint position1(0, 0);
    QPoint position2(200, 150);

    Balloon balloon1(position1, 30, Qt::red, 0, 1000);
    Balloon balloon2(position2, 50, Qt::green, 0, 2000);

    QVERIFY(balloon1.position() == QPoint(0, 0));
    QVERIFY(balloon2.position() == QPoint(200, 150));
    QVERIFY(balloon1.position() != balloon2.position());
}

void TestBalloon::testBalloonSize()
{
    Balloon balloon1(QPoint(50, 50), 20, Qt::red, 0, 1000);
    Balloon balloon2(QPoint(100, 100), 80, Qt::blue, 0, 1000);

    QCOMPARE(balloon1.size(), 20);
    QCOMPARE(balloon2.size(), 80);
    QVERIFY(balloon1.size() < balloon2.size());
}

void TestBalloon::testBalloonColor()
{
    Balloon redBalloon(QPoint(50, 50), 40, Qt::red, 0, 1000);
    Balloon blueBalloon(QPoint(100, 100), 40, Qt::blue, 0, 1000);
    Balloon greenBalloon(QPoint(150, 150), 40, Qt::green, 0, 1000);

    QVERIFY(redBalloon.color() == Qt::red);
    QVERIFY(blueBalloon.color() == Qt::blue);
    QVERIFY(greenBalloon.color() == Qt::green);
    QVERIFY(redBalloon.color() != blueBalloon.color());
}

void TestBalloon::testBalloonLifetime()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    Balloon shortLived(QPoint(50, 50), 40, Qt::red, currentTime, 500);
    Balloon longLived(QPoint(100, 100), 40, Qt::blue, currentTime, 5000);

    QCOMPARE(shortLived.lifetime(), 500);
    QCOMPARE(longLived.lifetime(), 5000);
    QVERIFY(shortLived.lifetime() < longLived.lifetime());

    QVERIFY(currentTime - shortLived.spawnTime() < shortLived.lifetime());
}

QTEST_MAIN(TestBalloon)
#include "test_balloon.moc"
