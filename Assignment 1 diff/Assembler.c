/*	Tanmay Garg Computer Architecture Assignment 1
*
*	To compile:
*	gcc -o Assembler Assembler.c
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#define FILE_NAME_SIZE 30
#define MAX_NUM_ARGS 4
#define ARG_SIZE 10
#define STRING_SIZE 40
#define MIPS_ARCH 32
#define INS_NUM 30
#define REG_NUM 33

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

//Function corrects the string after taking input from fgets function to remove \n
void string_corrector(char *s)
{
	int len = strlen(s);
	if (s[len - 1] == '\n')
	{
		s[len - 1] = '\0';
	}
}

//Function which separates the entire input string into separate 2D array
void command_argument_separator(char *input_command_line, char commands_args[MAX_NUM_ARGS][ARG_SIZE])
{
	int i = 0, j = 0;
	int num_args = 0;
	int strncpy_num = 0;
	while (input_command_line[i] != '\0')
	{
		while (input_command_line[j] != ' ')
		{
			if (input_command_line[j] == '\0')
			{
				break;
			}
			j++;
		}

		strncpy(commands_args[num_args], input_command_line + strncpy_num * sizeof(char), j - strncpy_num);
		strncpy_num = j + 1;
		j++;
		num_args++;
		i++;
		if (input_command_line[j] == '\0')
		{
			break;
		}
	}
}

//Function to remove ',' from input commands
void command_arg_string_corrector(char commands_args[MAX_NUM_ARGS][ARG_SIZE])
{
	for (int i = 0; i < MAX_NUM_ARGS; i++)
	{
		if (commands_args[i][0] == '\0')
		{
			break;
		}
		for (int j = 0; j < ARG_SIZE; j++)
		{
			if (commands_args[i][j] == ',')
			{
				commands_args[i][j] = '\0';
				break;
			}
		}
	}
}

//Function to convert mips instruction into its binary form
void opcode_to_binary(char *opfunction, char *return_str, instruction_mips *arr_instruction)
{
	for(int i = 0; i < INS_NUM; i++)
	{
		if(strcmp(opfunction, arr_instruction[i].instruction) == 0)
		{
			strcpy(return_str, arr_instruction[i].opcode);
			return;
		}
	}
}

//Function to convert mips register into its binary form
void register_to_binary(char *register_input, char *return_str, register_mips *arr_register)
{
	for(int i = 0; i < REG_NUM; i++)
	{
		if(strcmp(register_input, arr_register[i].register_name) == 0)
		{
			strcpy(return_str, arr_register[i].binary);
			return;
		}
	}
}

//Function to convert decimal number into required number of bits in binary form
void dec_to_bin_num(char *arr, char *return_str, int num)
{
	int tmp = atoi(arr);
	for (int i = num; i >= 0; i--)
	{
		if (tmp % 2 == 1)
		{
			return_str[i] = '1';
		}
		else
		{
			return_str[i] = '0';
		}
		tmp = tmp / 2;
	}
}

//Function to convert General R format into its machine code
void R_format_to_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	// add and nor or sub slt sltu
	char rs[6] = "", rd[6] = "", rt[6] = "", funct[7] = "";
	opcode_to_binary(commands_args[0], funct, arr_ins);
	register_to_binary(commands_args[2], rs, arr_reg);
	register_to_binary(commands_args[1], rd, arr_reg);
	register_to_binary(commands_args[3], rt, arr_reg);
	sprintf(return_str, "%s%s%s%s%s%s", "000000", rs, rt, rd, "00000", funct);
}

//Function to convert General I format into its machine code
void I_format_to_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	// addi andi ori slti sltiu
	char opcode[7] = "", rs[6] = "", rt[6] = "", immediate[17] = "";
	opcode_to_binary(commands_args[0], opcode, arr_ins);
	register_to_binary(commands_args[2], rs, arr_reg);
	register_to_binary(commands_args[1], rt, arr_reg);
	dec_to_bin_num(commands_args[3], immediate, 15);
	sprintf(return_str, "%s%s%s%s", opcode, rs, rt, immediate);
}

//Function to convert Shift operations R format into its machine code
void R_format_exception_shift_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	//sll srl
	char rd[6] = "", rt[6] = "", shamt[6] = "", funct[7] = "";
	opcode_to_binary(commands_args[0], funct, arr_ins);
	register_to_binary(commands_args[1], rd, arr_reg);
	register_to_binary(commands_args[2], rt, arr_reg);
	dec_to_bin_num(commands_args[3], shamt, 4);
	sprintf(return_str, "%s%s%s%s%s%s", "000000", "00000", rt, rd, shamt, funct);
}

//Function to convert BEQ BNE into its machine code
void I_format_exception_beq_bne_to_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	//beq bne
	char opcode[7] = "", rs[6] = "", rt[6] = "", immediate[17] = "";
	opcode_to_binary(commands_args[0], opcode, arr_ins);
	register_to_binary(commands_args[1], rs, arr_reg);
	register_to_binary(commands_args[2], rt, arr_reg);
	dec_to_bin_num(commands_args[3], immediate, 15);
	sprintf(return_str, "%s%s%s%s", opcode, rs, rt, immediate);
	/*Function can be changed such that offset can be changed independently */
}

