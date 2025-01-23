#include <stdio.h>
#include <string.h>

#define MEM_SIZE 256 /*Size of the memory*/
#define REG_SIZE 8 /*Size of the register*/
#define REG_A_INDEX 102 /*Index of register A in the memory*/
#define REG_B_INDEX 103 /*Index of register B in the memory*/

/*Define a structure*/
typedef struct {
    char A[REG_SIZE]; /*Register A*/
    char B[REG_SIZE]; /*Register B*/
    char program_counter[2][REG_SIZE + 1]; /*Program counter*/
    char instr_reg[3][REG_SIZE + 1]; /*Instruction register*/
    char memory[MEM_SIZE][REG_SIZE + 1];  /*Memory array*/
} Vizmachine;

void load_to_memory(Vizmachine *simulator, const char *file); /*Function to load assembly code into memory*/
const char *opcode_to_binary(const char *instruction); /*Function to convert opcode to binary*/
int to_binary(int decimal_number); /*Convert a decimal number to binary*/
int to_decimal(const char binary_number[]); /*Convert a binary number to decimal*/
int my_atoi(const char *str); /*Convert a string to an integer*/
int my_isdigit(char c); /* Function to check if a character is a digit*/

int main() {
    Vizmachine simulator;
    int cont; /*Continue flag*/
    char filename[100];

    do {
        printf("Enter the filename: "); /*Promt for filename*/
        scanf("%s", filename);

        FILE *file = fopen(filename, "r"); /*Open the file for reading*/
        if (file == NULL) { /*Check if file opened successfully*/
            printf("Failed to open file. Please enter a valid filename.\n");
            continue;
        }
        
        load_to_memory(&simulator, filename); /*Load file into memory*/
        fclose(file);

        while (1) {
            printf("Do you want to execute another assembly code? Press (1) for yes, Press (0) for exit: "); /*Prompt for continuation*/
            scanf("%d", &cont); 
            if (cont == 0 || cont == 1) { /*Check if input is valid*/
                break;
            } else {
                printf("INVALID INPUT. PLEASE ENTER 1 OR 0!!!\n"); /*Error message for invalid input*/
            }
        }

        if(cont == 0){
            printf("SEE YOU SOON!!!\n");
        }
        
    } while (cont != 0);

    return 0;
}

const char *opcode_to_binary(const char *instruction) {
    /*Compare instruction with known opcodes and return corresponding binary string*/
    if (strcmp(instruction, "ADD") == 0) return "00000001";
    if (strcmp(instruction, "ADDI") == 0) return "00000010";
    if (strcmp(instruction, "ADDM") == 0) return "00000011";
    if (strcmp(instruction, "AND") == 0) return "00000100";
    if (strcmp(instruction, "ANDI") == 0) return "00000101";
    if (strcmp(instruction, "ANDM") == 0) return "00000110";
    if (strcmp(instruction, "OR") == 0) return "00000111";
    if (strcmp(instruction, "ORI") == 0) return "00001000";
    if (strcmp(instruction, "ORM") == 0) return "00001001";
    if (strcmp(instruction, "SUB") == 0) return "00001010";
    if (strcmp(instruction, "SUBI") == 0) return "00001011";
    if (strcmp(instruction, "SUBM") == 0) return "00001100";
    if (strcmp(instruction, "INC") == 0) return "00001101";
    if (strcmp(instruction, "DEC") == 0) return "00001110";
    if (strcmp(instruction, "SHL") == 0) return "00001111";
    if (strcmp(instruction, "SHR") == 0) return "00010000";
    if (strcmp(instruction, "BRE") == 0) return "00010001";
    if (strcmp(instruction, "BRN") == 0) return "00010010";
    if (strcmp(instruction, "J") == 0) return "00010011";
    if (strcmp(instruction, "NOR") == 0) return "00010100";
    if (strcmp(instruction, "LDA") == 0) return "00010101";
    if (strcmp(instruction, "STR") == 0) return "00010110";
    if (strcmp(instruction, "SWP") == 0) return "00010111";
    if (strcmp(instruction, "LESS") == 0) return "00011000";
    if (strcmp(instruction, "GRT") == 0) return "00011001";
    if (strcmp(instruction, "PRI") == 0) return "00011010";
    if (strcmp(instruction, "PRII") == 0) return "00011011";
    if (strcmp(instruction, "PRIM") == 0) return "00011100";
    if (strcmp(instruction, "LDAI") == 0) return "00011101";
    if (strcmp(instruction, "EXIT") == 0) return "00011110";
    return NULL; /*Return NULL if instruction is unknown*/
}

