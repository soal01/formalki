#include"automat.h"


Automat::Automat(std::vector<char> alphabet, size_t countOfVertexes, 
            std::vector<std::map<char, std::set<size_t>>> edges,
            std::set<size_t> terminateVertexes)
            :alphabet_(alphabet),
            edges_(edges),
            countOfVertexes_(countOfVertexes),
            isTerminate_(countOfVertexes, false)
            {
                for (auto u: terminateVertexes) {
                    isTerminate_[u] = true;
                }
            }

Automat::Automat(size_t countOfVertexes, std::vector<char> alphabet)
                :alphabet_(alphabet),
                edges_(countOfVertexes),
                countOfVertexes_(countOfVertexes),
                isTerminate_(countOfVertexes_, false)
                {
                    countOfVertexes_=countOfVertexes;
                }

Automat::Automat()
                :alphabet_(),
                edges_(),
                countOfVertexes_(0),
                isTerminate_()
                {}
            
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

void Automat::addVertex() {
    countOfVertexes_++;
    isTerminate_.push_back(false);
    edges_.push_back(std::map<char, std::set<size_t>>());
}

void Automat::changeTerminate(size_t vertex) {
    isTerminate_[vertex] = !isTerminate_[vertex];
}

std::istream& operator >>(std::istream& is, Automat& automat) {
    size_t countOfVertexes;
    is >> countOfVertexes;
    size_t sizeOfAlphabet;
    is >> sizeOfAlphabet;
    std::vector<char> alphabet;
    for (size_t i = 0; i < sizeOfAlphabet; ++i) {
        char alpha;
        do {
            is >> alpha;
            //std::cout<<"alpha="<<alpha
        } while (alpha == ' ');
        alphabet.push_back(alpha);
    }
    //std::cout<<"correct"<<std::endl;
    automat = Automat(countOfVertexes, alphabet);
    size_t countOfEdges;
    is >> countOfEdges;
    for (size_t i = 0; i < countOfEdges; ++i) {
        size_t from, to;
        char alpha;
        is >> from;
        do {
            is >> alpha;
        } while (alpha == ' ');
        is >> to;
        automat.addEdge(from, alpha, to);
    }
    //std::cout<<"correct"<<std::endl;
    size_t countOfTerminateVertexes;
    is >> countOfTerminateVertexes;
    for (size_t i = 0; i < countOfTerminateVertexes; ++i) {
        size_t vertex;
        is >> vertex;
        automat.changeTerminate(vertex);
    }
    return is;
}


std::ostream& operator <<(std::ostream& os, const Automat& automat) {
    os << "Edges: \n";
    for (size_t vertex = 0; vertex < automat.countOfVertexes_; ++vertex) {
        for (char alpha : automat.alphabet_) {
            std::set<size_t> nextVertexes = automat.getNextVertexes(vertex, alpha);
            for (size_t nextVertex : nextVertexes) {
                os << "<" << vertex << "," << alpha << "> --> " << nextVertex << "\n";
            }
        }
    }
    os << "Terminal vertexes:\n";
    for (size_t vertex = 0; vertex < automat.countOfVertexes_; ++vertex) {
        if (automat.isTerminate_[vertex])
            os << vertex << " ";
    }
    os << "\n";
    return os;
}

bool Automat::existEdge(size_t from, char at) const {
    return edges_[from].find(at) != edges_[from].end();
}

bool Automat::operator==(const Automat& automat) {
    if (alphabet_ != automat.getAlphabet())
        return false;
    if (countOfVertexes_ != automat.countOfVertexes())
        return false;
    for (size_t vertex = 0; vertex < countOfVertexes_; ++vertex) {
        if (isTerminate_[vertex] != automat.isTerminateVertex(vertex))
            return false;
    }
    for (size_t vertex = 0; vertex < countOfVertexes_; ++vertex) {
        for (char alpha : alphabet_) {
            if (existEdge(vertex, alpha) != automat.existEdge(vertex, alpha)) 
                return false;
            if (existEdge(vertex, alpha)) {
                if (getNextVertexes(vertex, alpha) != automat.getNextVertexes(vertex, alpha))
                    return false;
            }
        }
    }
    return true;
}