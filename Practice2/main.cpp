#include "main.h"




int main() {
    Algo* parser = new EarleyAlgorithm();
    Grammar grammar;
    std::cin >> grammar;
    parser->fit(grammar);
    std::string str;
    std::cin >> str;
    std::cout << (parser->predict(str)) << std::endl;
    
    return 0;
}