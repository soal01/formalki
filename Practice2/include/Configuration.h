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

std::set<Configuration> Scan(const Configuration& conf, char letter);
std::set<Configuration> Predict(const Configuration& conf, const Rule& rule);
std::set<Configuration> Complete(const Configuration& topConf,
                                 const Configuration& bottomConf);


bool operator <(const Configuration& first, const Configuration& second);
bool operator ==(const Configuration& first, const Configuration& second);

std::ostream& operator <<(std::ostream& os, const Configuration& conf);
