#include "Vole_machine.h"

void Machine::loadProgram(const std::vector<std::string> &program)
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
    if (value)
    {
        machine.getRegister(registerIndex).setValue(machine.getMemory().load(address));
    }
    else
    {
        machine.getRegister(registerIndex).setValue(address);
    }
}

void StoreInstruction::execute(Machine &machine)
{
    machine.getMemory().store(address, machine.getRegister(registerIndex).getValue());

    if (address == 0)
    {
        cout << "Output to screen: " << machine.getRegister(registerIndex).getValue() << "\n";
    }
}

void AddInstruction::execute(Machine &machine)
{
    if (isFloat)
    {
    }
    else
    {
        machine.getRegister(regDst).setValue(machine.getRegister(regSrc1).getValue() + machine.getRegister(regSrc2).getValue());
    }
}

void JumpInstruction::execute(Machine &machine)
{
    if (machine.getRegister(registerIndex).getValue() == machine.getRegister(0).getValue())
    {
        machine.getPC().setValue(address);
    }
}

void HaltInstruction::execute(Machine &machine)
{
    machine.halt();
    cout << "Machine execution has stopped\n";
}
