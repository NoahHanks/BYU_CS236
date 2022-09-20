#include <string>
#include <iostream>
#include <fstream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]){
    if (!argv[1])
        cout << "No file specified\n";
    else{
        string fileName = argv[1];
        Parser myParser(fileName);
        myParser.parse();
        cout << endl;
    }
    return 0;
}