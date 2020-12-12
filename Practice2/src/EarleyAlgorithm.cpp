#include "EarleyAlgorithm.h"


EarleyAlgorithm::EarleyAlgorithm() {

}

EarleyAlgorithm& EarleyAlgorithm::fit(const Grammar& G) {
    grammar = G;
    Rule firstRule = Rule("$->S");
    grammar.rules.insert(firstRule);
}

void EarleyAlgorithm::completeForClass(int numberOfClass) {
    for (auto bottomConf : classes[numberOfClass]) {
        int numberOfTopClass = bottomConf.indOfLastReadSymbol;
        for (auto topConf : classes[numberOfTopClass]) {
            auto newConf = complete(topConf, bottomConf);
            classes[numberOfClass].insert(newConf.begin(), newConf.end());
        }
    }
}

void EarleyAlgorithm::predictForClass(int numberOfClass) {
    for (auto conf : classes[numberOfClass]) {
        for (auto rule : grammar.rules) {
            auto newConf = predict(conf, rule);
            classes[numberOfClass].insert(newConf.begin(), newConf.end());
        }
    }
}

void EarleyAlgorithm::scanForClass(int numberOfClass) {
    char letter = str[numberOfClass];
    for (auto conf : classes[numberOfClass]) {
        auto newConf = scan(conf, letter);
        classes[numberOfClass+1].insert(newConf.begin(), newConf.end());
    }
}


bool EarleyAlgorithm::predict(const std::string& str) {
    int n = str.size();
    classes.resize(n + 1);
    Configuration firstConfiguration = Configuration(Rule("$->S"), 0, 0, 0);
    classes[0].insert(firstConfiguration);
    int oldSize = 0;
    while (classes[0].size() > oldSize) {
        oldSize = classes[0].size();
        completeForClass(0);
        predictForClass(0);
    }
    for (int i = 0; i < n; ++i) {
        scanForClass(i);
        oldSize = 0;
        while (classes[i + 1].size() > oldSize) {
            oldSize = classes[i + 1].size();
            completeForClass(i + 1);
            predictForClass(i + 1);
            
        }
    }
    Configuration finalConfiguration = Configuration(Rule("$->S"), 1, 0, n);
    return classes[n].find(finalConfiguration) != classes[n].end();
}