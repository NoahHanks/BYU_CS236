#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include "Node.h"

using namespace std;
#pragma once

class Interpreter {
public:
    Interpreter();
    Interpreter(DatalogProgram data);
    ~Interpreter();
    Relation evalOnePredicate(Predicate myPredicate);
    void evalOneRule(Rule myRule);
    void evalAllRules();
    void evalAllQueries();
    void buildDependency();
    void buildReverse();
private:
    DatalogProgram datalog;
    vector<Predicate> schemeVector;
    vector<Predicate> factVector;
    vector<Rule> ruleVector;
    vector<Predicate> queryVector;
    Database database;
    Graph myGraph;
};