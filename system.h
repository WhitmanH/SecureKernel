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
#define NUMBER_SYS_CALLS 11

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002
#define STACK_SIZE 0x4000
#define NULL ( (void *) 0)

/*
* Memory sizes
*/
#define Kilobyte 1024

extern char *vram;
extern unsigned int current_loc;
extern int currentDirectory;
extern char userInput[128];
extern char userArg[128];
extern char userArg2[128];
extern char userArg3[128];
extern char userArg4[128];
extern int write_flag;
extern int cur_file;



/*FILESYSTEM.C*/
typedef struct
{
    char name[20];
    char path[50];
    char desc[128];
    int level;
    struct File* parent;
    struct File* children;
    int privilege;
    int folder;
}File;



extern int totalFiles;
extern char* pwd;


/*Pointer to current File system array */
extern File* fileSystem;


/*File system arrays*/
extern File lvl[1];
extern File lvl0[1];
extern File lvl1[6];
extern File lvl_home[5];
extern File lvl_usr[5];
extern File lvl_lib[5];
extern File lvl_mnt[5];
extern File lvl_tmp1[1];
extern File lvl_tmp[5];
extern File lvl_sys[5];
extern File files[5];

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
extern void strcpy(char dest[], const char source[]);
extern char *strstrip(char *s);

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



 /* The Multiboot header. */
     typedef struct multiboot_header
     {
       unsigned long magic;
       unsigned long flags;
       unsigned long checksum;
       unsigned long header_addr;
       unsigned long load_addr;
       unsigned long load_end_addr;
       unsigned long bss_end_addr;
       unsigned long entry_addr;
     } multiboot_header_t;
     
     /* The symbol table for a.out. */
     typedef struct aout_symbol_table
     {
       unsigned long tabsize;
       unsigned long strsize;
       unsigned long addr;
       unsigned long reserved;
     } aout_symbol_table_t;
     
     /* The section header table for ELF. */
     typedef struct elf_section_header_table
     {
       unsigned long num;
       unsigned long size;
       unsigned long addr;
       unsigned long shndx;
     } elf_section_header_table_t;
     
     /* The Multiboot information. */
     typedef struct multiboot_info
     {
       unsigned long flags;
       unsigned long mem_lower;
       unsigned long mem_upper;
       unsigned long boot_device;
       unsigned long cmdline;
       unsigned long mods_count;
       unsigned long mods_addr;
       union
       {
         aout_symbol_table_t aout_sym;
         elf_section_header_table_t elf_sec;
       } u;
       unsigned long mmap_length;
       unsigned long mmap_addr;
     } multiboot_info_t;
     
     /* The module structure. */
     typedef struct module
     {
       unsigned long mod_start;
       unsigned long mod_end;
       unsigned long string;
       unsigned long reserved;
     } module_t;
     
     /* The memory map. Be careful that the offset 0 is base_addr_low
        but no size. */
     typedef struct memory_map
     {
       unsigned long size;
       unsigned long base_addr_low;
       unsigned long base_addr_high;
       unsigned long length_low;
       unsigned long length_high;
       unsigned long type;
     } memory_map_t;




#endif