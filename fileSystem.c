#include "system.h"
//#include "stdio.h"
#define numberFiles 12


int totalFiles = numberFiles;
int currentDirectory=0;
char* pwd;
int cur_file=0;

File* curDirectory;
File* prevDirectory;
File* blank;




/*stores user created files*/
File files[5];



/* Better file system structure */
File FileSystem[20][6];
File FileIndex[20];






void FILESYSTEM_init(void){

	int i=0,j=0;
	create_file_system_array();
	currentDirectory = 0;
	//File empty={"","","",0,0,NULL,0,0,0,0};
	File root = {"root", "","",0, 0,(struct File*)FileSystem[0], 3, 1, 5};
	File usr = {"usr", "usr","", 0, 1, (struct File*)FileSystem[1], 3, 1, 2};
	File home = {"home", "home", "", 0,2, (struct File*)FileSystem[2], 3, 1, 1};
	//File lib = {"lib", "lib", "", 1, (struct File*)lvl, (struct File*)lvl_lib, 3, 1};
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

void create_file_system_array(){
	File empty={"","","",0,0,NULL,0,0,0};
	int i=0, j=0;
	for( ; i<20; i++){
		for(j=0; j<max_file_size; j++){
			FileSystem[i][j] = empty;
		}
		
	}
}

int find_cur_direcroty_idnes(){
	int i=0, j=0;
	for( ; i<6; i++){
		if(strcmp(curDirectory[i].name, "")){
			for(j=0; j<numberFiles; j++){
				if(!strcmp(FileIndex[j].name, curDirectory[i].name)){
					message(curDirectory[i].name); 
					message(" ");
					message(FileIndex[j].name);
				}
			}	
		}
	}
	return 0;
}


void create_directory(char* name){
	int i=0;
	for( ; i<max_file_size ; i++){
		if(!strcmp(curDirectory[i].name, "")){
			message("make new file");
			strcpy(curDirectory[i].name, name);
			strcpy(curDirectory[i].desc, "");
			curDirectory[i].parent_index = currentDirectory;
			curDirectory[i].children=(struct File*)FileSystem[totalFiles];
			curDirectory[i].privilege=3;
			curDirectory[i].index=totalFiles;
			curDirectory[i].folder=1;
			FileIndex[totalFiles]= curDirectory[i];
			totalFiles++; 
			return;
		}
	}
	message("The size of this file has exceed its maximum capcity. You directory cannot be created"); 
}

void create_file(char* name, char * desc){
	int i=0;
	for( ; i<max_file_size ; i++){
		if(!strcmp(curDirectory[i].name, "")){
			message("make new file");
			strcpy(curDirectory[i].name, name);
			strcpy(curDirectory[i].desc, desc);
			curDirectory[i].parent_index = currentDirectory;
			curDirectory[i].children=(struct File*)FileSystem[totalFiles];
			curDirectory[i].privilege=3;
			curDirectory[i].folder=0;
			curDirectory[i].index=totalFiles;
			FileIndex[totalFiles]= curDirectory[i];
			totalFiles++; 
			return;
		}
	}
	message("The size of this file has exceed its maximum capcity. You directory cannot be created"); 
}


void delete_file(char* name){
	int i;
	File empty={"","","",0,0,NULL,0,0,0};
	for(i=0; i<max_file_size; i++){
		if(!strcmp(userArg, curDirectory[i].name)){
			if(curDirectory[i].folder==0){
				message("delete");
				curDirectory[i]=empty;
				FileIndex[curDirectory[i].index]=empty;
				totalFiles--;
				newlineX1();
			}else{
				message("Directory, not a file, cant delete using rm. Use rmdir instead.");
				newlineX1();
			}
		}
	}
}



void delete_directory(char* name){
	int i;
	File empty={"","","",0,0,NULL,0,0,0};
	for(i=0; i<max_file_size; i++){
		if(!strcmp(userArg, curDirectory[i].name)){
			if(curDirectory[i].folder==1){
				message("delete");
				curDirectory[i]=empty;
				FileIndex[curDirectory[i].index]=empty;
				totalFiles--;
				newlineX1();
			}else{
				message("File not directory, cant delete using rmdir. Use rm instead.");
				newlineX1();
			}
		}
	}
}