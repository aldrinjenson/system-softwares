#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display()
{

	char str;
	FILE *input, *intermediate, *symTbl;

	printf("\nThe contents of Input Table :\n\n");
	input = fopen("input.txt", "r");
	str = fgetc(input);
	while (str != EOF)
	{
		printf("%c", str);
		str = fgetc(input);
	}
	fclose(input);

	printf("\n\nThe contents of Intermediate Table :\n\n");
	intermediate = fopen("intermediate.txt", "r");
	str = fgetc(intermediate);
	while (str != EOF)
	{
		printf("%c", str);
		str = fgetc(intermediate);
	}
	fclose(intermediate);

	printf("\n\nThe contents of Symbol Table :\n\n");
	symTbl = fopen("symtab.txt", "r");
	str = fgetc(symTbl);
	while (str != EOF)
	{
		printf("%c", str);
		str = fgetc(symTbl);
	}
	fclose(symTbl);
}

void main()
{
	FILE *input = fopen("input.txt", "r");
	FILE *opTable = fopen("optab.txt", "r");
	FILE *output = fopen("intermediate.txt", "w");
	FILE *symTbl = fopen("symtab.txt", "w");

	char label[10], opcode[10], operand[10], code[10], mnemonic[10];

	int lineCount = 0;
	int locctr, startAddress = 0;
	fscanf(input, "%s %s %s", label, opcode, operand);
	if (strcmp(opcode, "START") == 0)
	{
		locctr = atoi(operand); // converting string to int
		startAddress = atoi(operand);
		fprintf(output, "      %s\t%s\t%s\n", label, opcode, operand);
		fscanf(input, "%s %s %s", label, opcode, operand);
	}
	else
		locctr = 0;
	while (strcmp(opcode, "END") != 0)
	{
		// fprintf(output, "%d\t", locctr);

		fprintf(output, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
		if (strcmp(label, "**") != 0)
		{
			// add to symTable if it's defining a symbol
			fprintf(symTbl, "%s\t%d\n", label, locctr);
		}

		fscanf(opTable, "%s %s", code, mnemonic);
		while (strcmp(code, "END") != 0)
		{
			if (strcmp(code, opcode) == 0)
			{
				// like searching a hashmap, loop till te code matches the opcode from opTable
				locctr += 3;
				break;
			}
			fscanf(opTable, "%s %s", code, mnemonic);
		}

		if (strcmp(opcode, "WORD") == 0)
			locctr += 3;
		else if (strcmp(opcode, "RESW") == 0)
			locctr += (3 * (atoi(operand)));
		else if (strcmp(opcode, "RESB") == 0)
			locctr += (atoi(operand));
		else if (strcmp(opcode, "BYTE") == 0)
			locctr += strlen(operand) - 2;

		// fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
		fscanf(input, "%s\t%s\t%s", label, opcode, operand);
	}
	fprintf(output, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
	int length = locctr - startAddress;
	printf("Assembly code converted to intermediate file\n");
	printf("The length of the code : %d\n", length);

	fclose(input);
	fclose(output);
	fclose(opTable);
	fclose(symTbl);
	display();
}