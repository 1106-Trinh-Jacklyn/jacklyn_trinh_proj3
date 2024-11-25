#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <sstream>

using namespace std;

class Machine{
    int N = 0;
    int Z = 0;
    int C = 0;
    int V = 0;
    uint32_t registers[8] = {0};

    void updateFlags(uint32_t result);
    void updateFlagsForAdd(uint32_t num1, uint32_t num2, uint32_t result);
    void updateFlagsForSub(uint32_t num1, uint32_t num2, uint32_t result);

    vector<string> split(const string& line);
    void executeInstruction(const string& instruction);
    void printState(const string& instruction);

    public:
        void file(const string& filename);
};

#endif