//Function to convert General J format into its machine code
void J_format_to_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	//j jal
	char opcode[7] = "", immediate[27] = "";
	opcode_to_binary(commands_args[0], opcode, arr_ins);
	dec_to_bin_num(commands_args[1], immediate, 25);
	sprintf(return_str, "%s%s", opcode, immediate);
}

//Function to convert JR into its machine code
void R_format_exception_jr_to_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	//jr
	char rs[6] = "", funct[7] = "";
	opcode_to_binary(commands_args[0], funct, arr_ins);
	register_to_binary(commands_args[1], rs, arr_reg);
	sprintf(return_str, "%s%s%s%s%s%s", "000000", rs, "00000", "00000", "00000", funct);
}

//Function to convert data transfer operations I format into its machine code
void I_format_exception_data_transfer_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	//lb lbu lh lhu lw sb sh sw ll sc
	char opcode[7] = "", rs[6] = "", rt[6] = "", immediate[17] = "";
	opcode_to_binary(commands_args[0], opcode, arr_ins);
	register_to_binary(commands_args[1], rt, arr_reg);
	char binary_num[ARG_SIZE - 4] = "";
	int i = 0;
	while (commands_args[2][i] != '(')
	{
		binary_num[i] = commands_args[2][i];
		i++;
	}
	strncpy(rs, commands_args[2] + (i + 1) * sizeof(char), 3);
	register_to_binary(rs, rs, arr_reg);
	dec_to_bin_num(binary_num, immediate, 15);
	sprintf(return_str, "%s%s%s%s", opcode, rs, rt, immediate);
}

//Function to convert LUI into its machine code
void I_format_exception_lui_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], char *return_str, instruction_mips *arr_ins, register_mips *arr_reg)
{
	// lui
	char opcode[7] = "", rt[6] = "", immediate[17] = "";
	opcode_to_binary(commands_args[0], opcode, arr_ins);
	register_to_binary(commands_args[1], rt, arr_reg);
	dec_to_bin_num(commands_args[2], immediate, 15);
	sprintf(return_str, "%s%s%s%s", opcode, "00000", rt, immediate);
}

//Enum for setting the number of arguments for printing in output file
enum print_setup {SIX, FOUR, FIVE};

//Function to print into output file in required format
void print_output(char *machine_code, char commands_args[MAX_NUM_ARGS][ARG_SIZE], FILE *output_ptr, enum print_setup type_num)
{
	char hexadecimal_num[9] = "";
	char hexadecimal_num_tmp[9] = "";
	unsigned long int num = strtoul(machine_code, NULL, 2);
	sprintf(hexadecimal_num_tmp, "%lx", num);
	for (int i = 0; i < 8 - strlen(hexadecimal_num_tmp); i++)
	{
		hexadecimal_num[i] = '0';
	}
	strcat(hexadecimal_num, hexadecimal_num_tmp);

	if(type_num == SIX)
	{
		printf("%s (%s, %s %s, %s, %s)\n", machine_code, hexadecimal_num, commands_args[0], commands_args[1], commands_args[2], commands_args[3]);
		fprintf(output_ptr, "%s (%s, %s %s, %s, %s)\n", machine_code, hexadecimal_num, commands_args[0], commands_args[1], commands_args[2], commands_args[3]);
	}
	if(type_num == FOUR)
	{
		printf("%s (%s, %s %s)\n", machine_code, hexadecimal_num, commands_args[0], commands_args[1], commands_args[2], commands_args[3]);
		fprintf(output_ptr, "%s (%s, %s %s)\n", machine_code, hexadecimal_num, commands_args[0], commands_args[1]);
	}
	if(type_num == FIVE)
	{
		printf("%s (%s, %s %s, %s)\n", machine_code, hexadecimal_num, commands_args[0], commands_args[1], commands_args[2], commands_args[3]);
		fprintf(output_ptr, "%s (%s, %s %s, %s)\n", machine_code, hexadecimal_num, commands_args[0], commands_args[1], commands_args[2]);
	}
}

