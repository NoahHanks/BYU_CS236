#include <stdio.h>
#include "Predicate.h"

using namespace std;

class Rule {
private:
    vector<Predicate> predicateList;
    Predicate headPredicate;
public:
    Rule();
    ~Rule();
    Rule(Predicate p);
    Rule(Predicate pred, vector<Predicate> predList);
    void addPredicate(Predicate pred);
    vector<Predicate> getPredicateList();
    Predicate getHeadPredicate();
    string toString();

};