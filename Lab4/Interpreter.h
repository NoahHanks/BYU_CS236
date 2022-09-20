//
//  Interpreter.h
//  Project3
//
//  Created by Cam on 3/5/19.
//  Copyright © 2019 Cam. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter {
public:
    Interpreter();
    Interpreter(DatalogProgram data);
    ~Interpreter();
    Relation evalOnePredicate(Predicate myPredicate);
    void evalOneRule(Rule myRule);
    void evalAllRules();
    void evalAllQueries();
    
    //Testing
    void test1();
private:
    DatalogProgram datalog;
    vector<Predicate> schemeVector;
    vector<Predicate> factVector;
    vector<Rule> ruleVector;
    vector<Predicate> queryVector; 
    Database database;
    
};

#endif /* Interpreter_h */
