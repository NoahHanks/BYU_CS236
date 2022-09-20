#include <string>
#include <iostream>
#include <iostream>
#include <vector>
#pragma once

using namespace std;

enum TokenType { COMMA, PERIOD, COLON_DASH, COLON, Q_MARK, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, STRING, COMMENT, END, UNDEFINED, LEFT_PAREN, RIGHT_PAREN, ID
};

class Token{
private:
    TokenType type;
    string value;
    int lineNum;
public:
Token(){}
~Token(){}

Token(TokenType t, string val, int numLine){
    type = t;
    value = val;
    lineNum = numLine;
}

TokenType getTokenType(){ return type; }
string getValue(){ return value; }

void printToken(){
    cout << "(" << toString() << "," << "\"" << value << "\"," << lineNum << ")";
}

string toString(){
    switch(type){
        case(COMMA): return "COMMA"; break;
        case(PERIOD): return "PERIOD"; break;
        case(COLON_DASH): return "COLON_DASH"; break;
        case(COLON): return "COLON"; break;
        case(Q_MARK): return "Q_MARK"; break;
        case(MULTIPLY): return "MULTIPLY"; break;
        case(ADD): return "ADD"; break;
        case(SCHEMES): return "SCHEMES"; break;
        case(FACTS): return "FACTS"; break;
        case(RULES): return "RULES"; break;
        case(QUERIES): return "QUERIES"; break;
        case(STRING): return "STRING"; break;
        case(COMMENT): return "COMMENT"; break;
        case(END): return "EOF"; break;
        case(UNDEFINED): return "UNDEFINED"; break;
        case(LEFT_PAREN): return "LEFT_PAREN"; break;
        case(RIGHT_PAREN): return "RIGHT_PAREN"; break;
        case(ID): return "ID"; break;
        default: return ""; break;
    }
}

};