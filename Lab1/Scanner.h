//
// Created by walte on 1/12/2022.
//

#ifndef CS235WINTER2022_SCANNER_H
#define CS235WINTER2022_SCANNER_H

#include "Token.h"
class Scanner
{
private:
    std::string input;
    unsigned int lineNum = 0;

public:
    Scanner(const std::string &input) : input(input)
    {}

    Token scanToken()
    {
        std::string value = "";
        TokenType type = TokenType::UNDEFINED;
        unsigned int size = 0;
        while (isspace(input.at(0)))
        {
            if (input.at(0) == '\n')
                lineNum++;
            input = input.substr(1, input.size() - 1);
        }

        switch (input.at(0))
        {
            case ',':
                size = 1;
                type = TokenType::COMMA;
                break;
        }

        value = input.substr(0, size);
        input = input.substr(size, input.size()-1);
        return Token(value, type, lineNum);
    }
};


#endif //CS235WINTER2022_SCANNER_H
