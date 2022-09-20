//
//  Predicate.h
//  Project2
//
//  Created by Cam on 2/6/19.
//  Copyright © 2019 Cam Brown. All rights reserved.
//

#ifndef Predicate_h
#define Predicate_h

#include <stdio.h>
#include <vector>
#include <string>
#include "Parameter.h"

using namespace std;

class Predicate {
public:
    Predicate();
    ~Predicate();
    Predicate(string ident);
    Predicate(string ident, vector<Parameter> pList);
    string getID();
    vector<Parameter> getParameters();
    void addParameter(Parameter param);
    string toString();
private:
    string id;
    vector<Parameter> paramList;
    
    
};
#endif /* Predicate_h */
