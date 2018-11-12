#include "myas.h"

enum symbol{FALSE, TRUE, REG, MEM, IMM, DISP};

int check_symbol(char *str)
{
	


}

int instr_trans(char *op, char *args, char* mcode)
{
	// check syntax 
	if(!is_valid(op, args)){
		printf("Error: %s %s is not valid\n", op, args);
		return 0;
	}


	strcpy(mcode, "AB CD EF");

	/********************************/
    /*  							*/
	/*    generate machine code     */
    /*  							*/
	/********************************/
	
	return 1;	
}
