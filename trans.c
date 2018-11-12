#include "myas.h"

extern int is_valid(char *op, char *args);
extern int check_reg(char *str, int idx);
extern int check_symbol(char *str);

int instr_trans(char *op, char *args, char* mcode)
{
	char tmp[256];	//eqaul args
	char *src;
	char *dest;

	// check syntax 
	if(!is_valid(op, args)){
		printf("Error: %s %s is not valid\n", op, args);
		strcpy(mcode, "error");
		return 0;
	}
	

	strcpy(mcode, "AB CD EF");

	strcpy(tmp, args);
	src = strtok(tmp, ",");		//seperate args
	dest = strtok(NULL, "\n");	//seperate args

	if(check_reg(src, 0) != FALSE && check_reg(dest, 0) != FALSE)	//1. reg to reg
		strcpy(mcode, "89");

	else if(check_symbol(src) == MEM && check_reg(dest, 0) == EAX)	//4. mem to reg(eax)
		strcpy(mcode, "a1");	
	
	else if(check_symbol(src) == MEM && check_reg(dest, 0) != FALSE) //2. mem to reg (addressing w.o/disp.)
		strcpy(mcode, "8b");
	
	else if(check_symbol(src) == DISP && check_reg(dest, 0) != FALSE) //3. mem to reg(addressing w/disp.)
		strcpy(mcode, "8b");
	
	else if(check_reg(src, 0) == EAX && check_symbol(dest) == MEM)	//5. reg(eax) to mem
		strcpy(mcode, "a3");

	else if(check_symbol(src) == IMM && check_reg(dest, 0) != FALSE){ //6. immediate to reg b8 + rd
									  //eax = 0, ecx = 1, edx = 2, ebx = 3 ...
		switch(check_reg(dest, 0)){
		case EAX :
			strcpy(mcode, "b8");
			break;
		case ECX :
			strcpy(mcode, "b9");
			break;
		case EDX :
			strcpy(mcode, "ba");
			break;
		case EBX :
			strcpy(mcode, "bb");
			break;
		case ESP :
			strcpy(mcode, "bc");
			break;
		case EBP :
			strcpy(mcode, "bd");
			break;
		case ESI :
			strcpy(mcode, "be");
			break;
		case EDI :
			strcpy(mcode, "bf");
			break;
		}
	}
	
	else
		strcpy(mcode, "error");	
	
	return 1;	
}
