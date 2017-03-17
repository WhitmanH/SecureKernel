/**
* Haley Whitman & Andrew Hill
* Minimal x86 Kernel
*/
#include "system.h"

/*Pointers to Null Page and and current directory*/
File* curDirectory;
File* NullPage;


/*file system */
File FileSystem[max_file_system_size][max_file_size];
File FileIndex[max_file_system_size];



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


/*@brief Takes a string, returns the length of that string
* @param str: a constant string
* @return int OF the length of str.
*/
unsigned short strlen(const char *str)
{
    unsigned short retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}


/*@brief Creates an example encrypted file at boot.
* @param None
* @return None
*/
void initalize_crypto(){
    char base[128];
    strcpy(base,"encrypted message");
    File example_crypto = {"crypto1.txt", "", "", "", 0, 11, (struct File*)FileSystem[11], 3, 2, 0,"-rwxr-xr-x", "root", "root", "2", "Mar 17  2107", "0"};
    FileIndex[11] = example_crypto;
    FileSystem[0][5]=example_crypto;    
    xor_encrypt_decrypt(base,2);
    strcpy(FileSystem[0][5].desc,base);

}


/*@brief returns an int, represents the least privilege key to be used to encrypt or decrypt.
* @param cur_file: file to be decrypted
* @return None
*/
int get_least_permission_key(File cur_file){
    message(cur_file.permissions);
    char public = cur_file.permissions[7];
    char group = cur_file.permissions[4];
    char owner = cur_file.permissions[1];
    if(!strcmp(public, 'r')){
        return 2;
    }else if(!strcmp(group, 'r')){
        return 1;
    }else if(!strcmp(owner, 'r')){
        return 0;
    }
    return -1;
}


/*@brief crates files and uses these file to populate the filesystem.
* @param None
* @return None
*/
void populate_file_system(){
    int i=0,j=0;
    create_file_system_array();
    currentDirectory = 0;

    /*File objects*/
    File root = {"root", "Soteria@CAMEL:/$ ","/","",0, 0,(struct File*)FileSystem[0], 3, 1, 6,"d---------", "", "", "", "Dec 31  1969", "0"};
    File usr = {"usr", "Soteria@CAMEL:/usr$ ","/usr/","", 0, 1, (struct File*)FileSystem[1], 0, 1, 2,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File home = {"home", "Soteria@CAMEL:/home$ ","/home/", "", 0,2, (struct File*)FileSystem[2], 3, 1, 1,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File mnt = {"mnt", "Soteria@CAMEL:/mnt$ ","/mnt/","", 0,3, (struct File*)FileSystem[3], 3, 1, 1,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File sys = {"sys", "Soteria@CAMEL:/sys$ ", "/sys/", "", 0,4, (struct File*)FileSystem[4], 0, 1, 1,"drwxr-xr-x", "root", "root", "1", "Dec 31  1969", "0"};
    File tmp = {"tmp", "Soteria@CAMEL:/tmp$ ", "/tmp/", "", 0,5, (struct File*)FileSystem[5], 3, 1, 0,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File user = {"camel", "Soteria@CAMEL:/home/camel$ ", "/home/camel/", "", 2 ,6, (struct File*)FileSystem[6], 3, 1, 0,"drwxr-xrwx", "camel", "camel", "2", "Mar 14 2017", "0"};
    File c_drive = {"c", "Soteria@CAMEL:/mnt/c$ ", "/mnt/c/", "", 4,7, (struct File*)FileSystem[7], 3, 1,0,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File bin = {"bin", "Soteria@CAMEL:/usr/bin$ ", "/user/bin/", "", 1,8,  (struct File*)FileSystem[8], 3, 1, 0,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File src = {"src", "Soteria@CAMEL:/usr/src$ ", "/usr/src/", "", 1,9, (struct File*)FileSystem[9], 3, 1, 0,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    File kern = {"kernel", "Soteria@CAMEL:/usr/kernel$ ", "/user/kernel/", "", 2, 10, (struct File*)FileSystem[10], 3, 1, 0,"drwxr-xr-x", "root", "root", "2", "Dec 31  1969", "0"};
    


    /*Used to keep track of current files index in FileSystem*/
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
    FileIndex[10] = kern;
    

    /*Populating the filesystem with initial files*/
    FileSystem[0][0]=usr; 
    FileSystem[0][1]=home; 
    FileSystem[0][2]=sys; 
    FileSystem[0][3]=mnt;
    FileSystem[0][4]=tmp;
   

    FileSystem[1][0]=bin;
    FileSystem[1][1]=src;
    FileSystem[2][0]=user;


    /*Keep tack of the current directory, and setting NullPage pointer*/
    NullPage=curDirectory=FileSystem[0];

}


