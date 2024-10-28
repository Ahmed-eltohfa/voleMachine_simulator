#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Vole_machine.h"
// #include "Vole_machine.cpp"
using namespace std;

int main()
{
    string regSrc1 = "00011";
    string regSrc2 = "00011";

    bitset<8> S(regSrc1);
    bitset<8> T(regSrc2);
    int result = S.to_ullong() + T.to_ullong();
    cout << result << "\n";
    return 0;
}