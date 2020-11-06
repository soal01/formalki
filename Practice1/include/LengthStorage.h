#pragma once
#include <algorithm>
#include <vector>

const size_t INF = 1e9;



class LengthStorage {
private:
    std::vector<int> _lengths;
    char _x;
public:
    LengthStorage(size_t count);
    LengthStorage(size_t count, char x);
    LengthStorage(size_t count, char a, char x);
    int operator[](size_t count) const;
    void setLength(size_t count, int value);
};


LengthStorage concatenate(const LengthStorage& first,
                            const LengthStorage& second);
LengthStorage add(const LengthStorage& first,
                    const LengthStorage& second);
LengthStorage kleenieStar(const LengthStorage& storage);