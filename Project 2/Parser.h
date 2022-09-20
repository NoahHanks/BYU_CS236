#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>

#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"

#pragma once
using namespace std;

class Parser {
private:
    Token current;
    vector<Token> tokenVector;
    DatalogProgram data;
    Predicate p;
    Rule r;
public:
Parser(string fileName){
    Scanner myScanner(fileName);
    myScanner.scan();
    tokenVector = myScanner.getVector();
    current = tokenVector.at(0);
}

~Parser(){}

void match(TokenType t){
    if(t == current.getTokenType()){
        tokenVector.erase(tokenVector.begin() + 0);
        current = tokenVector[0];
    }
    else
        throw current;
}

void parse(){
    try{
        // Check for schemes.
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        // Check for facts.
        match(FACTS);
        match(COLON);
        factList();
        // Check for rules.
        match(RULES);
        match(COLON);
        ruleList();
        // Check for quesries.
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        // Check for end of input.
        match(END);
        
        // cout << data.toString();
    }
    catch(Token error){
        cout << "Failure!" << endl << "  ";
        error.printToken();
    }
    
}

void scheme(){
    //scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    if (current.getTokenType() == ID)
        p.addParameter(Parameter(current.getValue(), current.toString()));
    match(ID);
    idList();
    match(RIGHT_PAREN);
    data.addScheme(p);
}

void schemeList(){
    // schemeList -> scheme schemeList | lambda
    if (current.getTokenType() != FACTS){
        scheme();
        schemeList();
    }
}

void fact(){
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    if (current.getTokenType() == STRING)
        p.addParameter(Parameter(current.getValue(), current.toString()));
    match(STRING);
    stringList();
    match(RIGHT_PAREN);
    match(PERIOD);
    data.addFact(p);
}

void factList(){
    // factList -> fact factList | lambda
    if(current.getTokenType() != RULES){
        fact();
        factList();
    }
}

void stringList(){
    // stringList -> COMMA STRING stringList | lambda
    if(current.getTokenType() != RIGHT_PAREN){
        match(COMMA);
        if (current.getTokenType() == STRING)
            p.addParameter(Parameter(current.getValue(), current.toString()));
        match(STRING);
        stringList();
    }
    
}

void rule(){
    // rule ->  headPredicate COLON_DASH predicate predicateList PERIOD
    p = headPredicate();
    r = Rule(p);
    match(COLON_DASH);
    r.addPredicate(predicate());
    predicateList();
    match(PERIOD);
    data.addRule(r);
}

void ruleList(){
    // ruleList ->  rule ruleList | lambda
    if(current.getTokenType() != QUERIES){
        rule();
        ruleList();
    }
}

void query(){
    // query -> predicate Q_MARK
    data.addQuery(predicate());
    match(Q_MARK);
}

void queryList(){
    // queryList -> query queryList | lambda
    if(current.getTokenType() != END){
        query();
        queryList();
    }
}

void idList(){
    // idList -> COMMA ID idList | lambda
    if(current.getTokenType() != RIGHT_PAREN){
        match(COMMA);
        if (current.getTokenType() == ID){
             p.addParameter(Parameter(current.getValue(), current.toString()));
        }
        match(ID);
        idList();
    }
}

Predicate headPredicate(){
    // headPredicate ->  ID LEFT_PAREN ID idList RIGHT_PAREN
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    if (current.getTokenType() == ID){
        p.addParameter(Parameter(current.getValue(), current.toString()));
    }
    match(ID);
    idList();
    match(RIGHT_PAREN);
    return p;
}

Predicate predicate(){
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    p = Predicate(current.getValue());
    match(ID);
    match(LEFT_PAREN);
    p.addParameter(parameter());
    parameterList();
    match(RIGHT_PAREN);
    return p;
}

void predicateList(){
    // predicateList -> COMMA predicate predicateList | lambda
    if(current.getTokenType() != PERIOD && current.getTokenType() != QUERIES){
        match(COMMA);
        r.addPredicate(predicate());
        predicateList();
    }
}

Parameter parameter(){
    //  parameter -> STRING | ID | expression
    Parameter newParam;
    if(current.getTokenType() == STRING){
        newParam.setValue(current.getValue());
        match(STRING);
    }
    else if(current.getTokenType() == ID){
        newParam.setValue(current.getValue());
        match(ID);
    }
    else if(current.getTokenType() == LEFT_PAREN){
        string val = "(";
        match(LEFT_PAREN);
        val += expression();
        match(RIGHT_PAREN);
        val += ")";
        newParam.setValue(val);
    }
    else
        throw current;
    return newParam;
}

void parameterList(){
    // parameterList -> COMMA parameter parameterList | lambda
    if(current.getTokenType() != RIGHT_PAREN){
        match(COMMA);
        p.addParameter(parameter());
        parameterList();
    }
}

string expression(){
    // expression -> LEFT_PAREN parameter operator parameter RIGHT_PAREN
    string express;
    express += parameter().getValue();
    express += operate();
    express += parameter().getValue();
    return express;
}

string operate(){
    // operator -> ADD | MULTIPLY
    if (current.getTokenType() == ADD){
        match(ADD);
        return "+";
    }
    else if (current.getTokenType() == MULTIPLY){
        match(MULTIPLY);
        return "*";
    }
    else{
        throw current;
    }
}

vector<Token> getTokenVector(){ return tokenVector; }
DatalogProgram getData(){ return data; }
Predicate getPredicate(){ return p; }
Rule getRule(){ return r; }
};