//Function to convert mips instruction code into binary and printing into output file
void convert_mips_binary(char commands_args[MAX_NUM_ARGS][ARG_SIZE], FILE *output_ptr, instruction_mips *arr_ins, register_mips *arr_reg)
{
	char machine_code[33] = "";
	char hexadecimal_num[9] = "";
	char hexadecimal_num_tmp[9];
	if (strcmp(commands_args[0], "add") == 0 || strcmp(commands_args[0], "and") == 0 || strcmp(commands_args[0], "nor") == 0 || strcmp(commands_args[0], "or") == 0 || strcmp(commands_args[0], "sub") == 0 || strcmp(commands_args[0], "slt") == 0 || strcmp(commands_args[0], "sltu") == 0)
	{
		R_format_to_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, SIX);
	}
	else if (strcmp(commands_args[0], "addi") == 0 || strcmp(commands_args[0], "andi") == 0 || strcmp(commands_args[0], "ori") == 0 || strcmp(commands_args[0], "slti") == 0 || strcmp(commands_args[0], "sltiu") == 0)
	{
		I_format_to_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, SIX);
	}
	else if (strcmp(commands_args[0], "sll") == 0 || strcmp(commands_args[0], "srl") == 0)
	{
		R_format_exception_shift_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, SIX);
	}
	else if (strcmp(commands_args[0], "beq") == 0 || strcmp(commands_args[0], "bne") == 0)
	{
		I_format_exception_beq_bne_to_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, SIX);
	}
	else if (strcmp(commands_args[0], "j") == 0 || strcmp(commands_args[0], "jal") == 0)
	{
		J_format_to_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, FOUR);
	}
	else if (strcmp(commands_args[0], "jr") == 0)
	{
		R_format_exception_jr_to_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, FOUR);
	}

	else if (strcmp(commands_args[0], "lb") == 0 || strcmp(commands_args[0], "lbu") == 0 || strcmp(commands_args[0], "lh") == 0 || strcmp(commands_args[0], "lhu") == 0 || strcmp(commands_args[0], "sb") == 0 || strcmp(commands_args[0], "sh") == 0 || strcmp(commands_args[0], "sw") == 0 || strcmp(commands_args[0], "ll") == 0 || strcmp(commands_args[0], "sc") == 0 || strcmp(commands_args[0], "lw") == 0)
	{
		I_format_exception_data_transfer_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, FIVE);
	}
	else if (strcmp(commands_args[0], "lui") == 0)
	{
		I_format_exception_lui_binary(commands_args, machine_code, arr_ins, arr_reg);
		print_output(machine_code, commands_args, output_ptr, FIVE);
	}
	else
	{
		printf("invalid command\n");
	}
}

//Function to create name of output file from given input file
void output_file_name_creator(char *input_file_name, char *return_str)
{
	int i = 0;
	while (input_file_name[i] != '.')
	{
		return_str[i] = input_file_name[i];
		i++;
	}
	strcat(return_str, "bin.txt");
}

int main()
{
	//Array of structs for out instruction and registers
	instruction_mips arr_instruction[30];
	register_mips arr_register[33];
	struct_ini_instruction(arr_instruction, arr_register);

	//File pointers 
	FILE *input_file_ptr;
	FILE *binary_output_file_ptr;

	//name of input file
	char input_file_name[FILE_NAME_SIZE];
	printf("Enter the name of file to be converted from MIPS to binary: ");
	fgets(input_file_name, FILE_NAME_SIZE, stdin);
	string_corrector(input_file_name);

	//file path in windows
	char input_file_path[FILE_NAME_SIZE] = "sample_data/";

	strcat(input_file_path, input_file_name);
	input_file_ptr = fopen(input_file_path, "r");
	if (input_file_ptr == NULL)
	{
		return EXIT_FAILURE;
	}

	//Initializing the input command and command arguments as \0
	char input_command[STRING_SIZE] = "";
	char commands_args[MAX_NUM_ARGS][ARG_SIZE];
	for (int i = 0; i < MAX_NUM_ARGS; i++)
	{
		for (int j = 0; j < ARG_SIZE; j++)
		{
			commands_args[i][j] = '\0';
		}
	}

	//name of output file
	char output_file_name[FILE_NAME_SIZE];
	output_file_name_creator(input_file_name, output_file_name);
	binary_output_file_ptr = fopen(output_file_name, "w");

	//Getting input from file line by line
	while (fgets(input_command, STRING_SIZE, input_file_ptr) != NULL)
	{	
		//Converting the input string into command arguments
		string_corrector(input_command);
		command_argument_separator(input_command, commands_args);
		command_arg_string_corrector(commands_args);

		//Convert MIPS to Binary
		convert_mips_binary(commands_args, binary_output_file_ptr, arr_instruction, arr_register);

		//Reinitialise command arguments
		for (int i = 0; i < MAX_NUM_ARGS; i++)
		{
			for (int j = 0; j < ARG_SIZE; j++)
			{
				commands_args[i][j] = '\0';
			}
		}
	}

	//Close File pointers
	fclose(binary_output_file_ptr);
	fclose(input_file_ptr);

	return EXIT_SUCCESS;
}