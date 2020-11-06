#include "main.h"

int main() {

    RegularHandler regularHandler;
    regularHandler.readInput();
    std::cout << regularHandler.getAnswer() << std::endl;

    return 0;
}