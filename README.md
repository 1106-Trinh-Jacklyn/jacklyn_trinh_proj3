# jacklyn_trinh_proj3

Run this code:
1. make
2. ./machine

Purpose: This program simulates a simplified machine language processor that interprets and executes assembly-like instructions resembling the ARMv7 ISA. The simulator supports a range of operations performed on a set of eight 32-bit registers (r0 to r7). The program updates register values and, for certain operations, modifies condition flags (N - negative, Z - zero, C - carry, V - overflow).

Working Process:
1. The input is read line by line.
   MOV Rd, #IMM: Moves the immediate constant IMM into register Rd.
   OPCODE Rd, Rn, Rm: Performs the operation OPCODE on registers Rn and Rm, storing the result in Rd.
   OPCODE Rd, Rn, #N: Performs a shift operation (logical left/right) on Rn by N bits, storing the result in Rd.
2. Registers (r0 to r7) and flags (N, Z, C, V) are initialized to zero before processing the instructions.
3. Each line is decoded and executed.
4. When a command with an 'S' suffix is executed, the flags are updated backed on the result. Otherwise, the flag do not change.
5. After executing each command, the program prints the instruction, the values of all registers, and the updated flag values.

Results:
1. Displays the instruction line.
2. Displays registers r0 to r7.
3. Displays the updated N, Z, C, and V flags.

Commands:
1. ADD: Adds two values.
2. AND: Bitwise AND of two values.
3. MOV: Moves the immediate operand into Rd.
4. LSR: Logical shift right.
5. LSL: Logical shift left.
6. CMP: Compares Rn and Rm (sets flags but doesn't update registers).
7. ORR: Bitwise OR operation.
8. SUB: Subtracts the second value from the first.
9. XOR: Bitwise XOR operation.
10. TST: Bitwise AND between Rn and Rm (sets flags but doesn't update registers).