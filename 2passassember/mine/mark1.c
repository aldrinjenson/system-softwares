#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
  FILE *input = fopen("input.txt", "r");
  FILE *intermediate = fopen("intermediateFile.txt", "w");
  FILE *opTab = fopen("optab.txt", "r");
  FILE *symTab = fopen("symtab.txt", "w");
  fprintf(intermediate, "yo");
  char label[10],
      opcode[10], operand[10];
  char mnemonic[10], code[10];

  int locctr = 0, startAddres = 0;
  fscanf(input, "%s %s %s", label, opcode, operand);
  if (strcmp(opcode, "START") == 0)
  {
    locctr = atoi(operand);
    startAddres = atoi(operand);
    fprintf(intermediate, "\t%s\t%s\t%s\n", label, opcode, operand);
    fscanf(input, "%s %s %s", label, opcode, operand);
  }
  else
  {
    startAddres = 0;
    locctr = 0;
  }

  while (strcmp(opcode, "END") != 0)
  {
    fprintf(intermediate, "%d\t%s\t%s\t%s", locctr, label, opcode, operand);
    if (strcmp(label, "**") != 0)
    {
      fprintf(symTab, "%s\t%d\n", label, locctr);
    }

    fscanf(opTab, "%s %s", mnemonic, code);
    while (strcmp(mnemonic, "END") != 0)
    {
      if (strcmp(mnemonic, opcode) == 0)
      {
        locctr += 3;
        break;
      }
      fscanf(opTab, "%s %s", mnemonic, code);
    }

    if (strcmp(opcode, "WORD") == 0)
      locctr += 3;
    else if (strcmp(opcode, "RESW") == 0)
      locctr += 3 * atoi(operand);
    else if (strcmp(opcode, "RESB") == 0)
      locctr += atoi(operand);
    else if (strcmp(opcode, "BYTE") == 0)
      locctr += strlen(operand) - 2;
    fscanf(input, "%s %s %s", label, opcode, operand);
  }

  fprintf(intermediate, "%d\t%s\t%s\t%s", locctr, label, opcode, operand);
  int length = locctr - startAddres;
  printf("Code Length = %d", length);

  fclose(input);
  fclose(intermediate);
  fclose(opTab);
  fclose(symTab);
}