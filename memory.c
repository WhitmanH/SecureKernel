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


void populate_file_system(){
    int i=0,j=0;
    create_file_system_array();
    currentDirectory = 0;
    File root = {"root", "","",0, 0,(struct File*)FileSystem[0], 3, 1, 5};
    File usr = {"usr", "usr","", 0, 1, (struct File*)FileSystem[1], 3, 1, 2};
    File home = {"home", "home", "", 0,2, (struct File*)FileSystem[2], 3, 1, 1};
    File mnt = {"mnt", "mnt","", 0,3, (struct File*)FileSystem[3], 3, 1, 1};
    File sys = {"sys", "sys", "", 0,4, (struct File*)FileSystem[4], 0, 1, 1};
    File tmp = {"tmp", "tmp", "", 0,5, (struct File*)FileSystem[5], 3, 1, 0};
    File user = {"user", "home/user", "", 2 ,6, (struct File*)FileSystem[6], 3, 1, 0};
    File c_drive = {"c", "mnt/c", "", 4,7, (struct File*)FileSystem[7], 3, 1,0};
    File bin = {"bin", "usr/bin", "", 1,8,  (struct File*)FileSystem[8], 3, 1, 0};
    File src = {"src", "usr/src", "", 1,9, (struct File*)FileSystem[9], 3, 1, 0};
    File kern = {"kernel", "usr/kernelnasm", "", 2, 10, (struct File*)FileSystem[10], 3, 1, 0};
    File andrew  ={"andrew","home/user/andrew", "", 6, 11, (struct File*)FileSystem[11], 3, 1, 0};

    FileIndex[0]= root;
    FileIndex[1] = usr;
    FileIndex[2] = home;
    FileIndex[4] = sys;
    FileIndex[3] = mnt;
    FileIndex[5] = tmp;
    FileIndex[6] = user;
    FileIndex[7] = c_drive;
    FileIndex[8] = bin;
    FileIndex[9] = src;
    FileIndex[11] = andrew;


    FileSystem[0][0]=usr; 
    FileSystem[0][1]=home; 
    FileSystem[0][2]=sys; 
    FileSystem[0][3]=mnt;
    FileSystem[0][4]=tmp;

    FileSystem[1][0]=bin;
    FileSystem[1][1]=src;

    FileSystem[2][0]=user;

    FileSystem[6][0]=andrew;


    blank=curDirectory=prevDirectory=FileSystem[0];

}
