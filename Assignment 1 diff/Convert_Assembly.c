/*	Tanmay Garg Computer Architecture Assignment 1
*
*	To compile:
*	gcc -o Convert_Assembly Convert_Assembly.c -lm
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#define FILE_NAME_SIZE 30
#define MAX_NUM_ARGS 4
#define ARG_SIZE 10
#define STRING_SIZE 80
#define MIPS_ARCH 32
#define INS_NUM 30
#define REG_NUM 33


//Function corrects the string after taking input from fgets function to remove \n
void string_corrector(char *s)
{
	int len = strlen(s);
	if (s[len - 1] == '\n')
	{
		s[len - 1] = '\0';
	}
}

//Function to create name of output file from given input file
void output_file_name_creator_bin_mips(char *input_file_name, char *return_str)
{
    int i = 0;
    while(!(input_file_name[i] == 'b' && input_file_name[i + 1] == 'i' && input_file_name[i + 2] == 'n'))
    {
        return_str[i] = input_file_name[i];
        i++;
    }
    strcat(return_str, "asm.txt");
    
}

//Function convert given binary number into decimal in string format
void binary_to_dec(char *input_binary, char *output_num)
{
    // int binary_num = atoi(input_binary);
    // int num = 0;
    // int i = 0;
    // while(binary_num != 0)
    // {
    //     num = num + (binary_num % 10) * pow(2, i);
    //     binary_num = binary_num / 10;
    //     i++;
    // }
	long int num = strtol(input_binary, NULL, 2);
    sprintf(output_num, "%ld", num);
}

void bin_to_dec(char *input_binary, char *output_num)
{
    int num = 0;

}

//struct for storing mips instruction
typedef struct instruction_mips
{
	char instruction[ARG_SIZE];
	char opcode[7];
}instruction_mips;

//struct for storing mips register
typedef struct register_mips
{
	char register_name[ARG_SIZE];
	char binary[6];
}register_mips;

//Function to initialize the array of struct of instructions and registers
void struct_ini_instruction(instruction_mips *instruction_arr, register_mips *register_arr)
{
	instruction_arr[0] = (instruction_mips){"add", "100000"};
	instruction_arr[1] = (instruction_mips){"addi", "001000"};
	instruction_arr[2] = (instruction_mips){"and", "100100"};
	instruction_arr[3] = (instruction_mips){"andi", "001100"};
	instruction_arr[4] = (instruction_mips){"nor", "100111"};
	instruction_arr[5] = (instruction_mips){"or", "100101"};
	instruction_arr[6] = (instruction_mips){"ori", "001101"};
	instruction_arr[7] = (instruction_mips){"sll", "000000"};
	instruction_arr[8] = (instruction_mips){"srl", "000010"};
	instruction_arr[9] = (instruction_mips){"sub", "100010"};
	instruction_arr[10] = (instruction_mips){"slt", "101010"};
	instruction_arr[11] = (instruction_mips){"sltu", "101011"};
	instruction_arr[12] = (instruction_mips){"slti", "001010"};
	instruction_arr[13] = (instruction_mips){"sltiu", "001011"};
	instruction_arr[14] = (instruction_mips){"beq", "000100"};
	instruction_arr[15] = (instruction_mips){"bne", "000101"};
	instruction_arr[16] = (instruction_mips){"j", "000010"};
	instruction_arr[17] = (instruction_mips){"jal", "000011"};
	instruction_arr[18] = (instruction_mips){"jr", "001000"};
	instruction_arr[19] = (instruction_mips){"lb", "100000"};
	instruction_arr[20] = (instruction_mips){"lbu", "100100"};
	instruction_arr[21] = (instruction_mips){"lh", "100001"};
	instruction_arr[22] = (instruction_mips){"lhu", "100101"};
	instruction_arr[23] = (instruction_mips){"lw", "100011"};
	instruction_arr[24] = (instruction_mips){"sb", "101000"};
	instruction_arr[25] = (instruction_mips){"sh", "101001"};
	instruction_arr[26] = (instruction_mips){"sw", "101011"};
	instruction_arr[27] = (instruction_mips){"ll", "110000"};
	instruction_arr[28] = (instruction_mips){"sc", "111000"};
	instruction_arr[29] = (instruction_mips){"lui", "001111"};

	register_arr[0] = (register_mips){"$zero", "00000"};
	register_arr[1] = (register_mips){"$0", "00000"};
	register_arr[2] = (register_mips){"$at", "00001"};
	register_arr[3] = (register_mips){"$v0", "00010"};
	register_arr[4] = (register_mips){"$v1", "00011"};
	register_arr[5] = (register_mips){"$a0", "00100"};
	register_arr[6] = (register_mips){"$a1", "00101"};
	register_arr[7] = (register_mips){"$a2", "00110"};
	register_arr[8] = (register_mips){"$a3", "00111"};
	register_arr[9] = (register_mips){"$t0", "01000"};
	register_arr[10] = (register_mips){"$t1", "01001"};
	register_arr[11] = (register_mips){"$t2", "01010"};
	register_arr[12] = (register_mips){"$t3", "01011"};
	register_arr[13] = (register_mips){"$t4", "01100"};
	register_arr[14] = (register_mips){"$t5", "01101"};
	register_arr[15] = (register_mips){"$t6", "01110"};
	register_arr[16] = (register_mips){"$t7", "01111"};
	register_arr[17] = (register_mips){"$s0", "10000"};
	register_arr[18] = (register_mips){"$s1", "10001"};
	register_arr[19] = (register_mips){"$s2", "10010"};
	register_arr[20] = (register_mips){"$s3", "10011"};
	register_arr[21] = (register_mips){"$s4", "10100"};
	register_arr[22] = (register_mips){"$s5", "10101"};
	register_arr[23] = (register_mips){"$s6", "10110"};
	register_arr[24] = (register_mips){"$s7", "10111"};
	register_arr[25] = (register_mips){"$t8", "11000"};
	register_arr[26] = (register_mips){"$t9", "11001"};
	register_arr[27] = (register_mips){"$k0", "11010"};
	register_arr[28] = (register_mips){"$k1", "11011"};
	register_arr[29] = (register_mips){"$gp", "11100"};
	register_arr[30] = (register_mips){"$sp", "11101"};
	register_arr[31] = (register_mips){"$fp", "11110"};
	register_arr[32] = (register_mips){"$ra", "11111"};
}

//Function to convert binary into mips instruction form
void binary_opcode(char *binfunction, char *return_str, instruction_mips *arr_instruction)
{
	for(int i = 0; i < INS_NUM; i++)
	{
		if(strcmp(binfunction, arr_instruction[i].opcode) == 0)
		{
			strcpy(return_str, arr_instruction[i].instruction);
			return;
		}
	}
}

//Function to convert binary into mips instruction for data transfer instructions due to clash in their opcodes
void binary_opcode_data_transfer(char *binfunction, char *return_str, instruction_mips *arr_instruction)
{
	for(int i = 16; i < INS_NUM; i++)
	{
		if(strcmp(binfunction, arr_instruction[i].opcode) == 0)
		{
			strcpy(return_str, arr_instruction[i].instruction);
			return;
		}
	}
}

//Function to convert binary into mips register form
void binary_register(char *bin_function, char *return_str, register_mips *arr_register)
{
	for(int i = 0; i < REG_NUM; i++)
	{
		if(strcmp(bin_function, arr_register[i].binary) == 0)
		{
			strcpy(return_str, arr_register[i].register_name);
			return;
		}
	}
}

//Function to convert binary into JR instruction
void bin_to_mips_jr(char *input_binary_text, char *mips_instruction, register_mips *arr_reg)
{
	char register_mips[4] = "", tmp_rs[6] = "";
	strncpy(tmp_rs, input_binary_text + 6 * sizeof(char), 5);
	binary_register(tmp_rs, register_mips, arr_reg);
	sprintf(mips_instruction, "jr %s", register_mips);
}

////Function to convert binary into general R format instruction
void binary_gen_R_format_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char funct[10] = "", rs[4] = "", rt[4] = "", rd[4] = "";
    char tmp_funct[7] = "", tmp_rs[6] = "", tmp_rt[6] = "", tmp_rd[6] = "";

    strncpy(tmp_funct, input_binary_text + 26 * sizeof(char), 6);
    strncpy(tmp_rs, input_binary_text + 6 * sizeof(char), 5);
    strncpy(tmp_rt, input_binary_text + 11 * sizeof(char), 5);
    strncpy(tmp_rd, input_binary_text + 16 * sizeof(char), 5);
    
    binary_opcode(tmp_funct, funct, arr_ins);
    binary_register(tmp_rs, rs, arr_reg);
    binary_register(tmp_rt, rt, arr_reg);
    binary_register(tmp_rd, rd, arr_reg);

    sprintf(mips_instruction, "%s %s, %s, %s", funct, rd, rs, rt);

}

//Function to convert binary into SLL SRL instruction
void binary_sll_srl_to_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char funct[10] = "", rt[4] = "", rd[4] = "", shamt[6] = "";
    char tmp_funct[7] = "", tmp_rt[6] = "", tmp_rd[6] = "", tmp_shamt[6] = "";

    strncpy(tmp_funct, input_binary_text + 26 * sizeof(char), 6);
    strncpy(tmp_rt, input_binary_text + 11 * sizeof(char), 5);
    strncpy(tmp_rd, input_binary_text + 16 * sizeof(char), 5);
    strncpy(tmp_shamt, input_binary_text + 21 * sizeof(char), 5);

    binary_opcode(tmp_funct, funct, arr_ins);
    binary_register(tmp_rt, rt, arr_reg);
    binary_register(tmp_rd, rd, arr_reg);
    binary_to_dec(tmp_shamt, shamt);

    sprintf(mips_instruction, "%s %s, %s, %s", funct, rd, rt, shamt);

}

//Function to convert binary into J JAL instruction
void binary_j_jal_to_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char opcode[10] = "", immediate[10];
    char tmp_opcode[7] = "", tmp_immediate[27] = "";

    strncpy(tmp_opcode, input_binary_text, 6);
    strncpy(tmp_immediate, input_binary_text + 6 * sizeof(char), 26);

	if(strcmp(tmp_opcode, "000010") == 0)
	{
		strcpy(opcode, "j");
	}
	if(strcmp(tmp_opcode, "000011") == 0)
	{
		strcpy(opcode, "jal");
	}

    binary_to_dec(tmp_immediate, immediate);

    sprintf(mips_instruction, "%s %s", opcode, immediate);
}

//Function to convert binary into BEQ BNE instruction
void binary_beq_bne_to_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char opcode[10] = "", rs[4] = "", rt[4] = "", immediate[10] = "";
    char tmp_opcode[7] = "", tmp_rs[6] = "", tmp_rt[6] = "", tmp_immediate[17] = "";

	strncpy(tmp_opcode, input_binary_text, 6);
	strncpy(tmp_rs, input_binary_text + 6 * sizeof(char), 5);
	strncpy(tmp_rt, input_binary_text + 11 * sizeof(char), 5);
	strncpy(tmp_immediate, input_binary_text + 16 * sizeof(char), 16);

	binary_opcode(tmp_opcode, opcode, arr_ins);
	binary_register(tmp_rs, rs, arr_reg);
	binary_register(tmp_rt, rt, arr_reg);
	binary_to_dec(tmp_immediate, immediate);

	sprintf(mips_instruction, "%s %s, %s, %s", opcode, rs, rt, immediate);
    
}

//Function to convert binary into LUI instruction
void binary_lui_to_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char opcode[10] = "", rt[4] = "", immediate[10] = "";
    char tmp_opcode[7] = "", tmp_rt[6] = "", tmp_immediate[17] = "";

	strncpy(tmp_opcode, input_binary_text, 6);
	strncpy(tmp_rt, input_binary_text + 11 * sizeof(char), 5);
	strncpy(tmp_immediate, input_binary_text + 16 * sizeof(char), 16);

	binary_opcode(tmp_opcode, opcode, arr_ins);
	binary_register(tmp_rt, rt, arr_reg);
	binary_to_dec(tmp_immediate, immediate);

	sprintf(mips_instruction, "%s %s, %s", opcode, rt, immediate);
}

//Function to convert binary into general I format instruction
void binary_gen_I_format_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char opcode[10] = "", rs[4] = "", rt[4] = "", immediate[10] = "";
    char tmp_opcode[7] = "", tmp_rs[6] = "", tmp_rt[6] = "", tmp_immediate[17] = "";

	strncpy(tmp_opcode, input_binary_text, 6);
	strncpy(tmp_rs, input_binary_text + 6 * sizeof(char), 5);
	strncpy(tmp_rt, input_binary_text + 11 * sizeof(char), 5);
	strncpy(tmp_immediate, input_binary_text + 16 * sizeof(char), 16);

	binary_opcode(tmp_opcode, opcode, arr_ins);
	binary_register(tmp_rs, rs, arr_reg);
	binary_register(tmp_rt, rt, arr_reg);
	binary_to_dec(tmp_immediate, immediate);

	sprintf(mips_instruction, "%s %s, %s, %s", opcode, rt, rs, immediate);
}

//Function to convert binary into R format instruction with shifts
void binary_R_format_shift_to_mips(char *input_binary_text, char *mips_instruction, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char opcode[10] = "", rs[4] = "", rt[4] = "", offset[10] = "";
    char tmp_opcode[7] = "", tmp_rs[6] = "", tmp_rt[6] = "", tmp_offset[17] = "";

	strncpy(tmp_opcode, input_binary_text, 6);
	strncpy(tmp_rs, input_binary_text + 6 * sizeof(char), 5);
	strncpy(tmp_rt, input_binary_text + 11 * sizeof(char), 5);
	strncpy(tmp_offset, input_binary_text + 16 * sizeof(char), 16);

	//binary_opcode(tmp_opcode, opcode, arr_ins);
	binary_opcode_data_transfer(tmp_opcode, opcode, arr_ins);
	binary_register(tmp_rs, rs, arr_reg);
	binary_register(tmp_rt, rt, arr_reg);
	binary_to_dec(tmp_offset, offset);

	sprintf(mips_instruction, "%s %s, %s(%s)", opcode, rt, offset, rs);
}

//Function to convert machine code into MIPS instruction and output into file
void binary_to_mips_conversion(char *input_binary_text, FILE* output_file_ptr, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char mips_instruction[40] = "";
    if(strncmp(input_binary_text, "000000", 6) == 0)
    {
        if(strncmp(input_binary_text + 21*sizeof(char), "00000", 5) == 0)
        {
            if(strncmp(input_binary_text + 11*sizeof(char), "00000", 5) == 0 && strncmp(input_binary_text + 16*sizeof(char), "00000", 5) == 0)
            {
                // return for jr
                bin_to_mips_jr(input_binary_text, mips_instruction, arr_reg);
            }
            else
            {
                // return for add and nor or sub slt sltu
                binary_gen_R_format_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
            }
        }
        else
        {
            // return for sll srl
            binary_sll_srl_to_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
        }
    }
    else if(strncmp(input_binary_text, "000010", 6) == 0 || strncmp(input_binary_text, "000011", 6) == 0)
    {
        // return for j jal
        binary_j_jal_to_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
    }
    else if(strncmp(input_binary_text, "000100", 6) == 0 || strncmp(input_binary_text, "000101", 6) == 0)
    {
        // return for beq bne
		binary_beq_bne_to_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
    }
    else if(strncmp(input_binary_text, "001111", 6) == 0)
    {
        // return for lui
		binary_lui_to_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
    }
    else if(strncmp(input_binary_text, "001000", 6) == 0 || strncmp(input_binary_text, "001100", 6) == 0 || strncmp(input_binary_text, "001101", 6) == 0 || strncmp(input_binary_text, "001010", 6) == 0 || strncmp(input_binary_text, "001011", 6) == 0)
    {
        // return for addi andi ori slti sltiu 
		binary_gen_I_format_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
    }
    else
    {
        // return for lb lbu lh lhu lw sb sh sw ll sc
		binary_R_format_shift_to_mips(input_binary_text, mips_instruction, arr_ins, arr_reg);
    }
    printf("%s\n", mips_instruction);
	fprintf(output_file_ptr, "%s\n", mips_instruction);
}

int main()
{
	//Array of structs for out instruction and registers
	instruction_mips arr_instruction[30];
	register_mips arr_register[33];
	struct_ini_instruction(arr_instruction, arr_register);

	//File Pointers
    FILE *input_file_ptr;
	FILE *MIPS_output_file_ptr;

	//name of input file
	char input_file_name[FILE_NAME_SIZE];
	printf("Enter the name of file to be converted from binary to MIPS: ");
	fgets(input_file_name, FILE_NAME_SIZE, stdin);
	string_corrector(input_file_name);
    input_file_ptr = fopen(input_file_name, "r");
    if(input_file_ptr == NULL)
    {
        return EXIT_FAILURE;
    }

	//Initializing the input command as \0
    char input_command[STRING_SIZE] = "";

	//Output file 
    char output_file_name[FILE_NAME_SIZE] = "";
    output_file_name_creator_bin_mips(input_file_name, output_file_name);
    MIPS_output_file_ptr = fopen(output_file_name, "w");
    char input_binary_text[33] = "";

	//Getting input line by line
    while(fgets(input_command, STRING_SIZE, input_file_ptr) != NULL)
    {
        strncpy(input_binary_text, input_command, 32);

		//Converting binary to MIPS
		binary_to_mips_conversion(input_binary_text, MIPS_output_file_ptr, arr_instruction, arr_register);
    }

	//Closing file pointers
    fclose(MIPS_output_file_ptr);
    fclose(input_file_ptr);

    return EXIT_SUCCESS;
}