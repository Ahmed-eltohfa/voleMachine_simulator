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
    else if (op == '7')
    {
        SubtractInstruction ins(reg, three, four);
        Instruction *temp = new SubtractInstruction(ins);
        ir.set(temp);
    }
    else if (op == '8')
    {
        MultiplyInstruction ins(reg, three, four);
        Instruction *temp = new MultiplyInstruction(ins);
        ir.set(temp);
    }
    else if (op == '9')
    {
        DivideInstruction ins(reg, three, four);
        Instruction *temp = new DivideInstruction(ins);
        ir.set(temp);
    }
    else if (op == 'A' || op == 'a')
    {
        OrInstruction ins(reg, three, four);
        Instruction *temp = new OrInstruction(ins);
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
    else if (op == 'D' || op == 'd')
    {
        AndInstruction ins(reg, three, four);
        Instruction *temp = new AndInstruction(ins);
        ir.set(temp);
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
    if (address >= 0 && address < memoryCells.size())
    {
        return memoryCells[address];
    }
    else
    {
        cerr << "Error: Invalid memory access at address " << address << "\n";
        return 0;
    }
}

void Memory::store(int address, int value)
{
    if (address >= 0 && address < memoryCells.size())
    {
        memoryCells[address] = value;
    }
    else
    {
        cout << "Error: Invalid memory access at address " << address << "\n";
    }
}

void Memory::displayMemory() const
{
    cout << "\n--- Memory Contents (16x16 Display) ---\n";
    cout << "      ";

    // Display column headers
    for (int col = 0; col < 16; ++col)
    {
        cout << " " << hex << uppercase << setw(2) << setfill('0') << col << " ";
    }
    cout << "\n";

    cout << "    ";
    cout << string(65, '-') << "\n";

    // Display each row with row headers
    for (int row = 0; row < 16; ++row)
    {
        // Display row header
        cout << "0x" << hex << uppercase << setw(2) << setfill('0') << row * 16 << " | ";

        // Display memory contents in 16 columns
        for (int col = 0; col < 16; ++col)
        {
            int address = row * 16 + col;
            cout << " " << setw(2) << setfill('0') << memoryCells[address] << " ";
        }
        cout << "\n";
    }
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
        machine.getRegister(regDst).setValue(machine.getRegister(regSrc1).getValue() + machine.getRegister(regSrc2).getValue());
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
    cout << "Halt instruction success \n";
}

void MoveInstruction::execute(Machine &machine)
{
    machine.getRegister(regSrc2).setValue(machine.getRegister(regSrc1).getValue());
}

void MultiplyInstruction::execute(Machine &machine)
{

    int result = machine.getRegister(regSrc1).getValue() * machine.getRegister(regSrc2).getValue();
    machine.getRegister(regDst).setValue(result);
}

void SubtractInstruction::execute(Machine &machine)
{

    int result = (machine.getRegister(regSrc1).getValue() - machine.getRegister(regSrc2).getValue()) & 0xFFFF;
    machine.getRegister(regDst).setValue(result);
}

void DivideInstruction::execute(Machine &machine)
{

    int result = (machine.getRegister(regSrc1).getValue() / machine.getRegister(regSrc2).getValue());
    machine.getRegister(regDst).setValue(result);
}

void OrInstruction::execute(Machine &machine)
{
    int result = machine.getRegister(regSrc1).getValue() | machine.getRegister(regSrc2).getValue();
    machine.getRegister(regDst).setValue(result);
}

void AndInstruction::execute(Machine &machine)
{
    int result = machine.getRegister(regSrc1).getValue() & machine.getRegister(regSrc2).getValue();
    machine.getRegister(regDst).setValue(result);
}
