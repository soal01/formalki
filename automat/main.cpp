#include"main.h"




int main() {
    Automat automat;
    std::cin >> automat;
    std::cout << automat;
    automat = determinateAutomat(automat);
    std::cout << automat;
    if (!isFullAutomat(automat)) {
        makeFull(automat);
    }
    std::cout<<"kek"<<std::endl;
    std::cout << automat;
    automat = minimizeFullDeterminateAutomat(automat);
    std::cout << automat;


    return 0;
}