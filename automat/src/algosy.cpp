#include"algosy.h"
#include<queue>
#include<string>
#include<set>


Automat determinateAutomat(const Automat& automat) {
    //std::vector<bool> used;
    std::queue<std::set<size_t> > unprocessedVertexes;
    std::vector<std::map<char, std::set<size_t>>> newEdges(1);
    std::map<std::set<size_t>, size_t> newNames;
    newNames[{0}] = 0;
    unprocessedVertexes.push({0});
    while (!unprocessedVertexes.empty()) {
        //std::cout<<"ha"<<std::endl;
        std::set<size_t> vertex = unprocessedVertexes.front();
        unprocessedVertexes.pop();
        for (char alpha : automat.getAlphabet()) {
            std::set<size_t> nextVertex;
            for (size_t simpleVertex : vertex) {
                std::set<size_t> nextSimpleVertexes = automat.getNextVertexes(simpleVertex, alpha);
                if (nextSimpleVertexes.size() != 0)
                    nextVertex.merge(nextSimpleVertexes);
            }

            if (nextVertex == std::set<size_t>())
                continue;

            if (newNames.find(nextVertex) == newNames.end()) {
                size_t countOfNames = newNames.size();
                newNames[nextVertex] = countOfNames;
                unprocessedVertexes.push(nextVertex);
                newEdges.push_back(std::map<char, std::set<size_t>>());
            } 
            newEdges[newNames[vertex]][alpha].insert(newNames[nextVertex]);
        }
    } 
    std::set<size_t> terminateVertexes;
    bool isNextNewVertex;
    for (auto newVertex : newNames) {
        std::set<size_t> vertex = newVertex.first;
        isNextNewVertex = false;
        for (size_t simpleVertex : vertex) {
            if (automat.isTerminateVertex(simpleVertex)) {
                terminateVertexes.insert(newNames[vertex]);
                isNextNewVertex = true;
                break;
            }
        }
        if (isNextNewVertex)
            continue;
    }
    return Automat(automat.getAlphabet(), newNames.size(),
                    newEdges, terminateVertexes);
}




Automat minimizeFullDeterminateAutomat(const Automat& automat) {
    std::map<std::set<size_t>, size_t> newNames;
    std::map<size_t, size_t> classes;
    std::map<size_t, std::string> strOfVertex;
    std::map<std::string, size_t> classOfStr;
    std::vector<std::map<char, std::set<size_t>>> newEdges;
    size_t oldClassesCount = 1;
    for (size_t i = 0; i < automat.countOfVertexes(); ++i) {
        if (automat.isTerminateVertex(i)) {
            classes[i] = 1;
        } else {
            classes[i] = 0;
            oldClassesCount = 2;
        }
    }
    size_t nextClassesCount = oldClassesCount;
    do {
        oldClassesCount = nextClassesCount;
        newEdges.clear();
        classOfStr.clear();
        strOfVertex.clear();
        newEdges=std::vector<std::map<char, std::set<size_t>>>(nextClassesCount);
        for (size_t vertex = 0; vertex < automat.countOfVertexes(); ++vertex) {
            std::string eqStr = std::to_string(classes[vertex]);
            for (char alpha : automat.getAlphabet()) {
                size_t nextVertex = *(automat.getNextVertexes(vertex, alpha).begin());
                eqStr += " " + std::to_string(classes[nextVertex]);
                newEdges[classes[vertex]][alpha] = {classes[nextVertex]};
            }
            strOfVertex[vertex] = eqStr;
            if (classOfStr.find(eqStr) == classOfStr.end()) {
                classOfStr[eqStr] = classOfStr.size();
                newEdges.push_back(std::map<char, std::set<size_t>>());
            }
        }
        nextClassesCount = classOfStr.size();
        for (size_t vertex = 0; vertex < automat.countOfVertexes(); ++vertex) {
            classes[vertex] = classOfStr[strOfVertex[vertex]];
        }
    } while(oldClassesCount < nextClassesCount);
    std::set<size_t> newTerminateVertexes;
    for (size_t vertex = 0; vertex < automat.countOfVertexes(); ++vertex) {
        if (automat.isTerminateVertex(vertex)) {
            newTerminateVertexes.insert(classes[vertex]);
        }
        
    }
    return Automat(automat.getAlphabet(), oldClassesCount,
                    newEdges, newTerminateVertexes);
}


bool isFullAutomat(const Automat& automat) {
    for (size_t vertex = 0; vertex < automat.countOfVertexes(); ++vertex) {
        for (char alpha : automat.getAlphabet()) {
            std::set<size_t> nextVertexes = automat.getNextVertexes(vertex, alpha);
            if (nextVertexes.size() == 0) 
                return false;
        }
    }
    return true;
}


void makeFull(Automat& automat) {
    size_t newVertex = automat.countOfVertexes();
    automat.addVertex();
    for (size_t vertex = 0; vertex < automat.countOfVertexes(); ++vertex) {
        for (char alpha : automat.getAlphabet()) {
            std::set<size_t> nextVertexes = automat.getNextVertexes(vertex, alpha);
            if (nextVertexes.size() == 0) {
                automat.addEdge(vertex, alpha, newVertex);
            }
        }
    }
}

Automat makeMinimalDeterminateAutomat(const Automat& automat) {
    Automat answer = automat;
    answer = determinateAutomat(answer);
    if (!isFullAutomat(answer)) {
        makeFull(answer);
    }
    answer = minimizeFullDeterminateAutomat(answer);
    return answer;
}