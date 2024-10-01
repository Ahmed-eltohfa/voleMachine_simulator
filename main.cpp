#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void formateTxt()
{
    string sentence;
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

int main()
{
    return 0;
}