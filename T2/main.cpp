#include <iostream>
#include "Polynomial.h"
#include "Polynomial.cpp"

using namespace std;

void displayMenu()
{
    cout << "\n--- Polynomial Menu ---\n";
    cout << "1. Add (p1 + p2)\n";
    cout << "2. Subtract (p1 - p2)\n";
    cout << "3. Multiply (p1 * p2)\n";
    cout << "4. Evaluate p1 and p2 at a specific value of x\n";
    cout << "5. Derivative of p1 and p2\n";
    cout << "6. Change polynomials\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void inputPolynomial(Polynomial &p, const string &name)
{
    cout << "Enter the degree of polynomial " << name << ": ";
    int degree;
    cin >> degree;

    vector<double> coeffs(degree + 1);
    cout << "Enter the coefficients from lowest degree to highest (a0, a1, ..., an):\n";
    for (int i = 0; i <= degree; ++i)
    {
        cout << "Coefficient for x^" << i << ": ";
        cin >> coeffs[i];
    }
    p.setCoefficients(coeffs);
}

int main()
{
    Polynomial p1, p2;
    int choice;
    double x;

    cout << "Input for Polynomial 1:\n";
    inputPolynomial(p1, "p1");

    cout << "Input for Polynomial 2:\n";
    inputPolynomial(p2, "p2");

    bool running = true;

    while (running)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Polynomial sum = p1 + p2;
            cout << "p1 + p2: " << sum << "\n";
            break;
        }
        case 2:
        {
            Polynomial difference = p1 - p2;
            cout << "p1 - p2: " << difference << "\n";
            break;
        }
        case 3:
        {
            Polynomial product = p1 * p2;
            cout << "p1 * p2: " << product << "\n";
            break;
        }
        case 4:
        {
            cout << "Enter the value of x to evaluate p1 and p2: ";
            cin >> x;
            cout << "p1(" << x << ") = " << p1.evaluate(x) << "\n";
            cout << "p2(" << x << ") = " << p2.evaluate(x) << "\n";
            break;
        }
        case 5:
        {
            Polynomial p1_derivative = p1.derivative();
            Polynomial p2_derivative = p2.derivative();
            cout << "Derivative of p1: " << p1_derivative << "\n";
            cout << "Derivative of p2: " << p2_derivative << "\n";
            break;
        }
        case 6:
        {
            cout << "Change Polynomial 1:\n";
            inputPolynomial(p1, "p1");
            cout << "Change Polynomial 2:\n";
            inputPolynomial(p2, "p2");
            break;
        }
        case 7:
        {
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }

        if (running)
        {
            cout << "\nWould you like to:\n";
            cout << "1. Continue with the same polynomials\n";
            cout << "2. Change polynomials\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            int contChoice;
            cin >> contChoice;

            if (contChoice == 2)
            {
                cout << "Change Polynomial 1:\n";
                inputPolynomial(p1, "p1");
                cout << "Change Polynomial 2:\n";
                inputPolynomial(p2, "p2");
            }
            else if (contChoice == 3)
            {
                running = false;
            }
        }
    }

    cout << "Program exited.\n";

    return 0;
}