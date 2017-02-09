/**
* Haley Whitman & Andrew Hill
* Minimal x86 Kernel
* Derived from Arjun Sreedhan
*/

void kmain(void){

	const char *openingMessage = "Soteria has booted. :)";
	char *vram = (char*)0xb8000; 

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

	j = 0;

	/*
	* Writing the string to VRAM.
	*/
	while(openingMessage[j] != '\0'){
		/* Printing the sting */
		vram[i] = openingMessage[j];
		/* Declaring font color, black bg, light grey fg */
		vram[i+1] = 0x07;
		++j;
		i = i + 2;
	}
	return;
}