#ifndef __SYSTEM_H
#define __SYSTEM_H

/*
* Global Values
*/
#define IDT_SIZE 256
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define COLUMNS_IN_LINE 80
#define LINES 25
#define BYTES_FOR_EACH_ELEMENT 2
#define NUMBER_SYS_CALLS 10

/*
* Memory sizes
*/
#define Kilobyte 1024

extern char *vram;
extern unsigned int current_loc;

/*MEMORY.C*/
extern void *memcpy(void *dest, const void *src, unsigned short count);
extern void *memset(void *dest, char val, unsigned short count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned short count);
extern unsigned short strlen(const char *str);
extern void paging_init(void);

/*output.C*/
extern void newlineX2(void);
extern void newlineX1(void);
extern void newCommand(void);
extern void clear(void);
extern void message(char* message);
extern void openingScreen();

/*SOT_STDLIB.C*/
extern char* strcat(char*, char*);
extern int my_strcmp(char*, char*);
extern int strlens(char*);

/*SYSTEM_CALLS.C*/
extern int commandLookup(char* call);


/*VGA*/
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

#endif