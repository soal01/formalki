#pragma once
#include "Grammar.h"

class Algo {
public:
    virtual Algo& fit(const Grammar& G) = 0;
    virtual bool predict(const std::string& str) = 0;
};