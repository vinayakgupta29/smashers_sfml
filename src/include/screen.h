#pragma once
#include "gameStateManager.h"
#include "models.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace smashers {
class Widget {
public:
  virtual ~Widget() = default;
};
} // namespace smashers
