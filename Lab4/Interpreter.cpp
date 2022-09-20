//
//  Interpreter.cpp
//  Project3
//
//  Created by Cam on 3/5/19.
//  Copyright © 2019 Cam. All rights reserved.
//

#include "Interpreter.h"

Interpreter :: Interpreter() {

}

Interpreter :: Interpreter(DatalogProgram data) {
    // Store the DatalogProgram as a data member
    datalog = data;
    schemeVector = data.getSchemes();
    factVector = data.getFacts();
    ruleVector =  data.getRules();
    queryVector = data.getQueries();
    
    // Make a Relation for each scheme Predicate, and put that Relation in the Database data member
    for(int i = 0; i < (int)schemeVector.size(); ++i){
        string schemeName = schemeVector.at(i).getID();
        vector<Parameter> schemeParams = schemeVector.at(i).getParameters();
        Scheme scheme;
        for(int j = 0; j < (int)schemeParams.size(); ++j){
            string value = schemeParams.at(j).getValue();
            scheme.push_back(value);
        }
        Relation newRelation(schemeName, scheme);
        database.insert(pair<string, Relation>(schemeName, newRelation));
    }
    
    // Make a Tuple for each fact Predicate, and put that Tuple in the appropriate Relation in the Database
    for(int i = 0; i < (int)factVector.size(); ++i){
        string factName = factVector.at(i).getID();
        vector<Parameter> factParams = factVector.at(i).getParameters();
        Tuple tuple;
        for(int j = 0; j < (int)factParams.size(); ++j){
            string value = factParams.at(j).getValue();
            tuple.push_back(value);
        }
        (database.at(factName)).addTuple(tuple);
    }
}

Interpreter :: ~Interpreter() {
    
}

Relation Interpreter :: evalOnePredicate(Predicate myPredicate) {
    string predicateName = myPredicate.getID();
    Relation myRelation = database.at(predicateName);
    vector<Parameter> predParams = myPredicate.getParameters();
    vector<int> positions;
    vector<string> variableNames;
    map<string, int> variables;
    for(int i = 0; i < (int)predParams.size(); i++) {
        if((predParams.at(i).getIsConstant()) == true) {
            myRelation = myRelation.select(predParams.at(i).getValue(), i, myRelation);
        }
        else {
            map<string, int> :: iterator duplicate = variables.find(predParams.at(i).getValue());
            if(duplicate == variables.end()) {
                positions.push_back(i);
                variableNames.push_back(predParams.at(i).getValue());
                variables.insert(pair<string, int>(predParams.at(i).getValue(), i));
            }
            else {
                myRelation = myRelation.select(duplicate->second, i, myRelation);
            }
        }
        
    }
    myRelation = myRelation.project(positions, myRelation);
    myRelation = myRelation.rename(variableNames, myRelation);
    
    return myRelation;
}

void Interpreter :: evalOneRule(Rule myRule) {

    vector<Predicate> rulePreds = myRule.getPredicateList();
    vector<Relation> relVec;
    for(Predicate x : rulePreds) {
        Relation newRelation = evalOnePredicate(x);
        relVec.push_back(newRelation);
    }
    int relVecSize = (int)relVec.size();
    for(int i = 0; i < relVecSize; i++) {
        if(i == relVecSize - 1) {
            break;
        }
        else {
            relVec.at(i+1) = relVec.at(i).join(relVec.at(i), relVec.at(i+1));
        }
    }
    Relation newRelation = relVec.at(relVecSize-1);
    
    Predicate headPredicate = myRule.getHeadPredicate();
    vector<Parameter> headPredParams = headPredicate.getParameters();
    int headPredSize = (int)headPredParams.size();
    int relParamSize = (int)newRelation.getScheme().size();
    vector<int> positions;
    vector<string> renameVals;
    for(int i = 0; i < headPredSize; i++){
        for(int j = 0; j < relParamSize; j++) {
            if(headPredParams.at(i).getValue() == newRelation.getScheme().at(j)){
                positions.push_back(j);
            }
        }
        renameVals.push_back(headPredParams.at(i).getValue());
    }
    
    newRelation = newRelation.project(positions, newRelation, renameVals);
    newRelation = newRelation.rename(renameVals, newRelation);
    database.at(headPredicate.getID()).unite(newRelation);
}

void Interpreter :: evalAllRules() {
    int sizeBefore = 0;
    int sizeAfter = 0;
    int numPasses = 0;
    cout << "Rule Evaluation" << endl;
    do{
        sizeBefore = database.getSize();
        for(int i = 0; i < (int)ruleVector.size(); i++){
            cout << ruleVector.at(i).toString();
            evalOneRule(ruleVector.at(i));
            cout << endl;
        }
        sizeAfter = database.getSize();
        numPasses++;
    } while(sizeBefore != sizeAfter);
    cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl << endl;
}

void Interpreter :: evalAllQueries() {
    cout << "Query Evaluation" << endl;
    for(int i = 0; i < (int)queryVector.size(); ++i) {
        Relation newRelation = evalOnePredicate(queryVector.at(i));
        cout << queryVector.at(i).toString() << "? ";
        if(newRelation.getSet().empty()) {
            cout << "No";
        }
        else {
            cout << "Yes(" << (int)newRelation.getSet().size() << ")";
            cout << newRelation.toString();
        }
        if(i != (int)queryVector.size()-1) {
            cout << endl;
        }
    }
}

void Interpreter :: test1() {
     Relation relation1 = database.at("snap");
     Relation relation2 = database.at("csg");
     Relation newRelation = database.at("Grades");
     newRelation = newRelation.join(relation1, relation2);
     cout << newRelation.toString();
     cout << endl;
    /*
     relation1 = database.at("snap");
     relation2 = database.at("cp");
     newRelation.join(relation1, relation2);
     cout << endl;
     relation1 = database.at("snap");
     relation2 = database.at("cdh");
     newRelation.join(relation1, relation2);
     cout << endl;
     relation1 = database.at("snap");
     relation2 = database.at("cr");
     newRelation.join(relation1, relation2);
     cout << endl;
     relation1 = database.at("csg");
     relation2 = database.at("snap");
     newRelation.join(relation1, relation2);
     cout << endl;
     */
}


