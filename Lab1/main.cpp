#include <iostream>
#include "Scanner.h"

int main()
{
    Scanner scanner(",,,");

    std::cout << scanner.scanToken().toString() << scanner.scanToken().toString() << scanner.scanToken().toString();
    return 0;
}
