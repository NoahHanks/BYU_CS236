#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include "Tuple.h"
#include "Scheme.h"


using namespace std;

class Relation {
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
    bool addTuple(Tuple t);
    
    string getName();
    Scheme getScheme();
    set<Tuple> getSet();
    void setScheme(Scheme s);
    
    Relation select(string constant, int index, Relation relation);
    Relation select(int index1, int index2, Relation relation);
    Relation project(vector<int> positions, Relation relation);
    Relation rename(vector<string> variables, Relation relation);
    
    Relation join(Relation relation1, Relation relation2);
    void unite(Relation relation1);
};