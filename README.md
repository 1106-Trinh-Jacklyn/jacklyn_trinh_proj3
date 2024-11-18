# jacklyn_trinh_proj3

Run this code:
1. make
2. ./machine

Purpose: This program simulates a basic machine language operation with ADD, AND, ASR, LSR, LSL, NOT, ORR, SUB, and XOR. It reads input from a file containing commands then performs the operation with the given hexadecimal value(s). It also updates the flags if the command is followed by an 'S' and then displays the results.

Working Process:
1. The input is read line by line.
2. Each line is split into an operation and two hexadecimal values.
3. The two hexadecimal values are then stored using uint32_t.
4. For two operand commands (commands beside NOT and NOTS), the program process two values. For one operand commands, the program processes one value.
5. If the command if followed by an 'S', the flags are updated. If the result is 0, Z = 1. Otherwise, Z = 0. If the result is negative, N = 1. Otherwise, N = 0.
6. The inputs and results are then displayed in hexadecimal format following the example format. The N and Z flags are also displayed.

Results:
1. Displays the operation.
2. Displays the input numbers in hexadecimal format.
3. Displays the results of the operation in hexadecimal format.
4. Displays the N and Z flags.

Commands:
1. ADD/ADDS: Adds two values.
2. AND/ANDS: Bitwise AND of two values.
3. ASR/ASRS: Arithmetic shift right.
4. LSR/LSRS: Logical shift right.
5. LSL/LSLS: Logical shift left.
6. NOT/NOTS: Bitwise NOT of a value.
7. ORR/ORRS: Bitwise OR of two values.
8. SUB/SUBS: Subtracts the second value from the first.
9. XOR/XORS: Bitwise XOR of two values.