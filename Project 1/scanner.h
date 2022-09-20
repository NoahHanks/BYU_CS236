#pragma once
#include "token.h"

using namespace std;

// States for the state machine which creates a different token based on the input of the currChar and nextChar.
enum state{init_st, special_st, special_string_st, end_st, eof_st, id_st, comment_st, string_st, white_space_st};

class Scanner{
    public:
        Scanner(string inputFile);
        ~Scanner();
        void GetCurrChar();
        void Tokenize();
        vector<Token> tokenList;
    private:
        Token TokenStateMachine();
        string FindWords();
        bool WhiteSpaceFound();
        bool nextCharVal;
        char currChar;
        char nextChar;
        ifstream fileStream;
        int lineNum;
        int initFlag;
        state currState;
        string fileName;
        string factsString;
};