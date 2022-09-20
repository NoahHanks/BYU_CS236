#include <vector>
#include <fstream>
#include <iostream>
#include "Token.h"
#pragma once

using namespace std;

class Scanner {
private:
    string file;
    int lineNum;
    char current;
    vector<Token> tokenVector;
    ifstream inputFile;
public:
Scanner(string fileName){
    file = fileName;
    lineNum = 1;
    inputFile.open(file, ifstream::in);
}

~Scanner(){
    if(inputFile.is_open())
        inputFile.close();
}

void scan(){
    while(inputFile.is_open()){
        current = inputFile.get();
        switch(current){
            case ',':
                tokenVector.push_back(Token(COMMA, ",", lineNum));
                break;
            case '.':
                tokenVector.push_back(Token(PERIOD, ".", lineNum));
                break;
            case '?':
                tokenVector.push_back(Token(Q_MARK, "?", lineNum));
                break;
            case '*':
                tokenVector.push_back(Token(MULTIPLY, "*", lineNum));
                break;
            case '+':
                tokenVector.push_back(Token(ADD, "+", lineNum));
                break;
            case ')':
                tokenVector.push_back(Token(RIGHT_PAREN, ")", lineNum));
                break;
            case '(':
                tokenVector.push_back(Token(LEFT_PAREN, "(", lineNum));
                break;
            case ':':
                if(inputFile.peek() == '-'){
                    inputFile.get();
                    tokenVector.push_back(Token(COLON_DASH, ":-", lineNum));
                }
                else
                    tokenVector.push_back(Token(COLON, ":", lineNum));
                break;
            case EOF:
                tokenVector.push_back(Token(END, "", lineNum));
                inputFile.close();
                break;
            case '\'':
                stringCheck();
                break;
            case '#':
                commentCheck();
                break;
            case '\n':
                lineNum++;
                break;
            case '\t': break;
            case ' ': break;
            default:
                checkOther();
                break;
                
        }
        
    }
    
}

void stringCheck(){
    bool stringScan = true;
    string temp = "";
    temp += current;
    int lineStart = lineNum;
    while(stringScan){
        if(inputFile.peek() == '\''){
            current = inputFile.get();
            temp += current;
            if(inputFile.peek() == '\'')
                temp += inputFile.get();
            else{
                tokenVector.push_back(Token(STRING, temp, lineStart));
                stringScan = false;
                break;
            }
        }
        else if(inputFile.peek() == EOF){
            tokenVector.push_back(Token(UNDEFINED, temp, lineStart));
            stringScan = false;
            break;
        }
        else if(isspace(inputFile.peek())){
            if(inputFile.peek() == '\n')
                lineNum++;
            temp += inputFile.get();
        }
        else
            temp += inputFile.get();        
    }
}

void commentCheck(){
    if(inputFile.peek() == '|'){
        multiLineCheck();
        return;
    }
    bool commentScan = true;
    string temp = "";
    temp += current;
    while(commentScan){
        if(inputFile.peek() == '\n'){
            commentScan = false;
            break;
        }
        else if(inputFile.peek() == EOF){
            commentScan = false;
            break;
        }
        else
            temp += inputFile.get();
    }
}
void multiLineCheck(){
    bool commentScan = true;
    string temp = "";
    temp += current;
    int lineStart = lineNum;
    while(commentScan){
        if(inputFile.peek() == '|'){
            temp += inputFile.get();
            if(inputFile.peek() == '#'){
                temp += inputFile.get();
                commentScan = false;
                break;
            }
        }
        else if(inputFile.peek() == EOF){
            tokenVector.push_back(Token(UNDEFINED, temp, lineStart));
            commentScan = false;
            break;
        }
        else if(isspace(inputFile.peek())){
            if(inputFile.peek() == '\n')
                lineNum++;
            temp += inputFile.get();
        }
        else
            temp += inputFile.get();
    }
}

void checkOther(){
    bool otherScan = true;
    string temp = "";
    temp += current;
    string scheme = "Schemes";
    string fact = "Facts";
    string rule = "Rules";
    string query = "Queries";
    
    if(isdigit(current)){
        string s = "";
        s += current;
        tokenVector.push_back(Token(UNDEFINED, s, lineNum));
        return;
    }
    else if(isalpha(current)){
        while(otherScan){
            if(isspace(inputFile.peek())){
                if(temp.compare(scheme) == 0){
                    tokenVector.push_back(Token(SCHEMES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(fact) == 0){
                    tokenVector.push_back(Token(FACTS, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(rule) == 0){
                    tokenVector.push_back(Token(RULES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(query) == 0){
                    tokenVector.push_back(Token(QUERIES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else{
                    tokenVector.push_back(Token(ID, temp, lineNum));
                    otherScan = false;
                    break;
                }
            }
            else if(inputFile.peek() == EOF){
                if(temp.compare(scheme) == 0){
                    tokenVector.push_back(Token(SCHEMES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(fact) == 0){
                    tokenVector.push_back(Token(FACTS, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(rule) == 0){
                    tokenVector.push_back(Token(RULES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(query) == 0){
                    tokenVector.push_back(Token(QUERIES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else{
                    tokenVector.push_back(Token(ID, temp, lineNum));
                    otherScan = false;
                    break;
                }
                
            }
            else if(inputFile.peek() == ':' || inputFile.peek() == '(' || inputFile.peek() == ',' || inputFile.peek() == ')' || inputFile.peek() == '?' || inputFile.peek() == '.' || inputFile.peek() == '*' || inputFile.peek() == '+' || inputFile.peek() == '#'){
                if(temp.compare(scheme) == 0){
                    tokenVector.push_back(Token(SCHEMES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(fact) == 0){
                    tokenVector.push_back(Token(FACTS, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(rule) == 0){
                    tokenVector.push_back(Token(RULES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else if(temp.compare(query) == 0){
                    tokenVector.push_back(Token(QUERIES, temp, lineNum));
                    otherScan = false;
                    break;
                }
                else{
                    tokenVector.push_back(Token(ID, temp, lineNum));
                    otherScan = false;
                    break;
                }
            }
            else{
                temp += inputFile.get();
            }
        }
    }
    else{
        string s = "";
        s += current;
        tokenVector.push_back(Token(UNDEFINED, s, lineNum));
        return;
    }
}

void printVector(){
    unsigned long unsign = tokenVector.size();
    int vectorSize = (int)unsign;
    for(int i=0; i < vectorSize; ++i){
        (tokenVector.at(i)).printToken();
    }
    cout << "Total Tokens = " << tokenVector.size();
}

vector<Token> getVector(){ return tokenVector; }

};