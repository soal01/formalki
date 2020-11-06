#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<set>


class Automat {
private:
    std::vector<char> alphabet_;
    std::vector<std::map<char, std::set<size_t> > >  edges_;
    size_t countOfVertexes_;
    std::vector<bool> isTerminate_;
public:
    Automat(std::vector<char> alphabet, size_t countOfVertexes, 
            std::vector<std::map<char, std::set<size_t>>> edges,
            std::set<size_t> terminateVertexes);
    Automat(size_t countOfVertexes, std::vector<char> alphabet);
    Automat();
    void addEdge(int from, char letter, int to);
    void addVertex();
    size_t countOfVertexes() const;
    std::set<size_t> getNextVertexes(size_t from, char at) const;
    bool existEdge(size_t from, char at) const;
    std::vector<char> getAlphabet() const;
    bool isTerminateVertex(size_t vertex) const;
    void changeTerminate(size_t vertex);
    bool operator==(const Automat& automat);
    friend std::ostream& operator <<(std::ostream& os, const Automat& automat);
};

std::istream& operator >>(std::istream& is, Automat& automat);
std::ostream& operator <<(std::ostream& os, const Automat& automat);