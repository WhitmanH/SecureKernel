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
	clearScreen();
}

void newCommand(void){
	decodeInstruction();
	char* pwd = "Soteria@CAMEL:/$ ";
	message(userInput);
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
	message("");
}

void clearScreen(void){
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


/*@brief Takes a pointer to a character and will print the full message. No newlines are created.
* @param message pointer to first index of string to print.
* @return void.
*/
void message(char* message){
	unsigned int j = 0;
	char* pwd = "Soteria@CAMEL:/$ ";
	char* msg=strcat(pwd, message);
	/*
	* Writing the string to VRAM.
	*/
	while(msg[j] != '\0'){
		/* Printing the sting */
		vram[current_loc] = msg[j];
		/* Declaring font color, black bg, light grey fg */
		vram[current_loc+1] = 0x07;
		++j;
		current_loc = current_loc + 2;
	}
}
