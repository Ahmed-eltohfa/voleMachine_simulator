#include "Vole_machine.h"

void Machine::loadProgram(const vector<string> &program)
{
    for (int i = 0; i < program.size(); i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int byte = stoi(program[i].substr(j * 2, j + 2), 0, 16);
            getMemory().store(2 * i + j, byte);
        }
    }
}

void Machine::fetchAndExecute()
{
}

void Machine::displayStatus() const
{
}

int Memory::load(int address) const
{
    if (address >= 0 && address < memoryCells.size()) {
        return memoryCells[address];
    } else {
        cerr << "Error: Invalid memory access at address " << address << endl;
        return 0; 
    }
}

void Memory::store(int address, int value)
{    
    if (address >= 0 && address < memoryCells.size()) {
        memoryCells[address] = value;
    } else {
        cout << "Error: Invalid memory access at address " << address << endl;
    }
}

void Memory::displayMemory() const
{
    cout << "Memory Contents:" << endl;
    for (size_t i = 0; i < memoryCells.size(); ++i) {
        cout << "Address " << i << ": " << memoryCells[i] << endl;
    }
}

void LoadInstruction::execute(Machine &machine)
{
}

void AddInstruction::execute(Machine &machine)
{
}

void StoreInstruction::execute(Machine &machine)
{
}

void JumpInstruction::execute(Machine &machine)
{
}

void HaltInstruction::execute(Machine &machine)
{
}
