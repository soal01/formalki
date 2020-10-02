#include<iostream>
#include<vector>
#include<map>

size_t INF = 1e9;

class Automat {
private:
    std::vector<char> alphabet_;
    std::vector<std::map<char, size_t>> edges_;
    std::vector<size_t> vertexes_;
    std::vector<bool> isTerminate_;
public:
    Automat(std::vector<char> alphabet, std::vector<size_t> vertexes, 
            std::vector<std::map<char, size_t>> edges,
            std::vector<size_t> terminateVertexes)
            :alphabet_(alphabet_),
            edges_(edges),
            vertexes_(vertexes),
            isTerminate_(vertexes.size(), false)
            {
                for (auto u: terminateVertexes) {
                    isTerminate_[u] = true;
                }
            }
    
    void addEdge(int from, char letter, int to);
    size_t countOfVertexes() const;
    size_t getVertex(size_t from, char at) const;
    std::vector<char> getAlphabet() const;
    bool isTerminateVertex(size_t vertex) const;
};