#include "scanner.h"
#include "token.h"
#include <cctype>
#include <cstdio>
#include <fstream>
#include <sstream>

#define EMPTY_CHAR ' '
#define EMPTY_STRING " "
#define CHAR_NEWLINE '\n'
#define STRING_NEWLINE "\n"
#define CHAR_RETURN '\r'
#define CHAR_TAB '\t'
#define CHAR_SINGLE_QUOTE '\''
#define STRING_SINGLE_QUOTE "\'"

// Initializes the variables of the scanner.
Scanner::Scanner(string inputFile){
    fileName = inputFile;
    fileStream.open(fileName);
    currState = init_st;
    initFlag = ONE_INIT;
    lineNum = ONE_INIT; 
    currChar = EMPTY_CHAR;
    nextChar = EMPTY_CHAR;
    factsString = EMPTY_STRING;
}

// Closes the fileStram on the scanner.
Scanner::~Scanner(){
    fileStream.close();
}

// Looks in the file and gets the next char into the currChr variable.
void Scanner::GetCurrChar(){
    currChar = fileStream.get();
}

// Checks for words if only letters and numbers are next to each other in the input file.
string Scanner::FindWords(){
    char stringCurrChar;
    string inputString;
    inputString += currChar;  
    stringCurrChar = fileStream.get();
    while(isalpha(stringCurrChar) || isdigit(stringCurrChar)){
        inputString += stringCurrChar;
        stringCurrChar = fileStream.get();  
    }
    if(!(isalpha(stringCurrChar)) && !(isdigit(stringCurrChar))){
        nextCharVal = true;
        nextChar = stringCurrChar;
    }            
    return inputString;
}

// Checks the current character to see if it is classified as white space.
bool Scanner::WhiteSpaceFound(){
    switch(currChar){
        case ' ': case CHAR_NEWLINE: case CHAR_RETURN: case CHAR_TAB:
            return true;
            break;
        default:
            return false;
            break;
    }
}

// Checks if the file is good, starts the state machine which takes input from text and turns it into a tokenized list.
void Scanner::Tokenize(){
    while(fileStream.good()){
        Token newToken;
        if(nextCharVal == true){
            currChar = nextChar;
            nextCharVal = false;
        }
        else
            GetCurrChar();
        newToken = TokenStateMachine();
        if(!(WhiteSpaceFound()) && !initFlag)
            tokenList.push_back(newToken);
        else if(currChar == EOF)
            tokenList.push_back(newToken);
        initFlag = ZERO_INIT;
    }
}

