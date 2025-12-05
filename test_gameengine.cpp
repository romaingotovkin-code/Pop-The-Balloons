#include <QtTest>
#include "gameengine.h"
#include "balloon.h"

class TestGameEngine : public QObject
{
    Q_OBJECT

private slots:
    void testGameEngineCreation();
    void testGameStart();
    void testBalloonSpawning();
    void testTargetColorChange();
    void testBalloonClick();
    void testGameOver();
};

void TestGameEngine::testGameEngineCreation()
{
    GameEngine engine;
    QVERIFY(engine.minimumSize().isValid());
}

void TestGameEngine::testGameStart()
{
    GameEngine engine;
    engine.startGame();

    // Проверяем, что игра активна после старта
    QVERIFY(engine.isGameActive());
}

void TestGameEngine::testBalloonSpawning()
{
    GameEngine engine;
    engine.startGame();

    // Проверяем создание шарика с определенным цветом
    int initialCount = engine.getBalloons().size();
    QTest::qWait(400); // Ждем появления шарика
    QVERIFY(engine.getBalloons().size() > initialCount);
}

void TestGameEngine::testTargetColorChange()
{
    GameEngine engine;
    engine.startGame();

    // Сохраняем начальный цвет
    QColor initialColor = engine.getTargetColor();

    // Имитируем смену цвета
    engine.changeTargetColor();
    QColor newColor = engine.getTargetColor();
    QVERIFY(initialColor != newColor);
}

void TestGameEngine::testBalloonClick()
{
    GameEngine engine;
    engine.startGame();

    // Создаем тестовый шарик нужного цвета
    engine.spawnTestBalloon(engine.getTargetColor(), QPoint(100, 100));

    // Имитируем клик по шарику
    QTest::mouseClick(&engine, Qt::LeftButton, Qt::NoModifier, QPoint(100, 100));

    // Проверяем, что счет увеличился
    QVERIFY(engine.getScore() > 0);
}

void TestGameEngine::testGameOver()
{
    GameEngine engine;
    engine.startGame();

    // Создаем шарик неправильного цвета и кликаем по нему
    QColor wrongColor = (engine.getTargetColor() == Qt::red) ? Qt::blue : Qt::red;
    engine.spawnTestBalloon(wrongColor, QPoint(100, 100));
    QTest::mouseClick(&engine, Qt::LeftButton, Qt::NoModifier, QPoint(100, 100));

    // Проверяем, что игра завершилась
    QVERIFY(!engine.isGameActive());
}

QTEST_MAIN(TestGameEngine)
#include "test_gameengine.moc"
