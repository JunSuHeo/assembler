#include "myas.h"

enum symbol{IMM, MEM, REG};
enum reg{EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI};
#define FALSE -1

int check_hexa(char *str, int start, int finish)
{
	while(idx < strlen(str)){
		if(str[idx] == '0' || str[idx] == '1' || str[idx] == '2' || str[idx] == '3' ||
		   str[idx] == '4' || str[idx] == '5' || str[idx] == '6' || str[idx] == '7' ||
		   str[idx] == '8' || str[idx] == '9' || str[idx] == 'a' || str[idx] == 'b' ||
		   str[idx] == 'c' || str[idx] == 'd' || str[idx] == 'e' || str[idx] == 'f'  )
			start++;
		else break;
	}

	if(start != finish)
		return FALSE;

	else return 1;
}

int check_reg(char *str, int idx)
{
	if(str[idx] == '%' && str[idx + 1] == 'e'){
		if(str[idx + 3] == 'x'){
			if(str[idx + 2] == 'a')
				return EAX;
			else if(str[idx + 2] =='c')
				return ECX;
			else if(str[idx + 2] == 'd')
				return EDX;
			else if(str[idx + 2] == 'b')
				return EBX;
			else return FALSE;
		}
		else if(str[idx + 3] == 'p'){
			if(str[idx + 2] == 's')
				return ESP;
			else if(str[idx + 2] =='b'
				return EBP;
			else return FALSE;
		}
		else if(str[idx + 3] == 'i'){
			if(str[idx + 2] == 's')
				return ESI;
			else if(str[idx + 2] == 'd')
				return EDI;
			else return FALSE;
		}
		else return FALSE;
	}
	else return FALSE;
}

int check_symbol(char *str)
{
	int last = strlen(str) - 1;

	if(str[0] == '$'){	//Immediate = $~~~~~~
		if(check_hexa(str, 1, last) != FALSE)
			return IMM;
		else
			return FALSE;
	}
	
	else if(str[0] == '('&& check_reg(str, 1) != FALSE && str[5] == ')')	//(%eax), (%ebx) ... = Memory
		return MEM;
	
	else if(str[0] == '0' && str[1] == 'x'&& check_hexa(str, 2, last-6) != FALSE	//0x~~~(%edx) = Memory
		 && str[last - 5] == '(' && str[last - 4] == '%' && str[last - 3] == 'e' && str[last] == ')')
		return MEM;

	else if(str[0] == '0' && str[1] == 'x' && check_hexa(str, 2))	//0x~~~ = Memory
		return MEM;

	else if(str[0] == '-' && str[1] == '0' && str[2] == 'x' && str[last -5] == '(' &&	//-0x~~(%eax) = Memory
		check_reg(str, last - 4) != FALSE && str[last] == ')')
		return MEM;
	
	else if(check_reg(str, 0) != FALSE)	//%eax, %ebx ... = Register
		return REG;
	
	else return FALSE;
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

		
	else if(check_symbol(src) == FALSE || check_symbol(dest) == FALSE)
		return 0;
	/*         syntax check         */
    /*  							*/
	/********************************/
	
	return 1;
}


