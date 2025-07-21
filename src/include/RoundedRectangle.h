#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class RoundedRectangle : public sf::Shape {
public:
  RoundedRectangle();

  void setSize(sf::Vector2f size);
  sf::Vector2f getSize() const;

  void setRadius(float radius);
  float getRadius() const;

  void setCornerPointCount(size_t points);
  size_t getCornerPointCount() const;

  virtual size_t getPointCount() const override;
  virtual sf::Vector2f getPoint(size_t index) const override;

private:
  size_t m_cornerPointCount = 2;
  float m_anglePerPoint = 45.0f;
  float m_radius = 1.0f;
  sf::Vector2f m_size;
};
;
