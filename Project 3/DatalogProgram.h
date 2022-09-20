#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

#include "Predicate.h"
#include "Rule.h"
#pragma once
using namespace std;

class DatalogProgram{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;
public:
/*datalogProgram ->	SCHEMES COLON scheme schemeList
		            FACTS COLON factList
		            RULES COLON ruleList
		            QUERIES COLON query queryList
			        EOF
            */
DatalogProgram(){
        schemes = vector<Predicate>();
        facts = vector<Predicate>();
        rules = vector<Rule>();
        queries = vector<Predicate>();
        domain = set<string>();
}
    
~DatalogProgram(){}

string toString(){
    stringstream ss;
    ss << "Success!";
    ss << endl << stringSchemes();
    ss << endl << stringFacts();
    ss << endl << stringRules() ;
    ss << endl << stringQueries();
    ss << endl << stringDomain();
    return ss.str();
}

vector<Predicate> getSchemes(){ return schemes; }
vector<Predicate> getFacts(){ return facts; }
vector<Rule> getRules(){ return rules; }
vector<Predicate> getQueries(){ return queries; }
set<string> getDomain(){ return domain; }
void addScheme(Predicate s){ schemes.push_back(s); }
void addQuery(Predicate query){ queries.push_back(query); }

void addFact(Predicate fact){
    facts.push_back(fact);
    addDomain(fact.getParameters());
}

void addRule(Rule rule){
    rules.push_back(rule);
    addDomain(rule.getPredicate().getParameters());
}

void addDomain(vector<Parameter> paramList){
    for(int i = 0; i < (int)paramList.size(); i++)
        if(paramList[i].getType() == "STRING")
            domain.insert(paramList[i].getValue()); 
}

string stringSchemes(){
    stringstream ss;
    ss << "Schemes(" << schemes.size() << "):";
    for(int i = 0; i < (int)schemes.size(); i++)
        ss << "\n  " << schemes[i].toString();
    return ss.str();
}

string stringDomain(){
    stringstream ss;
    ss << "Domain(" << domain.size() << "):";
    set<string>::iterator myIterator;
    for(myIterator = domain.begin(); myIterator != domain.end(); myIterator++)
        ss << "\n  " << (*myIterator);
    return ss.str();
}

string stringFacts(){
    stringstream ss;
    ss << "Facts(" << facts.size() << "):";
    for(int i = 0; i < (int)facts.size(); i++)
        ss << "\n  " << facts[i].toString() << ".";
    return ss.str();
}

string stringQueries(){
    stringstream ss;
    ss << "Queries(" << queries.size() << "):";
    for(int i = 0; i < (int)queries.size(); i++)
        ss << "\n  " << queries[i].toString() << "?";
    return ss.str();
}

string stringRules(){
    stringstream ss;
    ss << "Rules(" << rules.size() << "):";
    for(int i = 0; i < (int)rules.size(); i++)
        ss << "\n  " << rules[i].toString();
    return ss.str();
}
 
};