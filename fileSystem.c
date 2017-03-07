#include "system.h"
//#include "stdio.h"
#define numberFiles 6

int totalFiles = numberFiles;
int currentDirectory;
char* pwd;
int cur_file=0;

File* fileSystem;

/*Directory for level 0, root only*/
File lvl[1];
File lvl0[1];

/*Directory for level 1, usr, home, lib, mount, sys, tmp*/
File lvl1[6];
/*Directories in home file*/
File lvl_home[10];
/*Directories in usr file*/
File lvl_usr[10];
/*Directories in lib file*/
File lvl_lib[10];
/*Directories in mnt file*/
File lvl_mnt[5];

File files[25];





void FILESYSTEM_init(void){
	int i;
	currentDirectory = 0;
	File root = {"root", "","",0, NULL, (struct File*)lvl1};
	File usr = {"usr", "usr","", 1, (struct File*)lvl, (struct File*)lvl_home};
	File home = {"home", "home", "", 1, (struct File*)lvl, (struct File*)lvl_home};
	File lib = {"lib", "lib", "", 1, (struct File*)lvl, (struct File*)lvl_home};
	File mnt = {"mnt", "mnt","", 1, (struct File*)lvl, (struct File*)lvl_mnt};
	File sys = {"sys", "sys", "", 1, (struct File*)lvl, (struct File*)lvl_home};
	File tmp = {"tmp", "tmp", "", 1, (struct File*)lvl, NULL};
	File user = {"user", "home/user", "", 2, (struct File*)lvl1, NULL};
	File c_drive = {"c", "mnt/c", "", 2, (struct File*)lvl1, NULL};


	lvl[0] = root;
	lvl1[0] = usr;
	lvl1[1] = home;
	lvl1[2] = lib;
	lvl1[3] = mnt;
	lvl1[4] = tmp;
	lvl1[5] = sys;
	lvl_home[0] = user;
	lvl_mnt[0] = c_drive;
	
	//fileSystem[7] = user; 
	fileSystem=lvl;

}

void create_directory(char* name){
	totalFiles++;
	strcpy(fileSystem[totalFiles].name, name);
}

void create_file(char* name, char * desc){
	strcpy(files[cur_file].name,name);
	strcpy(files[cur_file].desc,desc);
	files[cur_file].level = fileSystem[0].level;
	cur_file++;
}




