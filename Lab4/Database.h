//
//  Database.h
//  Project3
//
//  Created by Cam on 3/5/19.
//  Copyright © 2019 Cam. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include <stdio.h>
#include <map>
#include <string>
#include "Relation.h"

using namespace std;

class Database : public map<string, Relation> {
public:
    Database();
    ~Database();
    int getSize();
private:
    
};

#endif /* Database_h */
