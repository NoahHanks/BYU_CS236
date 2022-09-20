#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class Parameter{
public:
    Parameter();
    Parameter(string val);
    Parameter(string val, string tokenType);
    ~Parameter();
    string getValue();
    string toString();
    string getType();
    void setValue(string val);
    bool getIsConstant();
    void setIsConstant(bool tf);
private:
    bool isConstant;
    string value;
    string type;
};