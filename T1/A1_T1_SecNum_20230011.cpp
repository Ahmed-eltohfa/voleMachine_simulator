// Name     : Ahmed Ehab Salah Elden
// ID       : 20230011
// Problems : (1) formate text (4) print prime nums (7) forms domino chain (11) file Censorship in arabic
// version  : (1.4)v

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iomanip>
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
    cout << "Formated text => " << out << "\n";
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
    cout << "Prime list => ";
    for (int num : numList)
    {
        if (num != 0)
        {
            cout << num << " ";
        }
    }
    cout << "\n";
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
    cout << "\n";
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

void fileReplacement(string fileName)
{
    srand(static_cast<unsigned int>(time(0)));
    cout << "Note: your terminal should support unicode to see the next lines :)\n";
    ifstream file;
    file.open(fileName);
    string newfileName;
    cout << "Please enter your file name to output here, and don't forget the .txt extension : ";
    cin >> newfileName;

    ofstream newFile(newfileName);
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
            cout << "Random Alternative: " << "ال" << chosenAlternative << "\n";
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
    cout << setw(25) << " " << "Welcome to Section 3 of the Problem Sheet, Task 1\n";
    while (true)
    {
        cout << "A)Problem 1 (Formate text)\n";
        cout << "B)Problem 4 (Print prime numbers within range)\n";
        cout << "C)Problem 7 (The game of dominos)\n";
        cout << "D)Problem 10 (Censorship of file in Arabic)\n";
        cout << "Please choose a char: ";
        string Input;
        cin >> Input;
        if (Input.size() == 1)
        {
            Input[0] = tolower(Input[0]);
        }
        while (Input.size() != 1 || (Input != "a" && Input != "b" && Input != "c" && Input != "d"))
        {
            cout << "Invalid input PLEASE a VALID choose one of these choices (A,B,C,D)\n";
            cout << "Please choose a char: ";
            cin >> Input;
            if (Input.size() == 1)
            {
                Input[0] = tolower(Input[0]);
            }
        }

        if (Input == "a")
        {
            cout << setw(12) << " " << "Problem 1\n";
            cin.ignore();
            formateTxt();
        }
        else if (Input == "b")
        {
            cout << setw(12) << " " << "Problem 4\n";
            cin.ignore();
            printPrime();
        }
        else if (Input == "c")
        {
            cout << setw(12) << " " << "Problem 7\n";
            cin.ignore();
            dominoCallFunction();
        }
        else
        {
            cout << setw(12) << " " << "Problem 10\n";
            string FileName;
            cout << "Please enter your file name here, and don't forget the .txt extension : ";
            cin >> FileName;
            cout << "\n";
            fstream dataFile;
            dataFile.open(FileName);
            while (dataFile.fail())
            {
                cout << "File open error! Please enter a valid file name: ";
                cin >> FileName;
                dataFile.open(FileName);
                cout << "\n";
            }
            fileReplacement(FileName);
            cout << "\n";
        }

        cout << "Thank you for using my program :)\n";
        cout << "A)Again\nB)Exit\n";
        string again;
        cin >> again;
        if (again.size() == 1)
        {
            again[0] = tolower(again[0]);
        }
        while (again.size() != 1 || (again != "a" && again != "b"))
        {
            cout << "Invalid input PLEASE choose one of these choices (A,B)\n";
            cout << "A)Again\n";
            cout << "B)Exit\n";
            cin >> again;
            if (again.size() == 1)
            {
                again[0] = tolower(again[0]);
            }
        }
        if (again == "b")
        {
            cout << "BYE :)\n";
            break;
        }
        cout << "\nPlease choose a char\n\n";
    }
    return 0;
}
