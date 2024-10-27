#include "Polynomial.h"

// Default constructor
Polynomial::Polynomial() : coeffs(1, 0.0)
{
}

// Constructor with coefficients
Polynomial::Polynomial(const vector<double> &coefficients) : coeffs(coefficients)
{
}

// Copy constructor
Polynomial::Polynomial(const Polynomial &other) : coeffs(other.coeffs)
{
}

// Destructor
Polynomial::~Polynomial()
{
}

// Assignment operator
Polynomial &Polynomial::operator=(const Polynomial &other)
{
    if (this != &other)
    {
        coeffs = other.coeffs;
    }
    return *this;
}

// Addition operator
Polynomial Polynomial::operator+(const Polynomial &other) const
{
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < result.size(); ++i)
    {
        if (i < coeffs.size())
            result[i] += coeffs[i];
        if (i < other.coeffs.size())
            result[i] += other.coeffs[i];
    }
    return Polynomial(result);
}

// Subtraction operator
Polynomial Polynomial::operator-(const Polynomial &other) const
{
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < result.size(); ++i)
    {
        if (i < coeffs.size())
            result[i] += coeffs[i];
        if (i < other.coeffs.size())
            result[i] -= other.coeffs[i];
    }
    return Polynomial(result);
}

// Multiplication operator
Polynomial Polynomial::operator*(const Polynomial &other) const
{
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i)
    {
        for (size_t j = 0; j < other.coeffs.size(); ++j)
        {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial &other) const
{
    return coeffs == other.coeffs;
}

ostream &operator<<(ostream &out, const Polynomial &poly)
{
    bool isFirstTerm = true;

    for (int i = poly.coeffs.size() - 1; i >= 0; --i)
    {
        double coef = poly.coeffs[i];

        if (coef != 0)
        {
            if (!isFirstTerm && coef > 0)
            {
                out << " + "; // Space around the plus sign
            }
            else if (coef < 0)
            {
                out << " - "; // Space around the minus sign
                coef = -coef; // Make coefficient positive for display
            }

            if (i == 0)
            {
                out << coef; // Constant term, no "x"
            }
            else if (i == 1)
            {
                out << coef << "x"; // Linear term, just "x"
            }
            else
            {
                out << coef << "x^" << i; // Higher degree terms
            }

            isFirstTerm = false;
        }
    }

    if (isFirstTerm)
    {
        out << "0"; // If no terms are printed, the polynomial is zero
    }

    return out;
}

// Return the degree of the polynomial
int Polynomial::degree() const
{
    return coeffs.size() - 1;
}

// Evaluate the polynomial at x
double Polynomial::evaluate(double x) const
{
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i)
    {
        result = result * x + coeffs[i];
    }
    return result;
}

// Composition of two polynomials
Polynomial Polynomial::compose(const Polynomial &q) const
{
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i)
    {
        result = result * q + Polynomial(vector<double>{coeffs[i]});
    }
    return result;
}

// Derivative of the polynomial
Polynomial Polynomial::derivative() const
{
    if (coeffs.size() == 1)
    {
        return Polynomial(vector<double>{0});
    }

    vector<double> deriv(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i)
    {
        deriv[i - 1] = coeffs[i] * i;
    }
    return Polynomial(deriv);
}

// Indefinite integral of the polynomial
Polynomial Polynomial::integral() const
{
    vector<double> integral(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i)
    {
        integral[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(integral);
}

// Definite integral of the polynomial between x1 and x2
double Polynomial::integral(double x1, double x2) const
{
    Polynomial intPoly = this->integral();
    return intPoly.evaluate(x2) - intPoly.evaluate(x1);
}

// Root finding using Newton's method
double Polynomial::getRoot(double guess, double tolerance, int maxIter)
{
    Polynomial derivPoly = this->derivative();
    double x = guess;

    for (int i = 0; i < maxIter; ++i)
    {
        double fx = this->evaluate(x);
        double fprime_x = derivPoly.evaluate(x);

        if (abs(fx) < tolerance)
        {
            return x;
        }
        if (fprime_x == 0)
        {
            break; // Avoid division by zero
        }
        x = x - fx / fprime_x;
    }
    return x; // Return best guess
}

// Set the coefficients of the polynomial
void Polynomial::setCoefficients(const vector<double> &coefficients)
{
    coeffs = coefficients;
}

// Get the coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const
{
    if (degree >= 0 && degree < coeffs.size())
    {
        return coeffs[degree];
    }
    return 0.0;
}