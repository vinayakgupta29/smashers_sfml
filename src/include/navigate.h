#pragma once 
#include "screen.h"
#include <memory>
#include <stack>
class Navigation{
private:
    std::stack<std::unique_ptr<Screen>>navigationStack;
public:
void push_and_replace_replace(std::unique_ptr<Screen> screen);};