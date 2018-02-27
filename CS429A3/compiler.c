//Kevin Nguyen, kdn433

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern int64_t compute(int64_t x, int64_t y, int64_t z);

int main (int argc, char* argv[]) {
	char *plus = "+", *minus = "-", *mult = "*", *divide = "/";
	int i, operandCounter = 0, operationCounter = 0, isDigit, sum = 0, sameOps = 1;
	

	//Must have enough arguments atleast 3 arguments; 2 operands and 1 operator
	if (argc <= 3) {
		fprintf(stderr, "Error: Not enough arguments!!\n");
		exit(1);
	}
	else {
		//Iterate through each element and check for error, structure, and syntax of expression
		i = 1;
		while (i<argc) {
			if ((strcmp(argv[i], plus) == 0) || (strcmp(argv[i], minus) == 0) || (strcmp(argv[i], mult) == 0) || (strcmp(argv[i], divide) == 0)) {
				//checks if operations has enough operands to work with
				if (operandCounter < 2) {
					fprintf(stderr, "Error: Not enough operands for a math operation was found!'\n'");
					exit(1);
				}
				else {
					operationCounter++;			
				}

				if ((strcmp(argv[i], plus) != 0) && (sscanf (argv[i], "%i", &isDigit) == 0)) {
					sameOps = 0;	
				} 
			}
			else if ((sscanf (argv[i], "%i", &isDigit) != 0) || (strcmp(argv[i], "x") == 0) || (strcmp(argv[i], "y") == 0) || (strcmp(argv[i], "z") == 0)) {
				operandCounter++;
				if (sscanf (argv[i], "%i", &isDigit) != 0) {
					sum = sum + isDigit;
				}
			}
			else {
				//Not a number or value
				fprintf(stderr, "Error: Not an integer value or math operations found!!\n");
				exit(1);
			}

			i++;
			if (i >= argc) {
				//Error if number of operators is one less than number of operands, balance 
				if (((operandCounter - operationCounter) != 1) && (operandCounter != 0 && operationCounter != 0)) {
					fprintf(stderr, "Error: Number of math operations must be one less than number of operands!'\n'");
					exit(1);
				}
				else if (operationCounter == 0 || operandCounter == 0) {
					fprintf(stderr, "Error: Must have math operation and operand available!'\n'");
					exit(1);
				}
			}
		}
		operandCounter = 0;
		printf("\t.globl compute\n");
		printf("compute:\n");
		//Iterate through each argument and apply computing, if all same operations then optimize
		if (sameOps == 1) {
			for (i=1; i<argc; i++) {
				if ((strcmp(argv[i], "x") == 0)) {
					fprintf(stdout, "\tpushq %%rdi\n"); operandCounter++;
				}
				else if ((strcmp(argv[i], "y") == 0)) {
					fprintf(stdout, "\tpushq %%rsi\n"); operandCounter++;
				} 
				else if ((strcmp(argv[i], "z") == 0)) {
  					fprintf(stdout, "\tpushq %%rdx\n"); operandCounter++;
				}
			}	
			if (operandCounter > 0) {
				fprintf(stdout, "\tpushq $%d\n", sum);
				for (i=0; i<operandCounter; i++) {
					fprintf(stdout, "\tpopq %%r10\n\tpopq %%r11\n");
					fprintf(stdout, "\taddq %%r10, %%r11\n");
					fprintf(stdout, "\tpushq %%r11\n");
				}
				printf("\tpopq %%rax\n");
			}
			else {
				fprintf(stdout, "\tmovq $%d, %%rax\n", sum);
			}
			printf("\tretq\n");
		}
		else { //not optimized
			for (i=1; i<argc; i++) {	
				//If statements print the assembly code based on inputs					
				if (strcmp(argv[i], plus) == 0) {
					fprintf(stdout, "\tpopq %%r10\n\tpopq %%r11\n");
					fprintf(stdout, "\taddq %%r10, %%r11\n");
					fprintf(stdout, "\tpushq %%r11\n");
				}
				else if (strcmp(argv[i], minus) == 0) {
					fprintf(stdout, "\tpopq %%r10\n\tpopq %%r11\n");
					fprintf(stdout, "\tsubq %%r10, %%r11\n");
					fprintf(stdout, "\tpushq %%r11\n");
				}
				else if (strcmp(argv[i], mult) == 0) {
					fprintf(stdout, "\tpopq %%r10\n\tpopq %%r11\n");
					fprintf(stdout, "\timulq %%r10, %%r11\n");
					fprintf(stdout, "\tpushq %%r11\n");
				}
				else if (sscanf (argv[i], "%i", &isDigit)) {
					fprintf(stdout, "\tpushq $%d\n", isDigit);
				}
				else if ((strcmp(argv[i], "x") == 0)) {
					fprintf(stdout, "\tpushq %%rdi\n");
				}
				else if ((strcmp(argv[i], "y") == 0)) {
					fprintf(stdout, "\tpushq %%rsi\n");
				} 
				else if ((strcmp(argv[i], "z") == 0)) {
  					fprintf(stdout, "\tpushq %%rdx\n");
				}
				else {
					fprintf(stderr, "Error: Not an integer value or math operation found!\n");
					exit(1);
				}
			}
			printf("\tpopq %%rax\n");
			printf("\tretq\n");
		}
	}
	return 0;
}