#include "include/navigate.h"
#include "include/screen.h"
void Navigation::push_and_replace_replace(std::unique_ptr<Screen> screen) {
  if (!navigationStack.empty())
    navigationStack.pop();
  navigationStack.push(std::move(screen));
}
