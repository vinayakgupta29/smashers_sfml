#include "include/RoundedRectangle.h"

RoundedRectangle::RoundedRectangle() {
  setCornerPointCount(m_cornerPointCount); // Initialize angle per point
}

void RoundedRectangle::setSize(sf::Vector2f size) {
  m_size = size;
  update();
}

sf::Vector2f RoundedRectangle::getSize() const { return m_size; }

void RoundedRectangle::setRadius(float radius) {
  m_radius = radius;
  update();
}

float RoundedRectangle::getRadius() const { return m_radius; }

void RoundedRectangle::setCornerPointCount(size_t points) {
  m_cornerPointCount = points;
  m_anglePerPoint = 90.0f / static_cast<float>(points);
  update();
}

size_t RoundedRectangle::getCornerPointCount() const {
  return m_cornerPointCount;
}

size_t RoundedRectangle::getPointCount() const {
  return m_cornerPointCount * 4;
}

sf::Vector2f RoundedRectangle::getPoint(size_t index) const {
  if (m_cornerPointCount == 1 || m_radius == 0.0f) {
    // Fallback to simple rectangle (not rounded)
    sf::RectangleShape rect(m_size);
    return rect.getPoint(index % 4);
  }

  size_t corner = index / m_cornerPointCount;
  float angle = 0.f;

  bool isLastPointOnCorner =
      (index % m_cornerPointCount == m_cornerPointCount - 1);
  if (isLastPointOnCorner) {
    angle = 90.f;
  } else {
    angle = (index % m_cornerPointCount) * m_anglePerPoint;
  }

  sf::Vector2f point;
  switch (corner) {
  case 0: // Top-left
    point = {m_radius, m_radius};
    angle -= 180.f;
    break;
  case 1: // Top-right
    point = {m_size.x - m_radius, m_radius};
    angle -= 90.f;
    break;
  case 2: // Bottom-right
    point = {m_size.x - m_radius, m_size.y - m_radius};
    break;
  default: // Bottom-left
    point = {m_radius, m_size.y - m_radius};
    angle += 90.f;
  }
  point += sf::Vector2f(
      static_cast<float>(std::cos(angle * M_PI / 180.f) * m_radius),
      static_cast<float>(std::sin(angle * M_PI / 180.f) * m_radius));

  return point;
}
