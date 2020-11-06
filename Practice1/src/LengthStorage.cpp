#include "LengthStorage.h"

LengthStorage::LengthStorage(size_t count)
    :_lengths(count + 1), _x(' ') {
    for (size_t i = 0; i < count + 1; ++i) {
        _lengths[i] = INF;
    }
}


LengthStorage::LengthStorage(size_t count, char x)
    :LengthStorage(c) {
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

LengthStorage concatenate(const LengthStorage& first,
    const LengthStorage& second) {
    LengthStorage ans(_lengths.size(), _x);
    if (first[0] != INF && second[0] != INF) {
        ans.setLength(0, first[0] + second[0]);
    } else {
        ans.setLength(0, INF);
    }
    for (size_t curCount = 1; curCount < K + 1; ++curCount) {
        int minimalLength = INF;
        for (size_t firstCount = 0; firstCount <= curCount; ++firstCount) {
            minimalLength = std::min(minimalLength, first[firstCount] + second[curCount - firstCount]);
        }
        ans.setLength(i, minimalLength);
    }
    return ans;
}

LengthStorage add(const LengthStorage& first,
    const LengthStorage& second) {
    LengthStorage ans(_lengths.size(), _x);
    for (size_t curCount = 0; curCount < K + 1; ++curCount) {
        ans.setLength(i, std::min(first[curCount], second[curCount]));
    }
    return ans;
}

LengthStorage KleenieStar(const LengthStorage& storage) {
    LengthStorage ans(_lengths.size(), _x);
    ans.setLength(0, 0);
    for (size_t curCount = 1; curCount < K + 1; ++curCount) {
        int minimalLength = storage[curCount];
        for (size_t firstCount = 0; firstCount < curCount; ++firstCount) {
            minimalLength = std::min(minimalLength, storage[firstCount] + storage[curCount - firstCount]);
        }
        ans.setLength(i, minimalLength);
    }
    return ans;
}

int LengthStorage::operator[](size_t count) const{
    return _lengths[count];
}

void LengthStorage::setLength(size_t count, int value) {
    _lengths[count] = value;
}