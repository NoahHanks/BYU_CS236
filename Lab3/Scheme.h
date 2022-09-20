//
// Created by walte on 2/10/2022.
//

#ifndef CS235WINTER2022_SCHEME_H
#define CS235WINTER2022_SCHEME_H

#include <vector>
#include <string>

using namespace std;

class Scheme
{
private:
    vector<string> attributes;
public:
    string at(unsigned int index)
    {
        return attributes.at(index);
    }

    unsigned int size()
    {
        return attributes.size();
    }

    void push_back(string newAttribute)
    {
        attributes.push_back(newAttribute);
    }

    bool operator<(const Scheme& s)
    {
        return this->attributes < s.attributes;
    }

    Scheme(const vector<string> &attributes) : attributes(attributes)
    {}

    Scheme()
    {}
};


#endif //CS235WINTER2022_SCHEME_H
