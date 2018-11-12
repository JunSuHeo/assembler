#include "myas.h"

enum symbol{FALSE, REG, IMM, MEM, DISP};

int check_symbol(char *str)
{
	int last = strlen(str) - 1;

	if(str[0] == '$')	//Immediate = $~~~~~~
		return IMM;

	else if(str[0] == '(' && str[1] == '%' && str[2] == 'e' && str[5] == ')')	//(%eax), (%ebx) ... = Memory
		return MEM;

	else if(str[0] == '0' && str[1] == 'x')		//0x~~~~~ = Memory
		return MEM;

	else if(str[0] == '0' && str[1] == 'x' && str[last - 5] == '(' && str[last - 4] == '%'	//0x~~(%eax) = Memory
		 && str[last - 3] == 'e' && str[last] == ')')
		return MEM;

	else if(str[0] == '-' && str[1] == '0' && str[2] == 'x' && str[last -5] == '(' &&	//-0x~~(%eax) = Memory
		str[last - 4] == '%' && str[last - 3] == 'e' && str[last] == ')')
		return MEM;
	
}


int is_valid(char *op, char *args)
{
	//printf("if valid, return 1\n");
	//printf("otherwise, return 0\n");

	/********************************/
	char *src;
	char *dest;
	char tmp[256];

	strcpy(tmp, args);

	if(strcmp(op, "mov") != 0)	//op string not equal "mov" is FALSE
		return 0;

	src = strtok(tmp, ",");	
	dest = strtok(NULL, "\n");
	
	if(check_symbol(dest) == IMM)
		return 0;
	
	else if(check_symbol(src) == IMM && check_symbol(dest) == IMM)
		return 0;

	else if(check_symbol(src) == MEM && check_symbol(dest) == MEM)
		return 0;

		
	/*         syntax check         */
    /*  							*/
	/********************************/
	
	return 1;
}


