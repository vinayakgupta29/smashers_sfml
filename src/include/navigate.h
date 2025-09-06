#pragma once
#include "screen.h"
#include <memory>
#include <stack>
class Navigation {
private:
  std::stack<std::unique_ptr<smashers::Widget>> navigationStack;

public:
  void push_and_replace(std::unique_ptr<smashers::Widget>);
  void pop(std::unique_ptr<smashers::Widget>);
};
