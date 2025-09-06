#pragma once
namespace Game {
enum class GameState {
  WAITING,
  PLAYING,
  GAME_OVER,
  TESTING,
};

GameState &getGameState();
void setGameState(GameState);
bool isStateUpdated();
} // namespace Game
