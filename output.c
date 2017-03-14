#include "system.h"

extern char* vram;
extern unsigned int current_loc;
extern char userInput[128];

void newlineX2(void){
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void newlineX1(void){
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void decodeInstruction(void){
	int id = commandLookup(userInput);
	switch(id){
		case 0 :
			break;
		case 1 :
			help();
			break;
		case 2 : 
			clear();
			break;
		case 3 : 
			echo();
			break;		
		case 4 :
			ls();
			break;
		case 7 :
			mkdir();
			break;	
		case 8:
			rmdir();
			break;	
		case 9 :
			cd();
			break;
		case 11:
			cat();	
			break;
		case 12:
			rm();
			break;
		default :
			message(userInput); message(" is not a selected command. Type -help for more information.");
			newlineX1();	
	}
}

void newCommand(void){
	//decodeInstruction();
	//char* pwd = "Soteria@CAMEL:/$ ";
	newlineX1();
	decodeInstruction();
	//message(userInput);
	message(pwd);
}


/*@brief Takes a pointer to a character and will print the full message. No newlines are created.
* @param message pointer to first index of string to print.
* @return void.
*/
void message(char* message){
	unsigned int j = 0;
	//char* pwd = "Soteria@CAMEL:/$ ";
	//char* msg=strcat(pwd, message);
	/*
	* Writing the string to VRAM.
	*/
	while(message[j] != '\0'){
		/* Printing the sting */
		vram[current_loc] = message[j];
		/* Declaring font color, black bg, light grey fg */
		vram[current_loc+1] = 0x07;
		++j;
		current_loc = current_loc + 2;
	}
}
//test later delete
void testPrintScreen(void){
	
}

void openingScreen(){
	const char soteriaScreen[] = {'S', 'O', 'T', 'E', 'R', 'I', 'A'};
	unsigned int j = 0;
	while(soteriaScreen != '\0'){
		vram[current_loc] = soteriaScreen[j];
		vram[current_loc+1] = 0x07;
		++j;
		current_loc = current_loc + 2;
	}
}
