#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdint>

using namespace std;

class Machine{
    int N = 0, Z = 0;
    void print(string& operation, uint32_t num1, uint32_t num2, uint32_t result);
    void print(string& operation, uint32_t num, uint32_t result);
    void printShift(string& operation, uint32_t num, int shift, uint32_t result);
    void flag(uint32_t result);

    public:
        void file(const string& filename);
        void parse(const string& line);
        void addCmd(uint32_t num1, uint32_t num2, string operation);
        void andCmd(uint32_t num1, uint32_t num2, string operation);
        void asrCmd(uint32_t num, int shift, string operation);
        void lsrCmd(uint32_t num, int shift, string operation);
        void lslCmd(uint32_t num, int shift, string operation);
        void notCmd(uint32_t num, string operation);
        void orrCmd(uint32_t num1, uint32_t num2, string operation);
        void subCmd(uint32_t num1, uint32_t num2, string operation);
        void xorCmd(uint32_t num1, uint32_t num2, string operation);
        void addsCmd(uint32_t num1, uint32_t num2, string operation);
        void andsCmd(uint32_t num1, uint32_t num2, string operation);
        void asrsCmd(uint32_t num, int shift, string operation);
        void lsrsCmd(uint32_t num, int shift, string operation);
        void lslsCmd(uint32_t num, int shift, string operation);
        void notsCmd(uint32_t num, string operation);
        void orrsCmd(uint32_t num1, uint32_t num2, string operation);
        void subsCmd(uint32_t num1, uint32_t num2, string operation);
        void xorsCmd(uint32_t num1, uint32_t num2, string operation);
};

#endif