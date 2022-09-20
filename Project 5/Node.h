#include <stdio.h>
#include <set>

using namespace std;
#pragma once

class Node {
public:
    Node();
    Node(int id);
    ~Node();
    int id;
    set<int> dependSet;
    set<int> reverseSet;
    bool visited;
    int postOrderNum;
};