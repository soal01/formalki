#include <gtest/gtest.h>
#include "main.h"


TEST(RuleTest, ConstructorTest) {
    std::string str = "S->aSbS";
    Rule rule = Rule(str);
    ASSERT_EQ(rule.LeftSymbol == 'S' && rule.rightPart == "aSbS", true);
}

TEST(RuleTest, ConstructorWithEpsTest) {
    std::string str = "S->\\eps";
    Rule rule = Rule(str);
    ASSERT_EQ(rule.LeftSymbol == 'S' && rule.rightPart == "", true);
}

TEST(RuleTest, OperatorGetTest) {
    Rule rule = Rule("S->aSbS");
    ASSERT_EQ(rule[2] == 'b', true);
}

TEST(RuleTest, InputTest) {
    std::string str = "S->aSbS";
    Rule rule1 = Rule(str);
    Rule rule2;
    std::ifstream file;
    file.open("../testing/Rule.in");
    if (file.fail()){
        file.open("testing/Rule.in");
    }
    
	file >> rule2;
    file.close();
    ASSERT_EQ(rule1 == rule2, true);
}

TEST(GrammarTest, InputTest) {
    Rule rule1 = Rule("S->aSbS");
    Rule rule2 = Rule("S->bSaS");
    Grammar grammar1, grammar2;
    grammar1.rules.insert(rule1);
    grammar1.rules.insert(rule2);
    std::ifstream file;
    file.open("../testing/Grammar.in");
    if (file.fail()){
        file.open("testing/Grammar.in");
    }
    file >> grammar2;
	
    file.close();
    ASSERT_EQ(grammar1 == grammar2, true);
}



TEST(EarlyAlgorithmTest, InGrammarTest1) {
    Algo* algo = new EarleyAlgorithm();
    Grammar grammar;
    std::string str;
    std::ifstream file;
    file.open("../testing/InGrammarTest.in");
    if (file.fail()){
        file.open("testing/InGrammarTest.in");
    }
    file >> grammar;
    *algo = algo->fit(grammar); 
    file >> str;
    bool ans = algo->predict(str);
    file.close();
    ASSERT_EQ(ans, true);
}



TEST(EarleyAlgorithmTest, NotInGrammarTest1) {
    Algo* algo = new EarleyAlgorithm();
    Grammar grammar;
    std::string str;
    std::ifstream file;
    file.open("../testing/NotInGrammarTest.in");
    if (file.fail()){
        file.open("testing/NotInGrammarTest.in");
    }
    file >> grammar;
    *algo = algo->fit(grammar); 
    file >> str;
    bool ans = algo->predict(str);
    file.close();
    ASSERT_EQ(ans, false);
}

TEST(EarleyAlgorithmTest, InGrammarTest2) {
    Algo* algo = new EarleyAlgorithm();
    Grammar grammar;
    std::string str;
    std::ifstream file;
    file.open("../testing/InGrammarTest2.in");
    if (file.fail()){
        file.open("testing/InGrammarTest2.in");
    }
    file >> grammar;
    *algo = algo->fit(grammar); 
    file >> str;
    bool ans = algo->predict(str);
    file.close();
    ASSERT_EQ(ans, true);
}

TEST(EarleyAlgorithmTest, NotInGrammarTest2) {
    Algo* algo = new EarleyAlgorithm();
    Grammar grammar;
    std::string str;
    std::ifstream file;
    file.open("../testing/NotInGrammarTest2.in");
    if (file.fail()){
        file.open("testing/NotInGrammarTest2.in");
    }
    file >> grammar;
    *algo = algo->fit(grammar); 
    file >> str;
    bool ans = algo->predict(str);
    file.close();
    ASSERT_EQ(ans, false);
}


TEST(ScanTest, NothingToReadTest) {
    Configuration conf(Rule("S->aSbS"), 4, 3, 0);
    char letter = 'a';
    auto ans = Scan(conf, letter);
    ASSERT_EQ(ans.size(), 0);
}

TEST(ScanTest, AnotherLetterTest) {
    Configuration conf(Rule("S->aSbS"), 2, 3, 0);
    char letter = 'a';
    auto ans = Scan(conf, letter);
    ASSERT_EQ(ans.size(), 0);
}

TEST(ScanTest, SuccessfulScanTest) {
    Configuration conf(Rule("S->aSbS"), 0, 0, 0);
    char letter = 'a';
    Configuration ansConf(Rule("S->aSbS"), 1, 0, 1);
    auto ans = Scan(conf, letter);
    ASSERT_EQ(*(ans.begin()) == ansConf, true);
}

TEST(PredictTest, AnotherLetterTest) {
    Configuration conf(Rule("S->aSbS"), 0, 2, 0);
    Rule rule("S->aaa");
    auto ans = Predict(conf, rule);
    ASSERT_EQ(ans.size(), 0);
}

TEST(PredictTest, SuccessfulPredictTest) {
    Configuration conf(Rule("S->aSbS"), 1, 2, 1);
    Rule rule("S->aaa");
    auto ans = Predict(conf, rule);
    Configuration ansConf(Rule("S->aaa"), 0, 1, 1);
    ASSERT_EQ(*(ans.begin()), ansConf);
}

TEST(CompleteTest, NothingToCompleteTest) {
    Configuration topConf(Rule("S->aSbS"), 4, 3, 3);
    Configuration bottomConf(Rule("S->aaa"), 3, 3, 5);
    auto ans = Complete(topConf, bottomConf);
    ASSERT_EQ(ans.size(), 0);
}

TEST(CompleteTest, AnotherLetterTest) {
    Configuration topConf(Rule("S->aSbS"), 3, 3, 3);
    Configuration bottomConf(Rule("T->aaa"), 3, 3, 5);
    auto ans = Complete(topConf, bottomConf);
    ASSERT_EQ(ans.size(), 0);
}

TEST(CompleteTest, AnotherClassesTest) {
    Configuration topConf(Rule("S->aSbS"), 3, 3, 3);
    Configuration bottomConf(Rule("S->aaa"), 3, 2, 5);
    auto ans = Complete(topConf, bottomConf);
    ASSERT_EQ(ans.size(), 0);
}

TEST(CompleteTest, NotReadConfigurationTest) {
    Configuration topConf(Rule("S->aSbS"), 3, 3, 3);
    Configuration bottomConf(Rule("S->aaa"), 2, 3, 5);
    auto ans = Complete(topConf, bottomConf);
    ASSERT_EQ(ans.size(), 0);
}

TEST(CompleteTest, SuccessfulCompleteTest) {
    Configuration topConf(Rule("S->aSbS"), 3, 3, 3);
    Configuration bottomConf(Rule("S->aaa"), 3, 3, 5);
    auto ans = Complete(topConf, bottomConf);
    Configuration ansConf(Rule("S->aSbS"), 4, 3, 5);
    ASSERT_EQ(*(ans.begin()), ansConf);
}