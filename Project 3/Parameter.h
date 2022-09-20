#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class Parameter{
private:
    string value;
    string type;
    bool isConstant; // Changes for Project 3.
public:

Parameter(){
    value = "";
    type = "";
}

Parameter(string val){
    value = val;
    type = "";
}

Parameter(string val, string tokenType){
    value = val;
    type = tokenType;
}

~Parameter(){}

string getValue(){ return value; }
string toString(){ return value; }
string getType(){ return type; }
void setValue(string val){ value = val; }
// Changes for Project 3.
bool getIsConstant() { return isConstant; }
void setIsConstant(bool b) { isConstant = b; }
};