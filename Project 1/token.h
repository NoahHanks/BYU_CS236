#pragma once
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define ZERO_INIT 0
#define ONE_INIT 1

#define STRINGIZED_COMMA "COMMA"
#define STRINGIZED_PERIOD "PERIOD"
#define STRINGIZED_Q_MARK "Q_MARK"
#define STRINGIZED_LEFT_PAREN "LEFT_PAREN"
#define STRINGIZED_RIGHT_PAREN "RIGHT_PAREN"
#define STRINGIZED_COLON "COLON"
#define STRINGIZED_COLON_DASH "COLON_DASH"
#define STRINGIZED_MULTIPLY "MULTIPLY"
#define STRINGIZED_ADD "ADD"
#define STRINGIZED_SCHEMES "SCHEMES"
#define STRINGIZED_FACTS "FACTS"
#define STRINGIZED_RULES "RULES"
#define STRINGIZED_QUERIES "QUERIES"
#define STRINGIZED_ID "ID"
#define STRINGIZED_STRING "STRING"
#define STRINGIZED_COMMENT "COMMENT"
#define STRINGIZED_UNDEFINED "UNDEFINED"
#define STRINGIZED_EOF "EOF"
#define STRINGIZED_ERROR "ERROR"

#define STRINGIZED_LOWER_SCHEMES "Schemes"
#define STRINGIZED_LOWER_FACTS "Facts"
#define STRINGIZED_LOWER_RULES "Rules"
#define STRINGIZED_LOWER_QUERIES "Queries"
#define STRINGIZED_LOWER_EOF "Eof"

using namespace std;

enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, 
    COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, 
    ID, STRING, COMMENT, UNDEFINED, EOFF, ERROR
};

class Token{
     public:
        Token();
        TokenType GetTokenType();
        string TokenToString();
        void SetTypeAndNum(string inputString, int tokenLineNum);
        void SetSpecialType(string inputType, string inputToken, int tokenLineNum);
    private:
        TokenType tokenType;
        string tokenValue;
        int tokenLineNum;
};