#include"algosy.h"
#include<queue>
#include<string>
#include<set>


Automat determinateAutomat(const Automat& automat) {
    //std::vector<bool> used;
    std::queue<std::set<size_t> > unprocessedVertexes;
    std::vector<std::map<char, size_t>> newEdges;
    std::map<std::set<size_t>, size_t> newNames;
    unprocessedVertexes.push({0});
    while (!unprocessedVertexes.empty()) {
        std::set<size_t> vertex = unprocessedVertexes.front();
        unprocessedVertexes.pop();
        for (char alpha : automat.getAlphabet()) {
            std::set<size_t> nextVertex;
            for (size_t simpleVertex : vertex) {
                size_t nextSimpleVertex = automat.getVertex(simpleVertex, alpha);
                if (nextSimpleVertex != INF)
                    nextVertex.insert(nextSimpleVertex);
            }

            if (nextVertex == std::set<size_t>())
                continue;

            if (newNames.find(nextVertex) == newNames.end()) {
                newNames[nextVertex] = newNames.size();
                unprocessedVertexes.push(nextVertex);
            } 
            newEdges[newNames[vertex]][alpha] = newNames[nextVertex];
        }
    } 
    std::vector<size_t> newVertexes(newNames.size());
    std::vector<size_t> terminateVertexes;
    bool isNextNewVertex;
    for (auto newVertex : newNames) {
        std::set<size_t> vertex = newVertex.first;
        isNextNewVertex = false;
        for (size_t simpleVertex : vertex) {
            if (automat.isTerminateVertex(simpleVertex)) {
                terminateVertexes.push_back(newNames[vertex]);
                isNextNewVertex = true;
                break;
            }
        }
        if (isNextNewVertex)
            continue;
    }
    return Automat(automat.getAlphabet(), newVertexes,
                    newEdges, terminateVertexes);
}