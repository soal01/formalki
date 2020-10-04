#include"automat.h"


Automat::Automat(std::vector<char> alphabet, size_t countOfVertexes, 
            std::vector<std::map<char, std::set<size_t>>> edges,
            std::set<size_t> terminateVertexes)
            :alphabet_(alphabet_),
            edges_(edges),
            countOfVertexes_(countOfVertexes),
            isTerminate_(countOfVertexes, false)
            {
                for (auto u: terminateVertexes) {
                    isTerminate_[u] = true;
                }
            }

void Automat::addEdge(int from, char letter, int to) {
    edges_[from][letter].insert(to);
}

size_t Automat::countOfVertexes() const {
    return countOfVertexes_;
}

std::set<size_t> Automat::getNextVertexes(size_t from, char at) const {
    if (edges_[from].find(at) != edges_[from].end()) {
        return std::set<size_t>(edges_[from].at(at));
    } else {
        return std::set<size_t>();
    }
}

std::vector<char> Automat::getAlphabet() const {
    return alphabet_;
}

bool Automat::isTerminateVertex(size_t vertex) const {
    return isTerminate_[vertex];
}