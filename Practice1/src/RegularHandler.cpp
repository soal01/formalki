#include "RegularHandler.h"


RegularHandler::RegularHandler()
    : _regularExpression(),
    _x('a'),
    _count(0) {
    
}

RegularHandler::RegularHandler(std::string regularExpression, 
                            char x, size_t count)
    : _regularExpression(regularExpression), _x(x), _count(count) {}


void RegularHandler::readInput(std::istream& is) {
    std::string str;
    std::getline(is, str);
    std::string count = "";
    size_t ind = str.size() - 1;
    while (!(str[ind] >= '0' && str[ind] <= '9')) {
        ind--;
    }
    
    for (; ind >= 0; ind--) {
        if (str[ind] != ' ') {
            count = str[ind] + count;
        } else {
            ind--;
            _x = str[ind];
            break;
        }
    }
    _regularExpression.resize(ind);
    std::copy(str.begin(), str.begin() + ind, _regularExpression.begin());
    _count = atoi(count.c_str());
}

void RegularHandler::print() {
    std::cout << _regularExpression << "  |rrrr" << std::endl;
    std::cout << _x << std::endl;
    std::cout << _count << std::endl;
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
    LengthStorage newRegular(_count, letter, _x);
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
        if (c != ' ') {
            _handleChar(regulars, c);
            //regulars.top().print();
        }
    }
    return regulars.top();
}


size_t RegularHandler::getAnswer() {
    LengthStorage finalStorage = _handleRegular();
    return finalStorage[_count];
}

bool operator==(const RegularHandler& a, const RegularHandler& b) {
    return (a._regularExpression == b._regularExpression) && 
    (a._count == b._count) && (a._x == b._x);
}