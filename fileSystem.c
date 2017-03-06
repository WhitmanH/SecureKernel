#include "system.h"
#define numberFiles 6
int totalFiles = numberFiles;

File fileSystem[100];

void FILESYSTEM_init(void){
	int i;
	currentDirectory = 0;
	File root = {"root", "/", 0};
	File usr = {"usr", "/usr", 1};
	File home = {"home", "/home", 1};
	File lib = {"lib", "/lib", 1};
	File mnt = {"mnt", "/mnt", 1};
	File sys = {"sys", "/sys", 1};
	File tmp = {"tmp", "/sys", 1};

	fileSystem[0] = root;
	fileSystem[1] = usr;
	fileSystem[2] = home;
	fileSystem[3] = lib;
	fileSystem[4] = mnt;
	fileSystem[5] = sys;
	fileSystem[6] = tmp;

}

void create_directory(char* name){
	totalFiles++;
	strcpy(fileSystem[totalFiles++].name, name);
}