#include <iostream>
#include "Polynomial.h"
#include "Polynomial.cpp"

using namespace std;

int main()
{
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4});    // Represents -1 + 4x
    Polynomial sum = p1 + p2;
    Polynomial difference = p1 - p2;
    Polynomial product = p1 * p2;
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p1 + p2: " << sum << endl;
    cout << "p1 - p2: " << difference << endl;
    cout << "p1 * p2: " << product << endl;
    double x = 2.5;
    cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
    cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl;

    return 0;
}