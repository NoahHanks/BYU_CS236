//
//  Scanner.h
//  Project 1
//
//  Created by Cam on 1/22/2019.
//  Copyright © 2019 Cameron Brown. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h

#include "Token.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Scanner {
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
    
private:
    string file;
    int lineNum;
    char current;
    vector<Token> tokenVector;
    ifstream inputFile;
};

#endif /* scanner.h */
