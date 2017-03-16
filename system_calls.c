#include "system.h"

/*@brief Takes a string and returns the coordinating "opcode" value.
* @param call String of system call
* @return int Of corresponding call's opcode.
*/
int currentDirectory;
char userArg[128];
char userArg2[128];



struct systemCalls{
	int id;
	char call[64];
};

struct systemCalls SYSTEM_CALLS[NUMBER_SYS_CALLS] = {{1, "-help"}, {2, "clear"}, {3, "echo"}, {4, "ls"}, {5, "read"}, {6, "edit"},
														{7, "mkdir"}, {8, "rmdir"}, {9, "cd"}, {10, "run"}, {11, "cat"}, {12, "rm"}, {13, "chmod"}};

int commandLookup(char* call){
	int i;
	for(i = 0; i < NUMBER_SYS_CALLS; ++i){
		if(!strcmp(call, SYSTEM_CALLS[i].call)){
			return SYSTEM_CALLS[i].id;
		}
	} 
}


void clear(void){
	unsigned int i = 0, j = 0;
	/*
	* Loop clears the screen. There exists 25 lines of 80 columns, and each element
	* takes 2 bytes.
	*/
	while(j < 80 * 25 * 2){ 
		//Print blank character
		vram[j] = ' ';
		//Highlight next character a light gray
		vram[j+1]= 0x07;
		j = j + 2;
	}
	current_loc = 0;
}

void chmod (void){
	int i=0, j=1, k=0;
	int file=-1;
	char per[3]="";
	memset(per, '\0', 3);


	if(!strcmp(FileIndex[currentDirectory].owner, "camel")){
		for(i=0; i <totalFiles; i++){
			if(!strcmp(FileIndex[i].name, userArg2)){
				file=i;
				break;
			}
		}
		for(i=0; i<3; i++){
			switch(userArg[i]){
				case '0' :
					strcpy(per,"---");
					break;
				case '1' :
					strcpy(per,"--x");
					break;
				case '2' : 
					strcpy(per,"-w-");
					break;
				case '3' : 
					strcpy(per,"-wx");
					break;		
				case '4' :
					strcpy(per,"r--");
					break;
				case '5' :
					strcpy(per,"r-x");
					break;
				case '6' :
					strcpy(per,"rw-");
					break;
				case '7' :
					strcpy(per,"rwx");
					break;	
				default :
					strcpy(per,"---");
				}
				if(file > -1){
					for(k=0; k<3; k++){
						curDirectory[file].permissions[j]=per[k];
						j++;
					}
				}
			}
		}else{
			message("chmod: cannot modify directory \"");
			message(userArg);
			message("\": Permission denied");
			newlineX1();
		}
}


void help(void){
	newlineX2();
	message("Currently Available System Calls:");
	newlineX1();
	int i;
	for(i = 0; i < NUMBER_SYS_CALLS; ++i){
		if(strcmp("\0", SYSTEM_CALLS[i].call)){
			message(SYSTEM_CALLS[i].call); message(", ");
		}
	}
	newlineX1();
	message("For help on a specific system call type -help <system call>.");
	newlineX2();
}


void ls(void){
	int i;
	if (!strcmp(userArg, "-la")){
		message("drwxr-xr-x 2 root root   0 Dec 31  1969 .");
		newlineX1();
		message("drwxr-xr-x 2 root root   0 Dec 31  1969 ..");
		newlineX1();
		for(i=0; i < FileIndex[currentDirectory].num_files; i++){
				message(curDirectory[i].permissions);
				message(" ");
				message(curDirectory[i].links);
				message(" ");
				message(curDirectory[i].owner);
				message(" ");
				message(curDirectory[i].group);
				message("   ");
				message(curDirectory[i].size);
				message(" ");
				message(curDirectory[i].date);
				message(" ");
				message(curDirectory[i].name);
				newlineX1();
		}
		newlineX1();
	}else if (! strcmp(userArg, "")){
		for(i=0; i < max_file_size; i++){
				message(curDirectory[i].name);
				message(" ");
		}
		newlineX1();
	}
}

void cd(void){
	int i;
	char messg[2];
	//char new_path[150];
	if((!strcmp(userArg, ""))){ //cd with no userArg takes you to root directory.
		currentDirectory=0;
		curDirectory = NullPage;
		strcpy(pwd, "Soteria@CAMEL:/$ ");
	}else if((!strcmp(userArg, ".."))){ //cd .. takes you to the prevdious directory.
		int next_dir = FileIndex[currentDirectory].parent_index;

		strcpy(pwd, FileIndex[next_dir].pwd);
		currentDirectory=next_dir;
		curDirectory=FileSystem[next_dir];
	} else {
		for(i = 0; i < max_file_size; ++i){ //cd usrArg, change to folder specified by usrArg
			if(!strcmp(userArg, curDirectory[i].name)){
				if(strcmp(curDirectory[i].permissions[7],'r')){
					message("You do not have the permissions to access \"");
					message(curDirectory[i].name);
					message("\" file");
					newlineX1();
				}else if( strcmp(curDirectory[i].permissions[0],'d')){
					message("File not folder!!!!!");
					newlineX1();
					message("No open for you");
					newlineX1();
				}else{
				strcpy(pwd, curDirectory[i].pwd);
				currentDirectory = curDirectory[i].index;
				File* temp = curDirectory;
				curDirectory=(File*)curDirectory[i].children;
				
				}
			}
		} 
	}
}

void mkdir(void){
	if(strcmp(FileIndex[currentDirectory].permissions[7],'r')){
		message("mkdir: cannot create directory \"");
		message(userArg);
		message("\": Permission denied");
		newlineX1();
	}else{
		create_directory(userArg);
	}

	
}

void echo(void){
	if(write_flag){
		if(strcmp(FileIndex[currentDirectory].permissions[7],'r')){
			message("echo: cannot create file \"");
			message(userArg);
			message("\": Permission denied");
			newlineX1();
		}else{
		create_file(userArg3, userArg);
		newlineX1();
		}
	}else{
		message(strcat(userArg, userArg2));
		newlineX1();
	}
}

void rm(void){
		int i=0;
	for(i=0; i < max_file_size; i++){
		if(!strcmp(userArg, curDirectory[i].name)) {
			if(strcmp(FileIndex[currentDirectory].permissions[8],'w')){
				message("rm: cannot create directory \"");
				message(userArg);
				message("\": Permission denied");
				newlineX1();
				return;
			}else{
				delete_file(userArg);
				return;
			}
		}
	}
}

void rmdir(void){
	int i=0;
	for(i=0; i < max_file_size; i++){
		if(!strcmp(userArg, curDirectory[i].name)) {
			if(strcmp(curDirectory[i].permissions[8],'w')){
				message("rmdir: cannot create directory \"");
				message(userArg);
				message("\": Permission denied");
				newlineX1();
				return;
			}else{
				delete_directory(userArg);
				return;
			}
		}
	}
}


void cat(void){
	int i=0;
	for(i=0; i < max_file_size; i++){
		if(!strcmp(userArg, curDirectory[i].name)) {
			if(curDirectory[i].folder == 1){
				message("cat: cannot read file \"");
				message(userArg);
				message("\": is a directory");
				newlineX1();
				return;
			}
			if(strcmp( curDirectory[i].permissions[7],'r')){
				message("cat: read file \"");
				message(userArg);
				message("\": Permission denied");
				newlineX1();
			}else{
				message(curDirectory[i].desc);
				newlineX1();
				return;
			}
		}
	}

}