#pragma once
#include <string>
#include <stack>
#include<iostream>
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
    void readInput();
    size_t getAnswer();

};