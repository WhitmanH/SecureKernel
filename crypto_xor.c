/**
* Haley Whitman & Andrew Hill
* XOR Ciper 
* Derived from KyleBanks: https://github.com/KyleBanks/XOREncryption/blob/master/C/main.c
*/
#include "system.h"


/*Three different levels of keys*/
char keys[3][8]={{'S','O','T','E','R','I', 'A'}, {'C','A','M','E','L'}, {'D','U','C','K'}};

/*@brief Simple xor encryption algorithm. 
* @param input: the string to be encrypted or decrypted
* @param key: integer specifying which key to use
* @return None
*/
void xor_encrypt_decrypt(char* input, int key){
	int i=0;
	char* temp=input;
	int jj = strlens(keys[key]);

	for(i=0; i< strlens(input); i++){
		input[i] = temp[i] ^ keys[key][i % jj];
	}
}
