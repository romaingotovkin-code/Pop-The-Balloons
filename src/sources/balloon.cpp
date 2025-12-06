#include "balloon.h"

Balloon::Balloon(const QPoint &position, int size, const QColor &color,
                 qint64 spawnTime, int lifetime)
    : m_position(position), m_size(size), m_color(color),
      m_spawnTime(spawnTime), m_lifetime(lifetime)
{
}
