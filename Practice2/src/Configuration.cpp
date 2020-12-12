#include "Configuration.h"



Configuration::Configuration(const Rule& rule, int indOfCurrentPosition,
                             int indOfLastReadSymbol, int numberOfClass):
    rule(rule),
    indOfCurrentPosition(indOfCurrentPosition),
    indOfLastReadSymbol(indOfLastReadSymbol),
    numberOfClass(numberOfClass)
    {}

bool Configuration::isRuleRead() const {
    return indOfCurrentPosition == rule.rightPart.size();
}

char Configuration::getCurrentSymbol() const {
    return rule[indOfCurrentPosition];
}

char Configuration::getLeftSymbol() const {
    return rule.LeftSymbol;
}

std::set<Configuration> scan(const Configuration& conf, char letter) {
    if (conf.isRuleRead()) {
        return {};
    }
    if (conf.getCurrentSymbol() == letter) {
        Configuration ans = conf;
        ans.indOfCurrentPosition++;
        ans.numberOfClass++;
        return { ans };
    } else {
        return {};
    }
}

std::set<Configuration> predict(const Configuration& conf, const Rule& rule) {
    if (conf.getCurrentSymbol() != rule.LeftSymbol) {
        return {};
    }
    Configuration ans = Configuration(rule, 0, conf.numberOfClass, conf.numberOfClass);
    return { ans };
}

std::set<Configuration> complete(const Configuration& topConf,
                                 const Configuration& bottomConf) {
    if (!bottomConf.isRuleRead()) {
        return {};
    }
    if (topConf.getCurrentSymbol() != bottomConf.getLeftSymbol()) {
        return {};
    }
    if (topConf.numberOfClass != bottomConf.indOfLastReadSymbol) {
        return {};
    }
    Configuration ans = topConf;
    ans.indOfCurrentPosition++;
    ans.numberOfClass = bottomConf.numberOfClass;
    return { ans };
}

