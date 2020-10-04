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
            /*:alphabet_(alphabet_),
            edges_(edges),
            countOfVertexes_(countOfVertexes),
            isTerminate_(countOfVertexes, false)
            {
                for (auto u: terminateVertexes) {
                    isTerminate_[u] = true;
                }
            }*/
    
    void addEdge(int from, char letter, int to);
    size_t countOfVertexes() const;
    std::set<size_t> getNextVertexes(size_t from, char at) const;
    std::vector<char> getAlphabet() const;
    bool isTerminateVertex(size_t vertex) const;
};