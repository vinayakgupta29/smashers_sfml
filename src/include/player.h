#pragma once
#include <cstdint>
#include <sys/types.h>
namespace smashers {
class Player {
private:
  int id;

  uint score;
  uint health;

public:
  void setScore(uint s);
  uint getScore() const;

  void setHealth(uint h);
  uint getHealth() const;
  void incrementScore();
  void decrementHealth();
  void reset();
  void print() const;
  Player();
  ~Player() = default;
};
} // namespace smashers
