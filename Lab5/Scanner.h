#include "Token.h"
#include <vector>
#include <fstream>
#include <iostream>
#pragma once

using namespace std;

class Scanner{
private:
    string file;
    int lineNum;
    char current;
    vector<Token> tokenVector;
    ifstream inputFile;
public:
    Scanner(string fileName);
    ~Scanner();
    void scan();
    void tokenize();
    void printVector();
    void stringCheck();
    void commentCheck();
    void multiLineCheck();
    void checkOther();
    vector<Token> getVector();
};