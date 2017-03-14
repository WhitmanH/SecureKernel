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




/*file system */
File FileSystem[max_file_system_size][max_file_size];
File FileIndex[max_file_system_size];


void FILESYSTEM_init(void){

	populate_file_system();


}

void create_file_system_array(){
	File empty={"","","",0,0,NULL,0,0,0};
	int i=0, j=0;
	for( ; i<max_file_system_size; i++){
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
	if(!strcmp(name,"")) {// Cannot make a directory with no name
			message("You need to enter directory name");
			newlineX1();
			return;
		}
	for( ; i<max_file_size ; i++){
		if(!strcmp(curDirectory[i].name, name)){//Cannot make a directory that with same path
			message("That file already exists");
			newlineX1();
			return;
		}else if((!strcmp(curDirectory[i].name, ""))){
			//message("make new direcoty");
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
	if(!strcmp(name,"")) { //Cannot make a file with no name
			message("You need to enter directory name");
			newlineX1();
			return;
		}
	for( ; i<max_file_size ; i++){
		if(!strcmp(curDirectory[i].name, name)){//Cannot make a file whos path already exists
			message("That file already exists");
			return;
		}else if((!strcmp(curDirectory[i].name, ""))){
			//message("make new file");
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