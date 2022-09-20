#include "scanner.h"
#define TOTAL_TOKENS "Total Tokens = "
#define ERROR_MESSAGE "No file specified\n Total Tokens = 0\n"

using namespace std;

int main (int argc, char* argv[]){
    if (!argv[1])
        cout << "No file specified\n Total Tokens = 0\n";
    else{
        string fileName = argv[ONE_INIT];
        Scanner mainScanner(fileName);  
        mainScanner.Tokenize();
        for(unsigned int i = ZERO_INIT; i < mainScanner.tokenList.size(); i++)
            cout << mainScanner.tokenList.at(i).TokenToString() << endl;
        cout << TOTAL_TOKENS << mainScanner.tokenList.size() << endl;
    }
    return ZERO_INIT;
}