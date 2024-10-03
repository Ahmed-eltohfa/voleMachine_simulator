#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void formateTxt()
{
    string sentence;
    cout << "Enter your sentence to formate: \n";
    getline(cin, sentence);
    string out = "";
    for (int i = 0; i < sentence.size(); i++)
    {
        if (i == 0 && islower(sentence[i]))
        {
            out += toupper(sentence[i]);
            continue;
        }
        static int n = 0;
        if (sentence[i] == ' ')
        {
            n++;
            if (n > 1)
            {
                continue;
            }
        }
        else
        {
            n = 0;
        }
        if (i > 0 && isupper(sentence[i]))
        {
            out += tolower(sentence[i]);
            continue;
        }
        out += sentence[i];
    }
    cout << out;
}

void printPrime()
{
    int n;
    cout << "Enter the limit to print primes to: \n";
    cin >> n;
    int numList[n] = {};
    for (int i = 2; i < n; i++)
    {
        numList[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        if (numList[i] == 0)
            continue;

        for (int j = i + 1; j < n; j++)
        {
            if (numList[j] % numList[i] == 0)
            {
                numList[j] = 0;
            }
        }
    }
    for (int num : numList)
    {
        if (num != 0)
        {
            cout << num << " ";
        }
    }
}

int main()
{
    return 0;
}