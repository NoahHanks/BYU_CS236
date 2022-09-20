#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <set>
#include "Tuple.h"
#include "Scheme.h"

#pragma once
using namespace std;

class Relation{
private:
    string name;
    Scheme scheme;
    set<Tuple> tupleSet;
public:
    Relation();
    Relation(string n, Scheme s);
    Relation(string n, set<Tuple> s);
    Relation(string n);
    ~Relation();
    string toString();
    void addTuple(Tuple t);
    string getName();
    Scheme getScheme();
    set<Tuple> getSet();
    
    Relation select(string constant, int index, Relation relation);
    Relation select(int index1, int index2, Relation relation);
    Relation project(vector<int> position, Relation relation);
    Relation rename(vector<string> variables, Relation relation);
};