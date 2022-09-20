//
//  Parameter.h
//  Project2
//
//  Created by Cam on 2/6/19.
//  Copyright © 2019 Cam Brown. All rights reserved.
//

#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include <string>

using namespace std;

class Parameter {
public:
    Parameter();
    Parameter(string val);
    Parameter(string val, string tokenType);
    ~Parameter();
    string getValue();
    string toString();
    string getType();
    void setValue(string val);
    bool getIsConstant();
    void setIsConstant(bool tf);
private:
    bool isConstant;
    string value;
    string type;
    
};

#endif /* Parameter_h */
