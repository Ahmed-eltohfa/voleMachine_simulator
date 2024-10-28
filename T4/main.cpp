#include "Vole_machine.h"
#include "Vole_machine.cpp"
#include <fstream>

using namespace std;

vector<string> loadProgramFromFile(const string &filePath)
{
    vector<string> program;
    ifstream file(filePath);
    string instruction;

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filePath << "\n";
        return program;
    }

    while (file >> instruction)
    {
        program.push_back(instruction);
    }

    file.close();
    return program;
}

int main()
{
    Machine voleMachine;    // Initialize the Vole machine object
    vector<string> program; // Stores the loaded program
    bool exitFlag = false;
    int choice;

    // Simple menu loop
    while (!exitFlag)
    {
        cout << "\n--- Vole Machine Simulator ---" << "\n";
        cout << "1. Load Program from File" << "\n";
        cout << "2. Execute Program Step-by-Step" << "\n";
        cout << "3. Display Machine Status" << "\n";
        cout << "4. Exit" << "\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // load instruction file
        {
            string filePath;
            cout << "Enter file path: ";
            cin >> filePath;
            program = loadProgramFromFile(filePath);
            if (!program.empty())
            {
                voleMachine.loadProgram(program);
                cout << "Program loaded successfully." << "\n";
            }
            break;
        }
        case 2: // Execute
        {
            if (program.empty())
            {
                cout << "No program loaded! Please load a program first." << "\n";
                break;
            }

            // Step-by-step execution
            while (voleMachine.running())
            {
                voleMachine.fetchAndExecute();
                voleMachine.displayStatus();

                char stepChoice;
                cout << "Press 'n' to continue, or 'q' to stop: ";
                cin >> stepChoice;

                if (stepChoice == 'q')
                {
                    break;
                }
            }
            break;
        }
        case 3: // Display
        {
            // Display the current status of the machine
            voleMachine.displayStatus();
            break;
        }
        case 4:
        {
            exitFlag = true;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << "\n";
        }
        }
    }

    cout << "Exiting simulator. Goodbye!" << "\n";
    return 0;
}