// The state machine that goes through each character and checks if certain matches are made. 
// A hierarchy exists which prioritizes the eof or whitespace before actual characters.
// When a match is found with a charcter, the branch of that state is taken to add the token to the list.
Token Scanner::TokenStateMachine(){
    Token newToken;
    currState = init_st;
    while(currState != end_st){
        switch(currState){
            // Init states goes through all the first charcters to assess which state to pick next.
            case init_st:
                if(currChar == EOF)
                    currState = eof_st;
                else if(WhiteSpaceFound()){
                    if(currChar == CHAR_NEWLINE|| currChar == CHAR_RETURN){
                        lineNum++;
                        currState = white_space_st;
                    }
                    else if(currChar == CHAR_TAB)
                        currState = white_space_st;
                    currState = white_space_st;
                }
                else if(currChar == EOF)
                    currState = eof_st;
                else if(initFlag == ONE_INIT)
                    currState = end_st;
                else if(currChar == ',' || currChar == '.' || currChar == '?'||currChar == ':' || currChar == '*' 
                    || currChar == '(' || currChar == ')' || currChar == '+')
                    currState = special_st; 
                else if(currChar == '#')
                    currState = comment_st;
                else if(currChar == CHAR_SINGLE_QUOTE)
                    currState = string_st;
                else if(isalpha(currChar))
                    currState = special_string_st;
                else{
                    string tempString;
                    tempString += currChar;
                    newToken.SetSpecialType(STRINGIZED_UNDEFINED, tempString, lineNum);
                    return newToken;
                }
                break;
            // Checks for the colon and colon dash tokens.
            case special_st:
                if(currChar == ':'){
                    nextChar = fileStream.get();
                    if(nextChar == '-'){
                        newToken.SetTypeAndNum(":-", lineNum);
                        return newToken;
                    }
                    else{
                        newToken.SetTypeAndNum(":", lineNum);
                        nextCharVal = true;
                        return newToken;
                    }
                }
                else{
                    string tempString;
                    tempString += currChar;
                    newToken.SetTypeAndNum(tempString, lineNum);
                    return newToken;
                }
                break;
            // Checks for rules based on which character the token falls into.
            case special_string_st:
                factsString = FindWords();
                switch(currChar){
                    case 'S':
                        if(factsString == STRINGIZED_LOWER_SCHEMES){
                            newToken.SetTypeAndNum(factsString, lineNum);
                            return newToken;
                        }
                        else
                            currState = id_st;
                        break;
                    case 'F':
                        if(factsString == STRINGIZED_LOWER_FACTS){
                            newToken.SetTypeAndNum(factsString, lineNum);
                            return newToken;
                        }
                        else
                            currState = id_st;
                        break;
                    case 'R':
                        if(factsString == STRINGIZED_LOWER_RULES){
                            newToken.SetTypeAndNum(factsString, lineNum);
                            return newToken;
                        }
                        else
                            currState = id_st;
                        break;
                    case 'Q':
                        if(factsString == STRINGIZED_LOWER_QUERIES){
                            newToken.SetTypeAndNum(factsString, lineNum);
                            return newToken;
                        }
                        else
                            currState = id_st;
                        break;
                    default:
                        currState = id_st;  
                        break; 
                }
                break;
            // Checks for comment tokens with the bar, slash, and pound characters as well as empty lines in between.
            case comment_st:
                nextChar = fileStream.get();
                currChar = nextChar;
                if(currChar == '|'){
                    int emptyLines = ZERO_INIT;
                    bool ieof_st = false;
                    string tempStringComment;
                    tempStringComment = "#|";
                    GetCurrChar();
                    nextChar = fileStream.peek();
                    while(!(currChar == EOF && nextChar == EOF)){
                        if(nextChar == '#' && currChar == '|'){
                            tempStringComment += "|#";
                            fileStream.get();
                            newToken.SetSpecialType(STRINGIZED_COMMENT, tempStringComment, lineNum);
                            lineNum += emptyLines;
                            return newToken;
                        }
                        else if(nextChar == EOF)
                            ieof_st = true;
                        if(currChar == CHAR_NEWLINE || currChar == CHAR_RETURN){
                            lineNum++;
                            emptyLines++;
                            tempStringComment.append(STRING_NEWLINE);
                        }
                        else{
                            string tempString;
                            tempString += currChar;
                            tempStringComment.append(tempString);
                        }
                        GetCurrChar();
                        nextChar = fileStream.peek();
                    }
                    if(ieof_st){                        
                        newToken.SetSpecialType(STRINGIZED_UNDEFINED, tempStringComment, lineNum);
                        tokenList.push_back(newToken);
                        newToken.SetTypeAndNum(STRINGIZED_EOF, lineNum + emptyLines);
                        currChar = EOF;
                        return newToken;
                    }
                    else{
                        newToken.SetSpecialType(STRINGIZED_COMMENT, tempStringComment, lineNum);
                        lineNum += emptyLines;
                        newToken.TokenToString();
                        return newToken;
                    }
                    GetCurrChar();
                }
                else{
                    string comment = "#";
                    comment += currChar;
                    nextChar = fileStream.peek();
                    while(nextChar != CHAR_NEWLINE){
                        GetCurrChar();
                        comment += currChar;
                        nextChar = fileStream.peek();
                        if(nextChar == CHAR_RETURN || nextChar == CHAR_NEWLINE)
                            break;
                    }
                    newToken.SetSpecialType(STRINGIZED_COMMENT, comment, lineNum);
                    return newToken;
                }
                break;
            // Checks for regular strings between single quotes
            case string_st:
                GetCurrChar();
                if(currChar == CHAR_SINGLE_QUOTE){
                    string tempString = STRING_SINGLE_QUOTE;
                    int emptyLines = ZERO_INIT;
                    while(currChar != EOF){
                        if(currChar == CHAR_NEWLINE || currChar == CHAR_RETURN){
                            emptyLines++;
                        }
                        nextChar = fileStream.peek();
                        if(currChar == CHAR_SINGLE_QUOTE && nextChar == CHAR_SINGLE_QUOTE){
                            GetCurrChar();
                            nextChar = fileStream.peek();
                            tempString += currChar;
                            tempString += STRING_SINGLE_QUOTE;
                        }
                        else if(currChar == CHAR_SINGLE_QUOTE && nextChar != CHAR_SINGLE_QUOTE){
                            tempString += STRING_SINGLE_QUOTE;
                            newToken.SetSpecialType(STRINGIZED_STRING, tempString, lineNum);
                            lineNum += emptyLines;
                            return newToken;
                            break;
                        }
                        else if(nextChar == EOF){
                            newToken.SetSpecialType(STRINGIZED_UNDEFINED, tempString, lineNum);
                            tokenList.push_back(newToken);
                            newToken.SetTypeAndNum(STRINGIZED_EOF, lineNum + emptyLines);
                            currChar = EOF;
                            return newToken;
                            break;
                        }
                        else
                            tempString += currChar;
                        GetCurrChar();
                    }
                }
                else if(currChar == CHAR_SINGLE_QUOTE){
                    newToken.SetSpecialType(STRINGIZED_STRING, "\'\'", lineNum);
                    return newToken;
                }
                else{
                    string tempString = STRING_SINGLE_QUOTE;
                    int emptyLines = ZERO_INIT;
                    while(!(currChar == EOF)){
                        if(currChar == CHAR_RETURN || currChar == CHAR_NEWLINE)
                            emptyLines++;
                        nextChar = fileStream.peek();
                        if(currChar == CHAR_SINGLE_QUOTE && nextChar == CHAR_SINGLE_QUOTE){
                            GetCurrChar();
                            nextChar = fileStream.peek();
                            tempString += currChar;
                            tempString += STRING_SINGLE_QUOTE;
                        }
                        else if(currChar == CHAR_SINGLE_QUOTE && nextChar != CHAR_SINGLE_QUOTE){
                            tempString += STRING_SINGLE_QUOTE;
                            newToken.SetSpecialType(STRINGIZED_STRING, tempString, lineNum);
                            lineNum += emptyLines;
                            return newToken;
                            break;
                        }
                        else if(nextChar == EOF){
                            tempString += currChar;
                            newToken.SetSpecialType(STRINGIZED_UNDEFINED, tempString, lineNum);
                            tokenList.push_back(newToken);
                            newToken.SetTypeAndNum(STRINGIZED_EOF, lineNum + emptyLines);
                            currChar = EOF;
                            return newToken;
                            break;
                        }
                        else
                            tempString += currChar;
                        GetCurrChar();
                    }
                }
                break;
            // The rest of the cases for basic tokens.
            case id_st:
                newToken.SetSpecialType(STRINGIZED_ID, factsString, lineNum);
                return newToken;
                break;
            case eof_st:
                newToken.SetTypeAndNum(STRINGIZED_EOF, lineNum);
                return newToken;
                break;
            case white_space_st: 
                currState = end_st;
                break;
            case end_st:
                return newToken;
                break;
            default:
                newToken.SetSpecialType(STRINGIZED_UNDEFINED, STRINGIZED_UNDEFINED, lineNum);
        }   
    }
    newToken.SetSpecialType(STRINGIZED_UNDEFINED, STRINGIZED_UNDEFINED, lineNum);
    return newToken;
}