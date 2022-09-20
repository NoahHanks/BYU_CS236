#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#pragma once

using namespace std;

class Tuple : public vector<string>{
private:
public:
    Tuple();
    ~Tuple();
    string toString();
};