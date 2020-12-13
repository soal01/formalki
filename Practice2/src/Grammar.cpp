#include "Grammar.h"


Rule::Rule(const std::string& strOfRule) {
    LeftSymbol = strOfRule[0];
    for (size_t i = 3; i < strOfRule.size(); ++i) {
        rightPart.push_back(strOfRule[i]);
    }
    if (rightPart == "\\eps") {
        rightPart = "";
    }
}

Rule::Rule() {
    LeftSymbol = 0;
    rightPart = "";
}

char Rule::operator[](size_t ind) const {
    return rightPart[ind];
}


std::istream& operator >>(std::istream& is, Rule& rule) {
    std::string s;
    is >> s;
    rule = Rule(s);
    return is;
}

std::istream& operator >>(std::istream& is, Grammar& grammar) {
    int count;
    is >> count;
    for (int i = 0; i < count; ++i) {
        Rule rule;
        is >> rule;
        grammar.rules.insert(rule);
    }
    return is;
}


bool operator ==(const Rule& first, const Rule& second) {
    return first.LeftSymbol == second.LeftSymbol && first.rightPart == second.rightPart;
}


bool operator <(const Rule& first, const Rule& second) {
    if (first.LeftSymbol == second.LeftSymbol) {
        return first.rightPart < second.rightPart;
    }
    return first.LeftSymbol < second.LeftSymbol;
}


bool operator ==(const Grammar& first, const Grammar& second) {
    if (first.rules.size() != second.rules.size()) {
        return false;
    }
    for (auto el : first.rules) {
        if (second.rules.find(el) == second.rules.end()) {
            return false;
        }
    }
    return true;
}