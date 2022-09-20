#include "Interpreter.h"

Interpreter :: Interpreter(){}

Interpreter :: Interpreter(DatalogProgram data){
    datalog = data;
    schemeVector = data.getSchemes();
    factVector = data.getFacts();
    ruleVector =  data.getRules();
    queryVector = data.getQueries();

    for(int i = 0; i < (int)schemeVector.size(); ++i){
        string schemeName = schemeVector.at(i).getID();
        vector<Parameter> schemeParams = schemeVector.at(i).getParameters();
        Scheme scheme;
        for(int j = 0; j < (int)schemeParams.size(); ++j){
            string value = schemeParams.at(j).getValue();
            scheme.push_back(value);
        }
        Relation newRelation(schemeName, scheme);
        database.insert(pair<string, Relation>(schemeName, newRelation));
    }

    for(int i = 0; i < (int)factVector.size(); ++i){
        string factName = factVector.at(i).getID();
        vector<Parameter> factParams = factVector.at(i).getParameters();
        Tuple tuple;
        for(int j = 0; j < (int)factParams.size(); ++j){
            string value = factParams.at(j).getValue();
            tuple.push_back(value);
        }
        (database.at(factName)).addTuple(tuple);
    }
    buildDependency();
    buildReverse();
    myGraph.dfsForest();
    myGraph.sccDFSForest();
}

Interpreter :: ~Interpreter(){}

Relation Interpreter :: evalOnePredicate(Predicate myPredicate){
    string predicateName = myPredicate.getID();
    Relation myRelation = database.at(predicateName);
    vector<Parameter> predParams = myPredicate.getParameters();
    vector<int> positions;
    vector<string> variableNames;
    map<string, int> variables;
    for(int i = 0; i < (int)predParams.size(); i++){
        if((predParams.at(i).getIsConstant()) == true)
            myRelation = myRelation.select(predParams.at(i).getValue(), i, myRelation);
        else{
            map<string, int> :: iterator duplicate = variables.find(predParams.at(i).getValue());
            if(duplicate == variables.end()){
                positions.push_back(i);
                variableNames.push_back(predParams.at(i).getValue());
                variables.insert(pair<string, int>(predParams.at(i).getValue(), i));
            }
            else
                myRelation = myRelation.select(duplicate->second, i, myRelation);
        }

    }
    myRelation = myRelation.project(positions, myRelation);
    myRelation = myRelation.rename(variableNames, myRelation);
    return myRelation;
}

void Interpreter :: evalOneRule(Rule myRule){
    vector<Predicate> rulePreds = myRule.getPredicateList();
    vector<Relation> relVec;
    for(Predicate x : rulePreds){
        Relation newRelation = evalOnePredicate(x);
        relVec.push_back(newRelation);
    }
    int relVecSize = (int)relVec.size();
    for(int i = 0; i < relVecSize; i++){
        if(i == relVecSize - 1)
            break;
        else 
            relVec.at(i+1) = relVec.at(i).join(relVec.at(i), relVec.at(i+1));
    }
    Relation newRelation = relVec.at(relVecSize-1);
    Predicate headPredicate = myRule.getHeadPredicate();
    vector<Parameter> headPredParams = headPredicate.getParameters();
    int headPredSize = (int)headPredParams.size();
    int relParamSize = (int)newRelation.getScheme().size();
    vector<int> positions;
    vector<string> renameVals;
    for(int i = 0; i < headPredSize; i++)
        for(int j = 0; j < relParamSize; j++)
            if(headPredParams.at(i).getValue() == newRelation.getScheme().at(j))
                positions.push_back(j);
    Relation tempRel = database.at(headPredicate.getID());
    for(int i = 0; i < (int)tempRel.getScheme().size(); i++)
        renameVals.push_back(tempRel.getScheme().at(i));
    newRelation = newRelation.project(positions, newRelation);
    newRelation = newRelation.rename(renameVals, newRelation);
    database.at(headPredicate.getID()).unite(newRelation);
}

void Interpreter :: evalAllRules(){
    cout << "Rule Evaluation" << endl;
    for(auto x : myGraph.scc){
        int numPasses = 0;
        cout << "SCC: ";
        int temp;
        for(set<int> :: iterator s = x.second.begin(); s != x.second.end(); ++s){
            if(s != x.second.begin())
                cout << ",";
            cout << "R" << *s;
            temp = *s;
        }
        cout << endl;

        if(x.second.size() == 1 && (x.second.size() == 1 && myGraph.nodes.at(temp).dependSet.find(temp) == myGraph.nodes.at(temp).dependSet.end())){
            cout << ruleVector.at(temp).toString();
            evalOneRule(ruleVector.at(temp));
            cout << endl;
            numPasses++;
        }
        else {
            int sizeBefore = 0;
            int sizeAfter = 0;
            numPasses = 0;
            do{
                sizeBefore = database.getSize();
                for(int i : x.second){
                    cout << ruleVector.at(i).toString();
                    evalOneRule(ruleVector.at(i));
                    cout << endl;
                }
                sizeAfter = database.getSize();
                numPasses++;
            } while(sizeBefore != sizeAfter);
        }
        cout << numPasses << " passes: ";
        for(set<int> :: iterator s = x.second.begin(); s != x.second.end(); ++s){
            if(s != x.second.begin())
                cout << ",";
            cout << "R" << *s;
        }
        cout << endl;
    }
    cout << endl;
}

void Interpreter :: evalAllQueries(){
    cout << "Query Evaluation" << endl;
    for(int i = 0; i < (int)queryVector.size(); ++i){
        Relation newRelation = evalOnePredicate(queryVector.at(i));
        cout << queryVector.at(i).toString() << "? ";
        if(newRelation.getSet().empty())
            cout << "No";
        else {
            cout << "Yes(" << (int)newRelation.getSet().size() << ")";
            cout << newRelation.toString();
        }
        if(i != (int)queryVector.size()-1)
            cout << endl;
    }
    cout << endl;
}

void Interpreter :: buildDependency(){
    for(int i = 0; i < (int)ruleVector.size(); i++){
        Rule myRule = ruleVector.at(i);
        Node myNode(i);
        for(int j = 0; j < (int)myRule.getPredicateList().size(); j++){
            Predicate myPred = myRule.getPredicateList().at(j);
            for(int k = 0; k < (int)ruleVector.size(); k++)
                if(myPred.getID() == ruleVector.at(k).getHeadPredicate().getID())
                    myNode.dependSet.insert(k);
        }
        myGraph.nodes.insert(pair<int, Node>(i, myNode));
    }
    cout << "Dependency Graph" << endl;
    for(map<int,Node>::iterator it=myGraph.nodes.begin(); it!=myGraph.nodes.end(); ++it){
        cout << "R" << it->first << ":";
        set<int> mySet = it->second.dependSet;
        for(set<int> :: iterator s = mySet.begin(); s != mySet.end(); ++s){
            if(s != mySet.begin())
            	cout << ",";
            cout << "R" << *s;
        }
        cout << endl;
    }
    cout << endl;
}

void Interpreter :: buildReverse(){
    for(map<int,Node> :: iterator i=myGraph.nodes.begin(); i!=myGraph.nodes.end(); ++i){
        set<int> mySet = i->second.dependSet;
        for(set<int> :: iterator j = mySet.begin(); j != mySet.end(); ++j)
            myGraph.nodes.at(*j).reverseSet.insert(i->first);
    }
}