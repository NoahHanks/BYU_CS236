//
// Created by walte on 1/12/2022.
//

#ifndef CS235WINTER2022_TOKEN_H
#define CS235WINTER2022_TOKEN_H

#include <string>
#include <sstream>
enum  class TokenType
{
    COMMA, COLON, COMMENT, UNDEFINED
};

std::string tokenToString(TokenType t)
{
    switch (t)
    {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        default:
            return "BAD TYPE";
    }
}

class Token
{
private:
    std::string value;
    TokenType type;
    unsigned int lineNum;
public:
    Token(const std::string &value, TokenType type, unsigned int lineNum) : value(value), type(type), lineNum(lineNum)
    {}

    const std::string &getValue() const
    {
        return value;
    }

    void setValue(const std::string &value)
    {
        Token::value = value;
    }

    TokenType getType() const
    {
        return type;
    }

    void setType(TokenType type)
    {
        Token::type = type;
    }

    unsigned int getLineNum() const
    {
        return lineNum;
    }

    void setLineNum(unsigned int lineNum)
    {
        Token::lineNum = lineNum;
    }

    std::string toString()
    {
        std::stringstream outSS;
        outSS << "(" << tokenToString(type) << ",\"" << value << "\"," << lineNum << ")";
        return outSS.str();
    }
};




#endif //CS235WINTER2022_TOKEN_H