void load_to_memory(Vizmachine *simulator, const char *filename) {
    int i, j;
    /*Initialize all memory cells to 0*/
    for (i = 0; i < MEM_SIZE; i++) {
        for (j = 0; j < REG_SIZE; j++) {
            simulator->memory[i][j] = '0';
        }
        simulator->memory[i][REG_SIZE] = '\0'; 
    }

    /*Pre fill memory cells with the values*/
    strcpy(simulator->memory[99], "00000101"); 
    strcpy(simulator->memory[100], "00000110");

    /*Initialize program counter cells with values 0 and 1*/
    snprintf(simulator->memory[103], REG_SIZE + 1, "%08d", 0);
    snprintf(simulator->memory[104], REG_SIZE + 1, "%08d", 1);

    /*Open assembly file for reading*/
    FILE *inp = fopen(filename, "r");
    if (inp == NULL) {
        printf("Failed to open file");
        return;
    }

    char line[100]; 
    int mem_index = 0;

    /*Read lines from the file*/
    while (fgets(line, sizeof(line), inp) != NULL && mem_index + 2 < MEM_SIZE) {
        line[strcspn(line, "\n")] = '\0';

        /*Divide the readed line based on the spaces*/
        char *instruction = strtok(line, " ");
        char *operand1 = strtok(NULL, " ");
        char *operand2 = strtok(NULL, " ");

        /*Takes the string representing an assembly instruction and returns a string containing the corresponding binary number*/
        const char *binary_opcode = opcode_to_binary(instruction);
        /*Check if the instruction is valid*/
        if (binary_opcode == NULL) {
            printf("Unknown instruction: %s\n", instruction);
            fclose(inp);
            return;
        }
        /*Store the binary instruction in memory*/        
        strncpy(simulator->memory[mem_index], binary_opcode, REG_SIZE);
        mem_index++;

        /*Store operand 1 in memory, or '00000000' if absent*/
        if (operand1 != NULL) { /*Check if the operand1 exists*/
            if (strcmp(operand1, "A") == 0) { /*Check if operand1 is the register "A"*/
                int binary_operand1 = to_binary(REG_A_INDEX); /*Convert the index of register A to binary*/
                char binary_operand1_str[REG_SIZE + 1]; /*Create a string to hold the binary representation*/
                snprintf(binary_operand1_str, sizeof(binary_operand1_str), "%08d", binary_operand1); /*Format the binary number as an 8-digit string*/
                strncpy(simulator->memory[mem_index], binary_operand1_str, REG_SIZE); /*Copy the binary string to the memory at the current index*/
            } else if (strcmp(operand1, "B") == 0) {
                int binary_operand1 = to_binary(REG_B_INDEX);
                char binary_operand1_str[REG_SIZE + 1];
                snprintf(binary_operand1_str, sizeof(binary_operand1_str), "%08d", binary_operand1);
                strncpy(simulator->memory[mem_index], binary_operand1_str, REG_SIZE);
            } else if (my_isdigit(operand1[0])) { /*Check if operand1 is a number or not*/
                int binary_operand1 = to_binary(my_atoi(operand1)); /*Convert the string to an integer, then to binary*/
                char binary_operand1_str[REG_SIZE + 1];
                snprintf(binary_operand1_str, sizeof(binary_operand1_str), "%08d", binary_operand1);
                strncpy(simulator->memory[mem_index], binary_operand1_str, REG_SIZE);
            } else {
                strncpy(simulator->memory[mem_index], operand1, REG_SIZE); /*Copy the operand directly to the memory at the current index*/
            }
        } else {
            /*If operand1 is absent, fill memory with '00000000' using a loop*/
            for (j = 0; j < REG_SIZE; j++) {
                simulator->memory[mem_index][j] = '0'; /*Set each bit to '0'*/
            }
        }
        mem_index++; /*Move to the next memory index for the next part of the instruction*/

        /*Store operand2 in memory, or '00000000' if absent*/
        if (operand2 != NULL) {
            if (strcmp(operand2, "A") == 0) {
                int binary_operand2 = to_binary(REG_A_INDEX); /*Convert the index of register A to binary*/
                char binary_operand2_str[REG_SIZE + 1];
                snprintf(binary_operand2_str, sizeof(binary_operand2_str), "%08d", binary_operand2);
                strncpy(simulator->memory[mem_index], binary_operand2_str, REG_SIZE);  /*Copy the binary string to the memory at the current index*/
            } else if (strcmp(operand2, "B") == 0) {
                int binary_operand2 = to_binary(REG_B_INDEX);
                char binary_operand2_str[REG_SIZE + 1];
                snprintf(binary_operand2_str, sizeof(binary_operand2_str), "%08d", binary_operand2);
                strncpy(simulator->memory[mem_index], binary_operand2_str, REG_SIZE);
            } else if (my_isdigit(operand2[0])) {
                int binary_operand2 = to_binary(my_atoi(operand2));
                char binary_operand2_str[REG_SIZE + 1];
                snprintf(binary_operand2_str, sizeof(binary_operand2_str), "%08d", binary_operand2);
                strncpy(simulator->memory[mem_index], binary_operand2_str, REG_SIZE);
            } else {
                strncpy(simulator->memory[mem_index], operand2, REG_SIZE);
            }
        } else {
            /*If operand2 is absent, fill memory with '00000000' using a loop*/
            for (j = 0; j < REG_SIZE; j++) {
                simulator->memory[mem_index][j] = '0';
            }
        }
        mem_index++;
    }

    /*Close the file*/
    fclose(inp);

    /*Print the contents of memory*/
    for (i = 0; i < MEM_SIZE; i++) {
        printf("%3d: ", i + 1);
        for (j = 0; j < REG_SIZE; j++) {
            printf("%c", simulator->memory[i][j]);
        }
        printf("\n");
    }
}

