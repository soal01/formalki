#include "RegularHandler.h"


RegularHandler::RegularHandler()
    : _regularExpression(),
    _x('a'),
    _count(0) {
    
}


void RegularHandler::readInput() {
    std::cin >> _regularExpression;
    std::cin >> _x;
    std::cin >> _count;
}

void RegularHandler::_handlePlus(std::stack<LengthStorage>& regulars) {
    LengthStorage first = regulars.top();
    regulars.pop();
    LengthStorage second = regulars.top();
    regulars.pop();
    regulars.push(add(first, second));
}

void RegularHandler::_handleKleenieStar(std::stack<LengthStorage>& regulars) {
    LengthStorage first = regulars.top();
    regulars.pop();
    regulars.push(kleenieStar(first));
}

void RegularHandler::_handleDot(std::stack<LengthStorage>& regulars) {
    LengthStorage first = regulars.top();
    regulars.pop();
    LengthStorage second = regulars.top();
    regulars.pop();
    regulars.push(concatenate(first, second));
}

void RegularHandler::_handleLetter(std::stack<LengthStorage>& regulars, char letter) {
    LengthStorage newRegular(_count, letter);
    regulars.push(newRegular);
}

void RegularHandler::_handleChar(std::stack<LengthStorage>& regulars, char c) {
    if (c == '.') {
        _handleDot(regulars);
        return;
    }
    if (c == '+') {
        _handlePlus(regulars);
        return;
    }
    if (c == '*') {
        _handleKleenieStar(regulars);
        return;
    }
    _handleLetter(regulars, c);
}

LengthStorage RegularHandler::_handleRegular() {
    std::stack<LengthStorage> regulars;
    for (char c : _regularExpression) {
        _handleChar(regulars, c);
    }
    return regulars.top();
}


size_t RegularHandler::getAnswer() {
    LengthStorage finalStorage = _handleRegular();
    return finalStorage[_count];
}

