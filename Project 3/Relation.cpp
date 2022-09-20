#include "Relation.h"

Relation :: Relation(){}

Relation :: Relation(string n, Scheme s){
    name = n;
    scheme = s;
}

Relation :: Relation(string n, set<Tuple> s){
    name = n;
    tupleSet = s;
}

Relation :: Relation(string n){ name = n; }

Relation :: ~Relation(){}

string Relation :: toString(){
    stringstream ss;
    if(tupleSet.empty())
        ss << "No";
    else{
        ss << "Yes(" << tupleSet.size() << ")";
        for(Tuple t : tupleSet){
            if(t.empty()){}
            else{
                ss << endl << "  ";
                for(int i = 0; i < (int)t.size(); ++i){
                    ss << scheme.at(i) << "=" << t.at(i);
                    if(i == (int)t.size()-1){}
                    else
                        ss << ", ";
                }
            }
            
        }
    }
    return ss.str();
}

void Relation :: addTuple(Tuple t){ tupleSet.insert(t); }
string Relation :: getName(){ return name; }
Scheme Relation :: getScheme(){ return scheme; }
set<Tuple> Relation :: getSet(){ return tupleSet; }

Relation Relation :: select(string constant, int i, Relation relation){
    Relation newRelation(relation.getName(), relation.getScheme());
    for(Tuple t : relation.getSet())
        if(t.at(i) == constant)
            newRelation.addTuple(t);
    return newRelation;
}

Relation Relation :: select(int i1, int i2, Relation relation){
    Relation newRelation(relation.getName(), relation.getScheme());
    for(Tuple t : relation.getSet())
        if(t.at(i1) == t.at(i2))
            newRelation.addTuple(t);
    return newRelation;
}

Relation Relation :: project(vector<int> position, Relation relation){
    Relation newRelation(relation.getName());
    for(Tuple t : relation.getSet()){
        Tuple temp;
        for(int j = 0; j < (int)position.size(); j++){
            temp.push_back(t.at(position.at(j)));
            scheme.push_back(relation.scheme.at(j));
        }
        newRelation.addTuple(temp);
    }
    return newRelation;
}

Relation Relation :: rename(vector<string> variables, Relation relation){
    Relation newRelation(relation.getName(), relation.getSet());
    for(int i = 0; i < (int)variables.size(); i++)
        newRelation.scheme.push_back(variables.at(i));
    return newRelation;
}