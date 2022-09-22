#include "actionBase.h"
#include <iostream>

actionBase::actionBase(std::function<void()> aCallback) : callback(aCallback) {}
