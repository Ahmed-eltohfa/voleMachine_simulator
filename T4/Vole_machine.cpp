#include "Vole_machine.h"

Machine::Machine()
{
}

Machine::~Machine()
{
}

Machine::loadProgram(const std::vector<std::string> &program)()
{
}

void Machine::fetchAndExecute()
{
}

void Machine::displayStatus() const
{
}

int Memory::load(int address) const
{
    return 0;
}

void Memory::store(int address, int value)
{
}

void Memory::displayMemory() const
{
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
