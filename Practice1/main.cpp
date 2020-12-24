#include "main.h"

int main() {

    RegularHandler regularHandler;
    regularHandler.readInput(std::cin);
    regularHandler.print();
    int ans = regularHandler.getAnswer();
    if (ans == INF) {
        std::cout << "INF" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }

    return 0;
}