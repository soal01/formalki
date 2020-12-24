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

std::set<Configuration> Scan(const Configuration& conf, char letter) {
    std::cout << "Scan " << conf << std::endl;
    if (conf.isRuleRead()) {
        return {};
    }
    if (conf.getCurrentSymbol() == letter) {
        std::cout << "Scan " << conf << std::endl;
        Configuration ans = conf;
        ans.indOfCurrentPosition++;
        ans.numberOfClass++;
        std::cout << ans << std::endl;
        return { ans };
    } else {
        return {};
    }
}

std::set<Configuration> Predict(const Configuration& conf, const Rule& rule) {
    if (conf.getCurrentSymbol() != rule.LeftSymbol) {
        return {};
    }
    Configuration ans = Configuration(rule, 0, conf.numberOfClass, conf.numberOfClass);
    return { ans };
}

std::set<Configuration> Complete(const Configuration& topConf,
                                 const Configuration& bottomConf) {
    if (topConf.isRuleRead()) {
        return {};
    }
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

bool operator <(const Configuration& first, const Configuration& second) {
    if (first.rule == second.rule) {
        if (first.indOfCurrentPosition == second.indOfCurrentPosition) {
            if (first.indOfLastReadSymbol == second.indOfLastReadSymbol) {
                return first.numberOfClass < second.numberOfClass;
            } else {
                return first.indOfLastReadSymbol < second.indOfLastReadSymbol;
            }
        } else {
            return first.indOfCurrentPosition < second.indOfCurrentPosition;
        }
    } else {
        return first.rule < second.rule;
    }
}

bool operator ==(const Configuration& first, const Configuration& second) {
    return !(first < second) && !(second < first);
}

std::ostream& operator <<(std::ostream& os, const Configuration& conf) {
    os << conf.rule.LeftSymbol<<"->"<<conf.rule.rightPart;
    os << " " << conf.indOfCurrentPosition << " " << conf.indOfLastReadSymbol;
    os << " " << conf.numberOfClass << "\n";
    return os;
}