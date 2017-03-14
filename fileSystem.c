#include "system.h"
//#include "stdio.h"
#define numberFiles 8

int totalFiles = numberFiles;
int currentDirectory;
char* pwd;
int cur_file=0;

File* curDirectory;
File* prevDirectory;
File* blank;

// /*Directory for level 0, root only*/
// File lvl[1];
// File lvl0[1];

// /*Directory for level 1, usr, home, lib, mount, sys, tmp*/
// File lvl1[6];
// /*Directories in home file*/
// File lvl_home[5];
// /*Directories in mnt file*/
// File lvl_mnt[5];

// /*Directories in usr file*/
// File lvl_usr[5];
// /*Directories in lib file*/
// File lvl_lib[5];
// /*Directories in tmp file*/
// File lvl_tmp[1];
// File lvl_tmp1[1];
// /*Directories in sys file*/
// File lvl_sys[5];
// File lvl_user[2];





/*stores user created files*/
File files[5];



/* Better file system structure */
File FileSystem[20][6];
File FileIndex[20];







void FILESYSTEM_init(void){

	int i=0,j=0;
	currentDirectory = 0;
	File empty={"","","",0,NULL,0,0,0};
	File root = {"root", "","",0, (struct File*)FileSystem[0], 3, 1, 5};
	File usr = {"usr", "usr","", 1, (struct File*)FileSystem[1], 3, 1, 2};
	File home = {"home", "home", "", 1, (struct File*)FileSystem[2], 3, 1, 1};
	//File lib = {"lib", "lib", "", 1, (struct File*)lvl, (struct File*)lvl_lib, 3, 1};
	File mnt = {"mnt", "mnt","", 1,  (struct File*)FileSystem[3], 3, 1, 1};
	File sys = {"sys", "sys", "", 1, (struct File*)FileSystem[4], 0, 1, 1};
	File tmp = {"tmp", "tmp", "", 1, (struct File*)FileSystem[5], 3, 1, 0};

	File user = {"user", "home/user", "", 2, (struct File*)FileSystem[6], 3, 1, 0};
	File c_drive = {"c", "mnt/c", "", 2, (struct File*)FileSystem[7], 3, 1,0};
	File bin = {"bin", "usr/bin", "", 2,  (struct File*)FileSystem[8], 3, 1, 0};
	File src = {"src", "usr/src", "", 2, (struct File*)FileSystem[9], 3, 1, 0};
	File kern = {"kernel", "usr/kernelnasm", "", 2, (struct File*)FileSystem[10], 3, 1, 0};
	File temp_blank = {"", "tmp", "", 2, (struct File*)FileSystem[11], 3, 1, 0};

	File FileIndex[20] = {usr, home, sys, mnt, tmp, bin, src, user};




	// lvl[0] = root;
	// lvl1[0] = usr;
	// lvl1[1] = home;
	// lvl1[2] = sys;
	// //lvl1[2] = lib;
	// lvl1[3] = mnt;
	// lvl1[4] = tmp;


	
	// lvl_home[0] = user;
	// lvl_mnt[0] = c_drive;
	// lvl_usr[0]=bin;
	// lvl_usr[1]=src;
	// lvl_sys[0]=kern;
	// lvl_tmp1[0]=temp_blank;
	
	// lvl_user[0]=empty;
	// //fileSystem[7] = user; 
	// //curDirectory=prevDirectory=lvl1;
	// //blank=lvl1;


	FileSystem[0][0]=usr; 
	FileSystem[0][1]=home; 
	FileSystem[0][2]=sys; 
	FileSystem[0][3]=mnt;
	FileSystem[0][4]=tmp;

	FileSystem[1][0]=bin;
	FileSystem[1][1]=src;

	FileSystem[2][0]=user;


	blank=curDirectory=prevDirectory=FileSystem[0];


}

void create_directory(char* name){
	strcpy(files[cur_file].name,name);
	strcpy(files[cur_file].desc,"");
	files[cur_file].level = curDirectory[0].level;
	cur_file++;
}

void create_file(char* name, char * desc){
	strcpy(files[cur_file].name,name);
	strcpy(files[cur_file].desc,desc);
	files[cur_file].level = curDirectory[0].level;
	cur_file++;
}




