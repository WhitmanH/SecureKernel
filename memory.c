/**
* Haley Whitman & Andrew Hill
* Minimal x86 Kernel
*/
#include "system.h"

unsigned long *pageDirectory = (unsigned long *) 0x9C000;
unsigned long *pageTable = (unsigned long *) 0x9D000; // Init page table (after page directory)

void *memcpy(void *dest, const void *src, unsigned short count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, unsigned short count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned short count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short strlen(const char *str)
{
    unsigned short retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}


/*
*Init code function dervied from http://www.osdever.net/tutorials/view/implementing-basic-paging

void paging_init(void){
    unsigned long *pageDirectory = (unsigned long *) 0x9C000;
    unsigned long *pageTable = (unsigned long *) 0x9D000; // Init page table (after page directory)

    unsigned long address=0;
    unsigned int i;

    for(i=0; i<Kilobyte; i++){
        pageTable[i] = address | 3; //This gives read/write. (011) flags, and present.
        address = address + (4 * Kilobyte);
    }
    //Have to set the first page into the directory before it uses it, otherwise will not work.
    pageDirectory[0] = (unsigned) pageTable; //read/write and present
    pageDirectory[0] = pageDirectory[0] | 3; 

    for(i = 1; i<Kilobyte; i++){
        pageDirectory[i] = 0 | 2; //read/write and not present
    }

    write_cr3(pageDirectory); // page directory address into cr3
    write_cr0(read_cr0() | 0x80000000); //paging bit in cr0 to 1, enable paging


}

*/