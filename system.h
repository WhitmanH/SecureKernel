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

extern char *vram;
extern unsigned int current_loc;


/*MEMORY.C*/
extern void *memcpy(void *dest, const void *src, unsigned short count);
extern void *memset(void *dest, char val, unsigned short count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned short count);
extern unsigned short strlen(const char *str);

/*PRINTYPRINT.C*/
extern void newlineX2(void);
extern void newlineX1(void);
extern void newCommand(void);
extern void clearScreen(void);
extern void message(const char* message);


#endif