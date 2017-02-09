/**
* Haley Whitman & Andrew Hill
* Minimal x86 Kernel
* Derived from Arjun Sreedhan
*/

#include "keyboard_map.h"

/*
* Global Values
*/


#define IDT_SIZE 256
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define COLUMNS_IN_LINE 80
#define LINES 25
#define BYTES_FOR_EACH_ELEMENT 2

/*
* Global Variables
*/
char *vram = (char*)0xb8000; 
unsigned int current_loc = 0;


extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *IDT_ptr);

/*
* Interrupt Descripter Table (IDT)
*/
struct IDT_entry{
	unsigned short int offset_lBits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_hBits;
};

struct IDT_entry IDT[IDT_SIZE];

void IDT_init(void){
	unsigned long keyboard_address;
	unsigned long IDT_address;
	unsigned long IDT_ptr[2];

	//Creating an IDT for the keyboard inputs
	keyboard_address = (unsigned long)keyboard_handler;
	IDT[0x21].offset_lBits = keyboard_address & 0xffff;
	IDT[0x21].selector = 0x08;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = 0x8e; //Interrupt gate
	IDT[0x21].offset_hBits = (keyboard_address & 0xffff0000) >> 16;


	write_port(0x20, 0x11);
	write_port(0xA0, 0x11);

	write_port(0x21, 0x20);
	write_port(0xA1, 0x28);

	write_port(0x21, 0x00);
	write_port(0xA1, 0x00);

	write_port(0x21, 0x01);
	write_port(0xA1, 0x01);

	write_port(0x21, 0xff);
	write_port(0xA1, 0xff);


	IDT_address = (unsigned long)IDT;
	IDT_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((IDT_address & 0xffff) << 16);
	IDT_ptr[1] = IDT_address >> 16;
	load_idt(IDT_ptr);
}

void kb_init(void){
	write_port(0x21, 0xFD);
}

void keyboard_handler_main(void){
	unsigned char status;
	char keycode;

	//Write the end of frame
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);

	if(status & 0x01){
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0){
			return;
		}
		vram[current_loc++] = keyboard_map[keycode];
		vram[current_loc++] = 0x07;
	}

}



void kmain(void){

	const char *openingMessage = "Soteria has booted. Try typing!";

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

	j = 0;

	/*
	* Writing the string to VRAM.
	*/
	while(openingMessage[j] != '\0'){
		/* Printing the sting */
		vram[i] = openingMessage[j];
		/* Declaring font color, black bg, light grey fg */
		vram[i+1] = 0x07;
		++j;
		i = i + 2;
	}
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
	current_loc = current_loc + (line_size - current_loc % (line_size));

	IDT_init();
	kb_init();


	while(1);

}