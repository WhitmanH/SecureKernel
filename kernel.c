/**
* Haley Whitman & Andrew Hill
* Minimal x86 Kernel
* Derived from Arjun Sreedhan
*/

#include "keyboard_map.h"
#include "system.h"

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *IDT_ptr);
typedef void (*call_module_t)(void);

/*
* Global Variables
*/
char *vram = (char*)0xb8000; 
unsigned int current_loc = 0;
char userInput[128];
int numbKeys = 0;


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


	/*Port Guide
	*PIC1: 0x20 for command and 0x21 for data
	*PIC2: 0xA0 for Command and 0xA1 for data
	*Initialization done here: http://stanislavs.org/helppc/8259.html
	* 0x11 is the initialize command for both PICs
	*/
	//ICW1 Initialisation Command Word One)
	write_port(0x20, 0x11);
	write_port(0xA0, 0x11);
	//ICW2
	write_port(0x21, 0x20); //0x21 comes from adding 1 bit to find the interrupt number from where PIC1 is initialized at 0x20.
	write_port(0xA1, 0x28);
	//ICW3
	write_port(0x21, 0x00);
	write_port(0xA1, 0x00);
	//ICW4
	write_port(0x21, 0x01);
	write_port(0xA1, 0x01);
	//Mask interrupts
	write_port(0x21, 0xff);
	write_port(0xA1, 0xff);


	IDT_address = (unsigned long)IDT;
	IDT_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((IDT_address & 0xffff) << 16);
	IDT_ptr[1] = IDT_address >> 16;
	load_idt(IDT_ptr);
}
//moving the blinking line in the kernel
void move_cursor(void){

}

void kb_init(void){
	//enables only keyboard
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
		}else if(keycode == 28){//if keyboard enter
			newCommand();
			numbKeys = 0;
			memset(userInput, 0, 128);
		}else if(keycode == 14){//backspace
			userInput[--numbKeys] = '\0';
			vram[--current_loc] = 0x00;
			vram[--current_loc] = ' ';
			//vram[--current_loc] = 0x0;
			vram[current_loc] = keyboard_map[0];
		} else{
			userInput[numbKeys++] = keyboard_map[keycode];
			vram[current_loc++] = keyboard_map[keycode];
			vram[current_loc++] = 0x07;
			vram[current_loc] = keyboard_map[0];
		}
	}
}




void kmain(unsigned int ebx){
	
	multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
	unsigned int address_of_module = mbinfo->mods_addr;
	char *openingMessage = "OS Kernel has booted.";

	unsigned int i = 0, j = 0;

	newlineX1();
	message(openingMessage);

	newlineX2();
	message("Soteria@CAMEL:/$ ");


	IDT_init();
	kb_init();
	FILESYSTEM_init();
	/* ... */
	
	//paging_init(); //without this, we only have access to 16mb of memory by default on x86 system.
	//call_module_t start_program = (call_module_t) address_of_module;
	//start_program();
	/* we’ll never get here, unless the module code returns */


	while(1);

}

void soteria(void){
	char *openingMessage = "Soteria has booted.";
	clear();
	message(openingMessage);
	//mem_init();
	//auth_init();
}
