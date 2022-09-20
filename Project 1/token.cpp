#include "token.h"

// Initztializes the token and its variables.
Token::Token(){
    tokenType = ERROR;
    tokenValue = STRINGIZED_UNDEFINED;
    tokenLineNum = ZERO_INIT;
}

// Gets the tokenType from the token.
TokenType Token::GetTokenType(){
    return tokenType;
}

// Takes input from the tokenType then converts it to a string using the defined constants.
string Token::TokenToString(){
    string stringizedType = STRINGIZED_ERROR;
    switch(tokenType){
        case COMMA:
            stringizedType = STRINGIZED_COMMA;
            break;
        case PERIOD:
            stringizedType = STRINGIZED_PERIOD;
            break;
        case Q_MARK:
            stringizedType = STRINGIZED_Q_MARK;
            break;
        case LEFT_PAREN:
            stringizedType = STRINGIZED_LEFT_PAREN;
            break;
        case RIGHT_PAREN:
            stringizedType = STRINGIZED_RIGHT_PAREN;
            break;
        case COLON:
            stringizedType = STRINGIZED_COLON;
            break;
        case COLON_DASH:
            stringizedType = STRINGIZED_COLON_DASH;
            break;
        case MULTIPLY:
            stringizedType = STRINGIZED_MULTIPLY;
            break;
        case ADD: 
            stringizedType = STRINGIZED_ADD;
            break;
        case SCHEMES:
            stringizedType = STRINGIZED_SCHEMES;
            break;
        case FACTS:
            stringizedType = STRINGIZED_FACTS;
            break;
        case RULES:
            stringizedType = STRINGIZED_RULES;
            break;
        case QUERIES:
            stringizedType = STRINGIZED_QUERIES;
            break;
        case ID:
            stringizedType = STRINGIZED_ID;
            break;
        case STRING:
            stringizedType = STRINGIZED_STRING;
            break;
        case COMMENT:
            stringizedType = STRINGIZED_COMMENT;
            break;
        case UNDEFINED:
            stringizedType = STRINGIZED_UNDEFINED;
            break;
        case EOFF:
            stringizedType = STRINGIZED_EOF;
            break;
        case ERROR:
            stringizedType = STRINGIZED_ERROR;
            break;
        default:
            stringizedType = STRINGIZED_UNDEFINED;
            break;
    }
    return ("(" + stringizedType + ",\"" + tokenValue + "\"," + to_string(tokenLineNum) + ")");
}

// Takes input from the string and line number then sets the correct tokenType based on the string and sets it in the token.
void Token::SetTypeAndNum(string inputString, int lineNum){
    tokenValue = inputString;
    tokenLineNum = lineNum;
    if(inputString == ",")
        tokenType = COMMA;
    else if(inputString == ".")
        tokenType = PERIOD;
    else if(inputString == "?")
        tokenType = Q_MARK;
    else if(inputString == "(")
        tokenType = LEFT_PAREN;
    else if(inputString == ")")
        tokenType = RIGHT_PAREN;
    else if(inputString == ":-")
        tokenType = COLON_DASH;
    else if(inputString == ":")
        tokenType = COLON;
    else if(inputString == "*")
        tokenType = MULTIPLY;
    else if(inputString == "+")
        tokenType = ADD;
    else if(inputString == STRINGIZED_LOWER_SCHEMES)
        tokenType = SCHEMES;
    else if(inputString == STRINGIZED_LOWER_FACTS)
        tokenType = FACTS;
    else if(inputString == STRINGIZED_LOWER_QUERIES)
        tokenType = QUERIES;
    else if(inputString == STRINGIZED_LOWER_RULES)
        tokenType = RULES;
    else if(inputString == STRINGIZED_EOF){
        tokenType = EOFF;
        tokenValue = "";
    }
    else
        tokenType = UNDEFINED;
}

// For the special tokens of rules, input is taken from the stringized input type and sets the token accordingly.
void Token::SetSpecialType(string inputType, string inputToken, int lineNum){
    if(inputType == STRINGIZED_ID){
        tokenType = ID;
        tokenValue = inputToken;
        tokenLineNum = lineNum;
    }
    else if(inputType == STRINGIZED_STRING){
        tokenType = STRING;
        tokenValue = inputToken;
        tokenLineNum = lineNum;
    }
    else if(inputType == STRINGIZED_COMMENT){
        tokenType = COMMENT;
        tokenValue = inputToken;
        tokenLineNum = lineNum;
    }
    else if(inputType == STRINGIZED_UNDEFINED){
        tokenType = UNDEFINED;
        tokenValue = inputToken;
        tokenLineNum = lineNum;
    }
}