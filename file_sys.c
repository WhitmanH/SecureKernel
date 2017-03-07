/*bin, 
usr, 
home, 
lib, 
root, 



sys => kernel
*/
#include <stdio.h>
#include "system.h"

struct Files
{
	char name[20];
	char path[50];
};


void strcpy2(char dest[], const char source[]) {
	int i = 0;
	while ((dest[i] = source[i]) != '\0') {
 	i++;
	}
}



int main(){
	struct Files files[100];
	struct Files boot, usr;
	strcpy2(boot.name, "boot");
	strcpy2(boot.path, "");
	strcpy2(usr.name, "usr");
	strcpy2(usr.path, "");
	files[0]=boot;
	files[1]=usr;
	for(int i=0; i <2; i++){
		printf("%s\n", files[i].name);
	}

}