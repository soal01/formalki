#pragma once
#include <set>
#include <string>
#include <iostream>

struct Rule {
    char LeftSymbol;
    std::string rightPart;
    Rule(const std::string& strOfRule);
    char operator[](size_t ind) const;
};



struct Grammar {
    std::set<Rule> rules;
};


std::istream& operator >>(std::istream& is, Rule& rule);
std::istream& operator >>(std::istream& is, Grammar& grammar);