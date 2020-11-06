#pragma once
#include"automat.h"


Automat determinateAutomat(const Automat& automat);


bool isFullAutomat(const Automat& automat);
void makeFull(Automat& automat);
Automat minimizeFullDeterminateAutomat(const Automat& automat);
Automat makeMinimalDeterminateAutomat(const Automat& automat);