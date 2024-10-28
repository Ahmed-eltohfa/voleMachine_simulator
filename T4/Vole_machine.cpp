#include "Vole_machine.h"

void Machine::loadProgram(const vector<string> &program)
{
    for (int i = 0; i < program.size(); i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int byte = stoi(program[i].substr(j * 2, j + 2), 0, 16);
            memory.store(2 * i + j, byte);
        }
    }
}

void Machine::fetchAndExecute()
{
    stringstream s;
    s << hex << memory.load(pc.getValue()) << hex << memory.load(pc.getValue() + 1);
    string instruction(s.str());
    if (instruction.length() == 3)
    {
        instruction = instruction.substr(0, 2) + "0" + instruction.substr(2, 3);
    }

    cout << "ins: " << instruction << "\n";
    char op = instruction[0];
    string regS(1, instruction[1]);
    string desS(1, instruction[2]);
    string desS2(1, instruction[3]);
    int reg = stoi(regS);
    int msgAdrs = stoi(instruction.substr(2, 3), 0, 16);
    int three, four;
    try
    {
        three = stoi(desS);
        four = stoi(desS2);
    }
    catch (const std::exception &e)
    {
        three = stoi(desS, 0, 16);
        four = stoi(desS2, 0, 16);
    }

    if (op == '1')
    {
        LoadInstruction ins(reg, msgAdrs, false);
        Instruction *temp = new LoadInstruction(ins);
        ir.set(temp);
    }
    else if (op == '2')
    {
        LoadInstruction ins(reg, msgAdrs, true);
        Instruction *temp = new LoadInstruction(ins);
        ir.set(temp);
    }
    else if (op == '3')
    {
        StoreInstruction ins(reg, msgAdrs);
        Instruction *temp = new StoreInstruction(ins);
        ir.set(temp);
    }
    else if (op == '4')
    {
        MoveInstruction ins(three, four);
        Instruction *temp = new MoveInstruction(ins);
        ir.set(temp);
    }
    else if (op == '5')
    {
        AddInstruction ins(reg, three, four, false);
        Instruction *temp = new AddInstruction(ins);
        ir.set(temp);
    }
    else if (op == '6')
    {
        AddInstruction ins(reg, three, four, true);
        Instruction *temp = new AddInstruction(ins);
        ir.set(temp);
    }
    else if (op == 'B' || op == 'b')
    {
        JumpInstruction ins(reg, msgAdrs);
        Instruction *temp = new JumpInstruction(ins);
        ir.set(temp);
    }
    else if (op == 'C' || op == 'c')
    {
        halt();
    }
    else
    {
        return;
    }

    ir.get()->execute(*this);
    pc.increment();
    pc.increment();
}

void Machine::displayStatus() const
{
    cout << "Output Screen: " << hex << memory.load(0x00) << "\n";
    for (int i = 0; i < registers.size(); i++)
    {
        cout << "R" << i << " : " << hex << registers[i].getValue() << "\n";
    }
    memory.displayMemory();
}

int Memory::load(int address) const
{
    if (address <= 255)
    {
        return memoryCells[address];
    }

    return 0;
}

void Memory::store(int address, int value)
{
    memoryCells[address] = value;
}

void Memory::displayMemory() const
{
    cout << "mem\n";
    for (int i = 0; i < 12; i++)
    {
        cout << hex << memoryCells[i] << "\n";
    }
}

void LoadInstruction::execute(Machine &machine)
{
    if (value)
    {
        cout << "load instruction success ture\n";
    }
    else
    {
        cout << "load instruction success false\n";
    }
}

void AddInstruction::execute(Machine &machine)
{
    cout << "Add instruction success \n";
}

void StoreInstruction::execute(Machine &machine)
{
    cout << "Store instruction success \n";
}

void JumpInstruction::execute(Machine &machine)
{
    cout << "Jump instruction success \n";
}

void HaltInstruction::execute(Machine &machine)
{
    cout << "Halt instruction success \n";
}

void MoveInstruction::execute(Machine &machine)
{
    cout << "Move instruction success";
}
