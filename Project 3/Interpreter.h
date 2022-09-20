#include <string>
#include <vector>
#include <stdio.h>
#include "DatalogProgram.h"
#include "Database.h"
#pragma once
using namespace std;

class Interpreter{
private:
    DatalogProgram datalog;
    vector<Predicate> schemeVector;
    vector<Predicate> factVector;
    vector<Rule> ruleVector;
    vector<Predicate> queryVector; 
    Database database;
public:
    Interpreter(){}

Interpreter(DatalogProgram data){
    datalog = data;
    schemeVector = data.getSchemes();
    factVector = data.getFacts();
    ruleVector =  data.getRules();
    queryVector = data.getQueries();
    
    for(int i = 0; i < (int)schemeVector.size(); i++){
        string schemeName = schemeVector.at(i).getID();
        vector<Parameter> schemeParams = schemeVector.at(i).getParameters();
        Scheme scheme;
        for(int j = 0; j < (int)schemeParams.size(); j++){
            string value = schemeParams.at(j).getValue();
            scheme.push_back(value);
        }
        Relation newRelation(schemeName, scheme);
        database.insert(pair<string, Relation>(schemeName, newRelation));
    }
    for(int i = 0; i < (int)factVector.size(); i++){
        string factName = factVector.at(i).getID();
        vector<Parameter> factParams = factVector.at(i).getParameters();
        Tuple tuple;
        for(int j = 0; j < (int)factParams.size(); j++){
            string value = factParams.at(j).getValue();
            tuple.push_back(value);
        }
        (database.at(factName)).addTuple(tuple);
    }
}

~Interpreter(){}

Relation evalOneQuery(Predicate myQuery){
    string queryName = myQuery.getID();
    Relation myRelation = database.at(queryName);
    vector<Parameter> queryParams = myQuery.getParameters();
    vector<int> positions;
    vector<string> variableNames;
    map<string, int> variables;
    for(int i = 0; i < (int)queryParams.size(); i++){
        if((queryParams.at(i).getIsConstant()) == true)
            myRelation = myRelation.select(queryParams.at(i).getValue(), i, myRelation);
        else {
            map<string, int> :: iterator duplicate = variables.find(queryParams.at(i).getValue());
            if(duplicate == variables.end()){
                positions.push_back(i);
                variableNames.push_back(queryParams.at(i).getValue());
                variables.insert(pair<string, int>(queryParams.at(i).getValue(), i));
            }
            else
                myRelation = myRelation.select(duplicate->second, i, myRelation);
        }
        
    }
    myRelation = myRelation.project(positions, myRelation);
    myRelation = myRelation.rename(variableNames, myRelation);
    
    variables.clear();
    return myRelation;
}

void evalAllQueries(){
    for(int i = 0; i < (int)queryVector.size(); i++){
        Relation newRelation = evalOneQuery(queryVector.at(i));
        cout << queryVector.at(i).toString() << "? " << newRelation.toString();
        if(i != (int)queryVector.size() - 1)
            cout << endl;
    }
}

};