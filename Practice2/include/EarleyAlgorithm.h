#pragma once
#include "Algo.h"
#include <vector>
#include "Configuration.h"

class EarleyAlgorithm : public Algo {
private:
    std::vector<std::set<Configuration>> _classes;
    std::string _str;
    Grammar _grammar;

    void completeForClass(int numberOfClass);
    void predictForClass(int numberOfClass);
    void scanForClass(int numberOfClass);
public:
    EarleyAlgorithm();
    EarleyAlgorithm& fit(const Grammar& G) override;
    bool predict(const std::string& str) override;
};