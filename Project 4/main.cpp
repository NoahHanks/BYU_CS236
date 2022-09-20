#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]){
    if (!argv[1])
        cout << "No file specified\n";
    else{
        string fileName = argv[1];
        Scanner myScanner(fileName);
        myScanner.scan();
        vector<Token> tokenVector = myScanner.getVector();
        Parser myParser(tokenVector);
        myParser.parse();
        DatalogProgram data = myParser.getData();
        Interpreter myInterpreter(data);
        myInterpreter.evalAllRules();
        myInterpreter.evalAllQueries();
        cout << endl;
        return 0;
        }    
}