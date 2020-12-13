#include "EarleyAlgorithm.h"


EarleyAlgorithm::EarleyAlgorithm() :
 _classes(),
 _str(),
 _grammar()
 {}

EarleyAlgorithm& EarleyAlgorithm::fit(const Grammar& G) {
    _grammar = G;
    Rule firstRule = Rule("$->S");
    _grammar.rules.insert(firstRule);
    return *this;
}

void EarleyAlgorithm::completeForClass(int numberOfClass) {
    for (auto bottomConf : _classes[numberOfClass]) {
        int numberOfTopClass = bottomConf.indOfLastReadSymbol;
        for (auto topConf : _classes[numberOfTopClass]) {
            auto newConf = Complete(topConf, bottomConf);
            _classes[numberOfClass].insert(newConf.begin(), newConf.end());
        }
    }
}

void EarleyAlgorithm::predictForClass(int numberOfClass) {
    for (auto conf : _classes[numberOfClass]) {
        for (auto rule : _grammar.rules) {
            auto newConf = Predict(conf, rule);
            _classes[numberOfClass].insert(newConf.begin(), newConf.end());
        }
    }
}

void EarleyAlgorithm::scanForClass(int numberOfClass) {
    char letter = _str[numberOfClass];
    for (auto conf : _classes[numberOfClass]) {
        auto newConf = Scan(conf, letter);
        _classes[numberOfClass+1].insert(newConf.begin(), newConf.end());
    }
}


bool EarleyAlgorithm::predict(const std::string& str) {
    int n = str.size();
    _str = str;
    _classes.resize(n + 1);
    Configuration firstConfiguration = Configuration(Rule("$->S"), 0, 0, 0);
    _classes[0].insert(firstConfiguration);
    int oldSize = 0;
    while (_classes[0].size() > oldSize) {
        oldSize = _classes[0].size();
        completeForClass(0);
        predictForClass(0);
    }
    for (int i = 0; i < n; ++i) {
        scanForClass(i);

        oldSize = 0;
        while (_classes[i + 1].size() > oldSize) {
            oldSize = _classes[i + 1].size();
            completeForClass(i + 1);
            predictForClass(i + 1);
        }
    }
    Configuration finalConfiguration = Configuration(Rule("$->S"), 1, 0, n);
    return _classes[n].find(finalConfiguration) != _classes[n].end();
}