#pragma once
#include <string>
#include <stack>
#include <iostream>
#include "LengthStorage.h"

class RegularHandler {
private:
    std::string _regularExpression;
    char _x;
    size_t _count;

    LengthStorage _handleRegular();
    void _handlePlus(std::stack<LengthStorage>& regulars);
    void _handleKleenieStar(std::stack<LengthStorage>& regulars);
    void _handleDot(std::stack<LengthStorage>& regulars);
    void _handleLetter(std::stack<LengthStorage>& regulars, char letter);
    void _handleChar(std::stack<LengthStorage>& regulars, char c);
public:
    RegularHandler();
    RegularHandler(std::string regularExpression, char x, size_t count);
    void readInput(std::istream& is);
    size_t getAnswer();
    void print();
    friend bool operator==(const RegularHandler& a, const RegularHandler& b);
};

bool operator==(const RegularHandler& a, const RegularHandler& b);

