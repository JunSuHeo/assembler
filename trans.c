#include "myas.h"

extern int is_valid(char *op, char *args);
extern int check_reg(char *str, int idx);
extern int check_symbol(char *str);

int instr_trans(char *op, char *args, char* mcode)
{
	char tmp[256];
	char *src;
	char *dest;

	// check syntax 
	if(!is_valid(op, args)){
		printf("Error: %s %s is not valid\n", op, args);
		strcpy(mcode, "error");
		return 0;
	}
	

	strcpy(mcode, "AB CD EF");

	/********************************/
	strcpy(tmp, args);
	src = strtok(tmp, ",");
	dest = strtok(NULL, "\n");
	//1. reg to reg
	if(check_reg(src, 0) != FALSE && check_reg(dest, 0) != FALSE)
		strcpy(mcode, "89");

	//4. mem to reg(eax)
	else if(check_symbol(src) == MEM && check_reg(dest, 0) == EAX)
		strcpy(mcode, "a1");

	//2. mem to reg
	else if(check_symbol(src) == MEM && check_reg(dest, 0) != FALSE)
		strcpy(mcode, "8b");

	//3. mem to reg
	else if(check_symbol(src) == DISP && check_reg(dest, 0) != FALSE)
		strcpy(mcode, "8b");
	//5. reg(eax) to mem
	else if(check_reg(src, 0) == EAX && check_symbol(dest) == MEM)
		strcpy(mcode, "a3");

	//6. immediate to reg
	else if(check_symbol(src) == IMM && check_reg(dest, 0) != FALSE){
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
    /*  							*/
	/*    generate machine code     */
    /*  							*/
	/********************************/
	
	return 1;	
}
