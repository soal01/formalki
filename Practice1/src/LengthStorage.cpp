#include "LengthStorage.h"

LengthStorage::LengthStorage(size_t count)
    :_lengths(count + 1), _x(' ') {
    for (size_t i = 0; i < count + 1; ++i) {
        _lengths[i] = INF;
    }
}


LengthStorage::LengthStorage(size_t count, char x)
    :LengthStorage(count) {
    _x = x;
}

LengthStorage::LengthStorage(size_t count, char a, char x)
    :LengthStorage(count, x) {
    if (_x == a) {
        _lengths[1] = 1; 
    } else {
        if (a == '1') {
            _lengths[0] = 0;
        } else {
            _lengths[0] = 1;
        }
    }
}

LengthStorage::LengthStorage(std::vector<int> lengths, char x)
    :_lengths(lengths), _x(x) {}


size_t LengthStorage::size() const {
    return _lengths.size() - 1;
}

char LengthStorage::getX() const {
    return _x;
}

LengthStorage concatenate(const LengthStorage& first, const LengthStorage& second) {
    LengthStorage ans(first.size(), first.getX());
    if (first[0] != INF && second[0] != INF) {
        ans.setLength(0, first[0] + second[0]);
    } else {
        ans.setLength(0, INF);
    }
    for (size_t curCount = 1; curCount < first.size() + 1; ++curCount) {
        int minimalLength = INF;
        for (size_t firstCount = 0; firstCount <= curCount; ++firstCount) {
            minimalLength = std::min(minimalLength, first[firstCount] + second[curCount - firstCount]);
        }
        ans.setLength(curCount, minimalLength);
    }
    return ans;
}

LengthStorage add(const LengthStorage& first, const LengthStorage& second) {
    LengthStorage ans(first.size(), first.getX());
    for (size_t curCount = 0; curCount < first.size() + 1; ++curCount) {
        ans.setLength(curCount, std::min(first[curCount], second[curCount]));
    }
    return ans;
}

LengthStorage kleenieStar(const LengthStorage& storage) {
    LengthStorage ans(storage.size(), storage.getX());
    ans.setLength(0, 0);
    for (size_t curCount = 1; curCount < storage.size() + 1; ++curCount) {
        int minimalLength = storage[curCount];
        for (size_t firstCount = 0; firstCount < curCount; ++firstCount) {
            minimalLength = std::min(minimalLength, ans[firstCount] + ans[curCount - firstCount]);
        }
        ans.setLength(curCount, minimalLength);
    }
    return ans;
}

void LengthStorage::print() {
    for (size_t i = 0; i < _lengths.size(); ++i) {
        std::cout << _lengths[i] << " ";
    }
    std::cout << std::endl;
}

int LengthStorage::operator[](size_t count) const{
    return _lengths[count];
}

void LengthStorage::setLength(size_t count, int value) {
    _lengths[count] = value;
}


bool operator==(const LengthStorage& a, const LengthStorage& b) {
    if (a.size() != b.size()) {
        return false;
    }

    if (a.getX() != b.getX()) {
        return false;
    }

    for (size_t i = 0; i < a.size() + 1; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
