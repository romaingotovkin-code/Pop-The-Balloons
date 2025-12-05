#ifndef BALLOON_H
#define BALLOON_H

#include <QtGui> // Включаем все Gui компоненты вместо отдельных
#include <QPoint>
#include <QColor>

class Balloon
{
public:
    Balloon() = default;
    Balloon(const QPoint &position, int size, const QColor &color,
            qint64 spawnTime, int lifetime);

    QPoint position() const { return m_position; }
    int size() const { return m_size; }
    QColor color() const { return m_color; }
    qint64 spawnTime() const { return m_spawnTime; }
    int lifetime() const { return m_lifetime; }

private:
    QPoint m_position;
    int m_size;
    QColor m_color;
    qint64 m_spawnTime;
    int m_lifetime;
};

#endif // BALLOON_H
