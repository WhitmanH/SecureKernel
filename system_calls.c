#include "system.h"

/*@brief Takes a string and returns the coordinating "opcode" value.
* @param call String of system call
* @return int Of corresponding call's opcode.
*/

struct systemCalls{
	int id;
	char call[64];
};

struct systemCalls SYSTEM_CALLS[NUMBER_SYS_CALLS] = {{1, "-help"}, {2, "clear"}, {3, "fuck"}};

int commandLookup(char* call){
	int i;
	//int = strlen(sCall)
	for(i = 0; i < NUMBER_SYS_CALLS; ++i){
		if(!strcmp(call, SYSTEM_CALLS[i].call)){
			return SYSTEM_CALLS[i].id;
		}
	} 
}


void clear(void){
	unsigned int i = 0, j = 0;
	/*
	* Loop clears the screen. There exists 25 lines of 80 columns, and each element
	* takes 2 bytes.
	*/
	while(j < 80 * 25 * 2){
		//Print blank character
		vram[j] = ' ';
		//Highlight next character a light gray
		vram[j+1]= 0x07;
		j = j + 2;
	}
	current_loc = 0;
}

void help(void){
	newlineX2();
	message("Currently Available System Calls:");
	newlineX1();
	int i;
	for(i = 0; i < NUMBER_SYS_CALLS; ++i){
		if(strcmp("\0", SYSTEM_CALLS[i].call)){
			message(SYSTEM_CALLS[i].call); message(", ");
		}
		
	}
	newlineX1();
}