#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;
struct dominoT
{
    int leftDots;
    int rightDots;
    int index;
    bool taken;

    dominoT(int l, int r) : leftDots(l), rightDots(r), index(0), taken(false) {};
};

ostream &operator<<(ostream &os, dominoT d)
{
    string out = " left: " + to_string(d.leftDots) + "\n right: " + to_string(d.rightDots) + "\n index: " + to_string(d.index) + "\n taken: " + to_string(d.taken) + "\n";
    os << out;
    return os;
}

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

bool FormsDominoChain(vector<dominoT> &dominos, int r, int l, dominoT base)
{
    static vector<dominoT> out;
    static int ri = 0, li = 0;
    if (dominos.empty())
    {
        out.push_back(base);
        for (int i = li; i < ri + 1; i++)
        {
            for (int j = 0; j < out.size(); j++)
            {
                if (out[j].index == i)
                {
                    cout << out[j].leftDots << "|" << out[j].rightDots << (i == ri ? "" : "-");
                }
            }
        }
        cout << "\n";

        return true;
    }

    for (int i = 0; i < dominos.size(); i++)
    {
        dominoT current(-1, -1);

        if (!dominos[i].taken)
        {
            current = dominos[i];
        }
        else
        {
            continue;
        }
        if (current.leftDots == r)
        {
            vector<dominoT> remains = dominos;
            dominoT temp = remains[i];
            temp.index = ++ri;
            temp.taken = true;
            out.push_back(temp);
            remains.erase(remains.begin() + i);
            if (FormsDominoChain(remains, current.rightDots, l, base))
            {
                return true;
            }
        }
        if (current.rightDots == l)
        {
            vector<dominoT> remains = dominos;
            dominoT temp = remains[i];
            temp.index = --li;
            temp.taken = true;
            out.push_back(temp);
            remains.erase(remains.begin() + i);
            if (FormsDominoChain(remains, r, current.leftDots, base))
            {
                return true;
            }
        }
    }

    return false;
}

void dominoCallFunction()
{
    vector<dominoT> dominos;
    int n;
    cout << "how many dominos to enter: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cout << "enter left and right: ";
        cin >> l >> r;
        dominoT d(l, r);
        dominos.push_back(d);
    }

    vector clone = dominos;
    clone.erase(clone.begin() + 0);

    if (!FormsDominoChain(clone, dominos[0].rightDots, dominos[0].leftDots, dominos[0]))
    {
        cout << "Cannot perform a sequence";
    }
}

unordered_map<string, vector<string>> lookupTable = {
    {"حرب", {"نزاع", "صراع"}},
    {"قتال", {"اشتباك", "مواجهة"}},
    {"سلاح", {"أداة", "معدات"}},
    {"مقاومة", {"دفاع", "صمود"}},
    {"جندي", {"فرد", "عنصر"}},
    {"رصاصة", {"طلقة", "شحنة"}},
    {"جيش", {"قوات", "تشكيل"}},
    {"غزو", {"دخول", "اجتياح"}},
    {"دم", {"سائل", "نسيج"}},
    {"شهيد", {"ضحية", "فقيد"}},
    {"قنبلة", {"عبوة", "مادة"}},
    {"صاروخ", {"قذيفة", "مقذوف"}},
    {"هجوم", {"عملية", "فعل"}},
    {"انقلاب", {"تغيير", "انتقال"}},
    {"احتجاج", {"تظاهر", "تجمع"}},
    {"مسلح", {"متمرد", "مقاتل"}},
    {"طائرة", {"مركبة", "ناقلة"}},
    {"دبابة", {"عربة", "مركبة"}},
    {"حريق", {"اشتعال", "نار"}},
    {"تدمير", {"إتلاف", "إلغاء"}},
    {"انفجار", {"تفجير", "حدث"}},
    {"اغتيال", {"تصفية", "إنهاء"}},
    {"عنف", {"شدة", "قسوة"}},
    {"إرهاب", {"تخويف", "ذعر"}},
    {"معركة", {"مواجهة", "مناوشة"}},
    {"خيانة", {"غدر", "خذلان"}},
    {"حصار", {"طوق", "إغلاق"}},
    {"مخيم", {"معسكر", "تجمع"}},
    {"احتلال", {"سيطرة", "إدارة"}},
    {"تهديد", {"تحذير", "إنذار"}}};

void fileReplacement()
{
    srand(static_cast<unsigned int>(time(0)));

    ifstream file;
    ofstream newFile("new.txt");
    file.open("test.txt");
    while (!file.eof())
    {
        string s;
        file >> s;
        string strippedWord = s;

        // while (!strippedWord.empty() && ispunct(strippedWord.back())) | NOT WORKING |
        // {
        //     strippedWord.pop_back();
        // }
        bool isStripped = false;

        if (s.substr(0, 4) == "ال")
        {
            isStripped = true;
            strippedWord = s.substr(4);
        }

        if (lookupTable.find(strippedWord) != lookupTable.end())
        {
            const vector<string> &alternatives = lookupTable[strippedWord];

            int randomIndex = rand() % alternatives.size();
            string chosenAlternative = alternatives[randomIndex];

            cout << "Original Word: " << s << "\n";
            cout << "Random Alternative: " << "ال" << chosenAlternative << endl;
            if (isStripped)
            {
                newFile << "ال";
            }

            newFile << chosenAlternative << " ";
        }
        else
        {
            newFile << s << " ";
        }
        // cout << s << "\n";
    }

    file.close();
}

int main()
{
    fileReplacement();
    return 0;
}