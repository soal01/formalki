#include "Grammar.h"


Rule::Rule(const std::string& strOfRule="") {
    LeftSymbol = strOfRule[0];
    for (size_t i = 3; i < strOfRule.size(); ++i) {
        rightPart.push_back(strOfRule[i]);
    }
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