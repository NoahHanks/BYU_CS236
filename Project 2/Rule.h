#include <stdio.h>
#include <sstream>
#include "Predicate.h"
#pragma once

using namespace std;

class Rule {
private:
    vector<Predicate> predicateList;
    Predicate predicate;
public:
Rule(){
    predicate = Predicate();
    predicateList = vector<Predicate>();
}

~Rule() {}

Rule(Predicate p){
    predicate = p;
    predicateList = vector<Predicate>();
}

Rule(Predicate p, vector<Predicate> pList){
    predicate = p;
    predicateList = pList;
}

void addPredicate(Predicate pred){ predicateList.push_back(pred); }
Predicate getPredicate(){ return predicate; }
vector<Predicate> getPredicateList(){ return predicateList; }

string toString(){
    stringstream ss;
    ss << predicate.toString() << " :- ";
    for(int i = 0; i < (int)predicateList.size(); i++)
        if(i == 0)
            ss << predicateList[i].toString();
        else
            ss << "," + predicateList[i].toString();
    ss << ".";
    return ss.str();
}

};