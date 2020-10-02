#include"automat.h"



void Automat::addEdge(int from, char letter, int to) {
    edges_[from][letter] = to;
}

size_t Automat::countOfVertexes() const {
    return vertexes_.size();
}

size_t Automat::getVertex(size_t from, char at) const {
    if (edges_[from].find(at) != edges_[from].end()) {
        return edges_[from][at];
    } else {
        return INF;
    }
}

std::vector<char> Automat::getAlphabet() const {
    return alphabet_;
}

bool Automat::isTerminateVertex(size_t vertex) const {
    return isTerminate_[vertex];
}