#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int main() {

  Scheme scheme1( { "A", "B" } );
  Scheme scheme2( { "B", "C" } );

  Tuple tuple1( {"'1'", "'2'"} );
  Tuple tuple2( {"'3'", "'4'"} );

  Relation::joinable(scheme1, scheme2, tuple1, tuple2);

}
