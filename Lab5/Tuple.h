#include <stdio.h>
#include <vector>
#include <string>
#pragma once

using namespace std;

class Tuple : public vector<string> {
private:
public:
    Tuple();
    ~Tuple();
};