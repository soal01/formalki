#pragma once
#include "Grammar.h"
#include <set>

struct Configuration {
    Rule rule;
    int indOfCurrentPosition;
    int indOfLastReadSymbol;
    int numberOfClass;
    Configuration(const Rule& rule, int indOfCurrentPosition,
                 int indOfLastReadSymbol, int numberOfClass);
    char getCurrentSymbol() const;
    char getLeftSymbol() const;
    bool isRuleRead() const;
};

std::set<Configuration> scan(const Configuration& conf, char letter);
std::set<Configuration> predict(const Configuration& conf, const Rule& rule);
std::set<Configuration> complete(const Configuration& topConf,
                                 const Configuration& bottomConf);
