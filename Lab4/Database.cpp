//
//  Database.cpp
//  Project3
//
//  Created by Cam on 3/5/19.
//  Copyright © 2019 Cam. All rights reserved.
//

#include "Database.h"

Database :: Database() {
    
}


Database :: ~Database() {
    
}

int Database :: getSize() {
    int size = 0;
    for(map<string, Relation>::iterator it = this->begin(); it != this->end(); ++it) {
        for(Tuple x : it->second.getSet()) {
            size++;
        }
    }
    
    return size;
}



