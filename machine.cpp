#include "machine.h"

void Machine::file(const string& filename){
    ifstream file(filename);

    if(!file.is_open()){
        cout << "Can't open file." << endl;
        return;
    }

    string line;

    while(getline(file, line)){
        executeInstruction(line);
    }

    file.close();
}

vector<string> Machine::split(const string& line){
    vector<string> parts;
    string part;
    istringstream stream(line);

    while(stream >> part){
        parts.push_back(part);
    }

    return parts;
}

void Machine::executeInstruction(const string& instruction){
    vector<string> parts = split(instruction);
    if(parts.empty()){
        return;
    }

    string op = parts[0];
    
    for(int i = 0; i < op.size(); i++){
        op[i] = toupper(op[i]);
    }

    if(op == "MOV"){
        int Rd = stoi(parts[1].substr(1));
        string immStr = parts[2];
        if(immStr[0] == '#'){
            immStr = immStr.substr(1);
        }
        try{
            uint32_t IMM = stoul(immStr, nullptr, 0);
            registers[Rd] = IMM;
        }catch(const exception &e){
            cout << "Invalid immediate value: " << parts[2] << endl;
        }
    }
    else if(op == "ADD" || op == "ADDS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        uint32_t result = registers[Rn] + registers[Rm];
        registers[Rd] = result;

        if(op == "ADDS"){
            updateFlagsForAdd(registers[Rn], registers[Rm], result);
        }
    }
    else if(op == "SUB" || op == "SUBS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        uint32_t result = registers[Rn] - registers[Rm];
        registers[Rd] = result;

        if(op == "SUBS"){
            updateFlagsForSub(registers[Rn], registers[Rm], result);
        }
    }
    else if(op == "AND" || op == "ANDS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        registers[Rd] = registers[Rn] & registers[Rm];

        if(op == "ANDS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "ORR" || op == "ORRS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        registers[Rd] = registers[Rn] | registers[Rm];

        if(op == "ORRS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "XOR" || op == "XORS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        registers[Rd] = registers[Rn] ^ registers[Rm];

        if(op == "XORS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "CMP"){
        int Rn = stoi(parts[1].substr(1));
        int Rm = stoi(parts[2].substr(1));

        uint32_t result = registers[Rn] - registers[Rm];

        updateFlagsForSub(registers[Rn], registers[Rm], result);
    }
    else if(op == "TST"){
        int Rn = stoi(parts[1].substr(1));
        int Rm = stoi(parts[2].substr(1));

        uint32_t result = registers[Rn] & registers[Rm];

        updateFlags(result);
    }
    else if(op == "LSR" || op == "LSRS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int shift = stoi (parts[3].substr(1));

        if(shift > 0){
            C = (registers[Rn] & (1 << (shift - 1))) != 0;
            registers[Rd] = registers[Rn] >> shift;
        }
        else{
            C = 0;
            registers[Rd] = registers[Rn];
        }

        if(op == "LSRS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "LSL" || op == "LSLS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int shift = stoi (parts[3].substr(1));

        if(shift > 0){
            C = (registers[Rn] & (1 << (32 - shift))) != 0;
            registers[Rd] = registers[Rn] << shift;
        }
        else{
            C = 0;
            registers[Rd] = registers[Rn];
        }

        if(op == "LSLS"){
            updateFlags(registers[Rd]);
        }
    }
    else{
        cout << "Invalid instruction: " << instruction << endl;
    }

    printState(instruction);
}

void Machine::printState(const string& instruction){
    cout << instruction << endl;
    
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ":0x" << uppercase << setw(8) << setfill('0') << hex << registers[i] << " ";
        if(i == 3){
            cout << endl;
        }
    }

    cout << endl;
    cout << "N = " << N << " Z = " << Z << " C = " << C << " V = " << V << endl;
}

void Machine::updateFlags(uint32_t result){
    Z = (result == 0);
    N = (result & 0x80000000) != 0;
}

void Machine::updateFlagsForAdd(uint32_t num1, uint32_t num2, uint32_t result){
    updateFlags(result);
    C = (uint64_t(num1) + uint64_t(num2)) > 0xFFFFFFFF;
    V = (((num1 ^ ~num2) & (num1 ^ result)) & 0x80000000) != 0;
}

void Machine::updateFlagsForSub(uint32_t num1, uint32_t num2, uint32_t result){
    updateFlags(result);
    C = (num1 >= num2);
    V = (((num1 ^ num2) & (num1 ^ result)) & 0x80000000) != 0;
}