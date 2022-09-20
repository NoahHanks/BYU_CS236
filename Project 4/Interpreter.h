#include <stdio.h>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Database.h"
#pragma once

using namespace std;

class Interpreter {
private:
    DatalogProgram datalog;
    vector<Predicate> schemeVector;
    vector<Predicate> factVector;
    vector<Rule> ruleVector;
    vector<Predicate> queryVector; 
    Database database;
public:
    Interpreter();
    Interpreter(DatalogProgram data);
    ~Interpreter();
    Relation evalOnePredicate(Predicate myPredicate);
    void evalOneRule(Rule myRule);
    void evalAllRules();
    void evalAllQueries();
};