#include "actionBase.h"
#include <iostream>

using namespace action;

actionBase::actionBase(std::function<void()> aCallback) : callback(aCallback) {}