int to_binary(int decimal_number) {
    int binary_number = 0, indx = 1;

    while (decimal_number > 0) {
        int remnd = decimal_number % 2; /*Get the remainder*/
        decimal_number /= 2; /*Update the decimal number*/
        binary_number += remnd * indx; /*Add the current binary digit to the correct place value in the result*/
        indx *= 10; /* Update the place value to the next position*/
    }

    return binary_number;
}

int to_decimal(const char binary_number[]) {
    int decimal_number = 0, base = 0, i;

    for (i = 7; i >= 0; i--) { /*Loop through the binary string from right to left*/
        if (binary_number[i] == '1') { /*Check if the current bit is '1'*/
            decimal_number += base; /*If '1', add the current base value to the decimal number*/
        }
        base *= 2; /*Update the base value to the next power of 2*/
    }
    return decimal_number;
}

int my_atoi(const char *str) {
    int result = 0, i = 0;
    while (str[i] != '\0') { /*Loop through the string until the null terminator is reached*/
        result = result * 10 + (str[i] - '0'); /*Convert the current character to an integer and add it to the result*/
        i++; /*Move to the next character*/
    }
    return result;
}

int my_isdigit(char c) {
    if (c >= '0' && c <= '9') {  /*Check if the character is between '0' and '9'*/
        return 1;  /*Return 1 (true) if the character is a digit*/
    } else {
        return 0;  /*Return 0 (false) if the character is not a digit*/
    }
}

