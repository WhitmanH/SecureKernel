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
														{7, "mkdir"}, {8, "rmdir"}, {9, "cd"}, {10, "run"}, {11, "cat"}};

int commandLookup(char* call){
	int i;
	//int = strlen(sCall)
	// char* tmp = strstrip(call);
	// message(tmp);
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
	for(i=0; i < 6; i++){
			message(curDirectory[i].name);
			message(" ");
	}
	newlineX1();
}

void cd(void){
	int i;
	if((!strcmp(userArg, ""))){ //cd with no userArg takes you to root directory.
		currentDirectory=1;
		curDirectory = prevDirectory = blank;
	}else if((!strcmp(userArg, ".."))){ //cd .. takes you to the prevdious directory.
		int next_dir = FileIndex[currentDirectory].parent_index;
		currentDirectory=next_dir;
		curDirectory=FileSystem[next_dir];
	} else {
		for(i = 0; i < 6; ++i){ //cd usrArg, change to folder specified by usrArg
			if(!strcmp(userArg, curDirectory[i].name)){
				if(curDirectory[i].privilege==0){
					message("You do not have the permissions to access \"sys\" file");
					newlineX1();
				}else if(curDirectory[i].folder==0){
					message("File not folder!!!!!");
					newlineX1();
					message("No open for you");
					newlineX1();
				}else{
				currentDirectory = curDirectory[i].index;
				File* temp = curDirectory;
				curDirectory=(File*)curDirectory[i].children;
				prevDirectory=temp;
				}
			}
		} 
	}
}

void mkdir(void){
	create_directory(userArg);
	//message(userArg);
}

void echo(void){
	if(write_flag){
		//message(userArg3);
		create_file(userArg3, userArg);
		newlineX1();
	}else{
		message(strcat(userArg, userArg2));
		newlineX1();
	}
}

void cat(void){
	int i=0;
	for(i=0; i < cur_file; i++){
		if(!strcmp(userArg, files[i].name)) {
			message(files[i].desc);
			newlineX1();
		}else{
			 message("File does not exist");
			 newlineX1();
		}
	}

}