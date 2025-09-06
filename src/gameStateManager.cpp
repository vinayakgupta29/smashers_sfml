#include "include/gameStateManager.h"

namespace {
Game::GameState currState = Game::GameState::WAITING;
Game::GameState prevState = Game::GameState::WAITING;
} // namespace
namespace Game {
GameState &getGameState() { return currState; }
void setGameState(GameState newState) {
  prevState = currState;
  currState = newState;
}
bool isStateUpdated() { return prevState == currState; }
} // namespace Game
