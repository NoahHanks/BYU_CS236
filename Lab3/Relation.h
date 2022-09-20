//
// Created by walte on 2/10/2022.
//

#ifndef CS235WINTER2022_RELATION_H
#define CS235WINTER2022_RELATION_H
#include "Tuple.h"
#include <set>

class Relation
{
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string &name, const Scheme &scheme) : name(name), scheme(scheme)
    {}

    Relation()
    {}

    const string &getName() const
    {
        return name;
    }

    void setName(const string &name)
    {
        Relation::name = name;
    }

    const Scheme &getScheme() const
    {
        return scheme;
    }

    void setScheme(const Scheme &scheme)
    {
        Relation::scheme = scheme;
    }

      Relation select(int index, const string& value) const {
    Relation result(name, scheme);
    for (Tuple t : tuples)
      if (t.at(index) == value)
	result.addTuple(t);
    return result;
  }

    bool addTuple(Tuple t) // if the tuple was not already in the set this returns true, otherwise false
    {
        return tuples.insert(t).second;
    }

    string toString()
    {
        stringstream out;
        for (Tuple t : tuples)
        {
            if (t.size() != 0)
                out << "  " << t.toString(scheme) << endl;
        }
        return out.str();
    }
};


#endif //CS235WINTER2022_RELATION_H
