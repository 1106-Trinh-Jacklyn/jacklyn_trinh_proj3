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
    stringstream stream(line);

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
    
    for(int i = 0; i < op.length(); i++){
        op[i] = toupper(op[i]);
    }

    if(op == "MOV"){
        int Rd = stoi(parts[1].substr(1));
        uint32_t IMM = stoul(parts[2].substr(2), nullptr, 16);
        registers[Rd] = IMM;
    }
    else if(op == "ADD" || op == "ADDS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        uint32_t result = (uint32_t)registers[Rn] + registers[Rm];
        registers[Rd] = result & 0xFFFF;

        if(op == "ADDS"){
            updateFlagsForAdd(registers[Rn], registers[Rm], result);
        }
    }
    else if(op == "SUB" || op == "SUBS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int Rm = stoi(parts[3].substr(1));

        uint32_t result = (uint32_t)registers[Rn] - registers[Rm];
        registers[Rd] = result & 0xFFFF;

        if(op == "SUBS"){
            updateFlagsForSub(registers[Rn], registers[Rm], result);
        }
    }
    else if(op == "AND" || op == "ANDS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));

        registers[Rd] = registers[Rd] & registers[Rn];

        if(op == "ANDS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "ORR" || op == "ORRS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));

        registers[Rd] = registers[Rd] | registers[Rn];

        if(op == "ORRS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "XOR" || op == "XORS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));

        registers[Rd] = registers[Rd] ^ registers[Rn];

        if(op == "XORS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "CMP"){
        int Rn = stoi(parts[1].substr(1));
        int Rm = stoi(parts[2].substr(1));

        uint32_t result = (uint32_t)registers[Rn] - registers[Rm];

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

        registers[Rd] = registers[Rn] >> shift;

        if(op == "LSRS"){
            updateFlags(registers[Rd]);
        }
    }
    else if(op == "LSL" || op == "LSLS"){
        int Rd = stoi(parts[1].substr(1));
        int Rn = stoi(parts[2].substr(1));
        int shift = stoi (parts[3].substr(1));

        registers[Rd] = registers[Rn] << shift;

        if(op == "LSLS"){
            updateFlags(registers[Rd]);
        }
    }

    printState(instruction);
}

void Machine::printState(const string& instruction){
    cout << instruction << endl;
    
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ":0x" << hex << uppercase << registers[i] << " ";
    }

    cout << endl;
    cout << "N = " << N << " Z = " << Z << " C = " << C << " V = " << V << endl;
}

void Machine::updateFlags(uint32_t result){
    if(result == 0){
        Z = 1;
    }
    else{
        Z = 0;
    }

    if((result & 0x80000000) == 0){
        N = 0;
    }
    else{
        N = 1;
    }
}

void Machine::updateFlagsForAdd(uint32_t num1, uint32_t num2, uint32_t result){
    updateFlags(result & 0xFFFF);

    uint64_t sum = (uint64_t)num1 + (uint64_t)num2;
    C = (sum >> 32) & 1;
    V = ((num1 >> 31) == (num2 >> 31)) && ((num1 >> 31) != ((result >> 31) & 1));
}

void Machine::updateFlagsForSub(uint32_t num1, uint32_t num2, uint32_t result){
    updateFlags(result & 0xFFFF);

    if(num1 >= num2){
        C = 1;
    }
    else{
        C = 0;
    }

    V = ((num1 >> 31) != (num2 >> 31)) && ((num1 >> 31) != ((result >> 31) & 1));
}