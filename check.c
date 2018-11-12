#include "myas.h"

int check_hexa(char *str, int start, int finish)	//check this string is hexadecimal
							//start is the first index to check string
							//finish is the end index to check string
{
	while(start <= finish){		
		if(str[start] == '0' || str[start] == '1' || str[start] == '2' || str[start] == '3' ||
		   str[start] == '4' || str[start] == '5' || str[start] == '6' || str[start] == '7' ||
		   str[start] == '8' || str[start] == '9' || str[start] == 'a' || str[start] == 'b' ||
		   str[start] == 'c' || str[start] == 'd' || str[start] == 'e' || str[start] == 'f'  )
			start++;
		else break;
	}

	if(start != finish + 1)	
		return FALSE;

	else return 1;
}

int check_reg(char *str, int idx)	//check this string type of register
{
	if(str[idx] == '%' && str[idx + 1] == 'e'){
		if(str[idx + 3] == 'x'){
			if(str[idx + 2] == 'a')	//%eax
				return EAX;
			else if(str[idx + 2] =='c')	//%ecx
				return ECX;
			else if(str[idx + 2] == 'd')	//%edx
				return EDX;
			else if(str[idx + 2] == 'b')	//%ebx
				return EBX;
			else return FALSE;
		}
		else if(str[idx + 3] == 'p'){	
			if(str[idx + 2] == 's')	//%esp
				return ESP;
			else if(str[idx + 2] =='b')	//%ebp
				return EBP;
			else return FALSE;
		}
		else if(str[idx + 3] == 'i'){	
			if(str[idx + 2] == 's')	//%esi
				return ESI;
			else if(str[idx + 2] == 'd')	//%edi
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

	if(str[0] == '$' && str[1] == '0' && str[2] == 'x'){	//$0x~~~~~ = Immediate
		if(check_hexa(str, 3, last) != FALSE)
			return IMM;
		else
			return FALSE;
	}
	
	else if(str[0] == '('&& check_reg(str, 1) != FALSE && str[5] == ')')	//(%eax), (%ebx) ... = Memory
		return MEM;
	
	else if(str[0] == '0' && str[1] == 'x'&& check_hexa(str, 2, last-6) != FALSE	//0x~~~(%edx) = Displacement
		 && str[last - 5] == '(' && str[last - 4] == '%' && str[last - 3] == 'e' && str[last] == ')')
		return DISP;

	else if(str[0] == '0' && str[1] == 'x' && check_hexa(str, 2, last))	//0x~~~ = Memory
		return MEM;

	else if(str[0] == '-' && str[1] == '0' && str[2] == 'x'&& check_hexa(str, 3, last - 6) != FALSE	
		 && str[last -5] == '(' && check_reg(str, last - 4) != FALSE && str[last] == ')')	//-0x~~~~~(%ebp) = Displacement
		return DISP;
	
	else if(check_reg(str, 0) != FALSE)	//%eax, %ebx ... = Register
		return REG;
	
	else return FALSE;
}


int is_valid(char *op, char *args)
{
	char *src;
	char *dest;
	char tmp[256];

	strcpy(tmp, args);

	if(strcmp(op, "mov") != 0)	//op string not equal "mov" is FALSE
		return 0;

	src = strtok(tmp, ",");	
	dest = strtok(NULL, "\n");
	
	if(check_symbol(dest) == IMM)	//invalid case1 : destination is Immediate
		return 0;
	
	else if(check_symbol(src) == IMM && check_symbol(dest) == IMM)	//invalid case2 : source and destination is Immediate
		return 0;

	else if(check_symbol(src) == MEM && check_symbol(dest) == MEM)	//invalid case3 : source and destination is Memory
		return 0;

		
	else if(check_symbol(src) == FALSE || check_symbol(dest) == FALSE)	//invalid case4 : source or destination is not symbol
		return 0;
	
	
	return 1;
}


