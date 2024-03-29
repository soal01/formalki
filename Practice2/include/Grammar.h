#pragma once
#include <set>
#include <string>
#include <iostream>

struct Rule {
    char LeftSymbol;
    std::string rightPart;
    Rule(const std::string& strOfRule);
    Rule();
    char operator[](size_t ind) const;
};

bool operator ==(const Rule& first, const Rule& second);
bool operator <(const Rule& first, const Rule& second);


struct Grammar {
    std::set<Rule> rules;
};


std::istream& operator >>(std::istream& is, Rule& rule);
std::istream& operator >>(std::istream& is, Grammar& grammar);


bool operator ==(const Grammar& first, const Grammar& second);