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
File lvl_home[5];
/*Directories in mnt file*/
File lvl_mnt[5];

/*Directories in usr file*/
File lvl_usr[5];
/*Directories in lib file*/
File lvl_lib[5];
/*Directories in tmp file*/
File lvl_tmp[5];
File lvl_tmp1[1];
/*Directories in sys file*/
File lvl_sys[5];
/*stores user created files*/
File files[5];





void FILESYSTEM_init(void){

	int i=0,j=0;
	currentDirectory = 0;
	File empty={"","","",0, NULL,NULL,0,0};
	File root = {"root", "","",0, NULL, (struct File*)lvl1, 3, 1};
	File usr = {"usr", "usr","", 1, (struct File*)lvl, (struct File*)lvl_usr, 3, 1};
	File home = {"home", "home", "", 1, (struct File*)lvl, (struct File*)lvl_home, 3, 1};
	//File lib = {"lib", "lib", "", 1, (struct File*)lvl, (struct File*)lvl_lib, 3, 1};
	File mnt = {"mnt", "mnt","", 1, (struct File*)lvl, (struct File*)lvl_mnt, 3, 1};
	File sys = {"sys", "sys", "", 1, (struct File*)lvl, (struct File*)lvl_sys, 0, 1};
	File tmp = {"tmp", "tmp", "", 1, (struct File*)lvl, (struct File*)lvl_tmp1, 3, 1};

	File user = {"user", "home/user", "", 2, (struct File*)lvl1, NULL, 3, 1};
	File c_drive = {"c", "mnt/c", "", 2, (struct File*)lvl1, NULL, 3, 1};
	File bin = {"bin", "usr/bin", "", 2, (struct File*)lvl1, NULL, 3, 1};
	File src = {"src", "usr/src", "", 2, (struct File*)lvl1, NULL, 3, 1};
	File kern = {"kernel", "usr/kernelnasm", "", 2, (struct File*)lvl1, NULL, 3, 1};
	File temp_blank = {"", "tmp", "", 2, (struct File*)lvl1, NULL, 3, 1};

	while(j<5){
		lvl_tmp[j]=empty;
		j++;
	}



	lvl[0] = root;
	lvl1[0] = usr;
	lvl1[1] = home;
	lvl1[2] = sys;
	//lvl1[2] = lib;
	lvl1[3] = mnt;
	lvl1[4] = tmp;
	
	lvl_home[0] = user;
	lvl_mnt[0] = c_drive;
	lvl_usr[0]=bin;
	lvl_usr[1]=src;
	lvl_sys[0]=kern;
	lvl_tmp1[0]=temp_blank;
	
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




