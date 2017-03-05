/*
* Haley Whitman & Andrew Hill
* Derived from Arjun Sreedharan
*/

OUTPUT_FORMAT(elf32-i386)
ENTRY(entry)


SECTIONS
{
	. = 0xC0100000;

	.text :AT(ADDR(.text) - 0xC0000000){
	 	*(.text)
	 }
	.data :
	 {
	 	*(.data)
	 }
	.bss : AT(ADDR(.bss) - 0xC0000000)
	{	
		*(COMMON)
		*(.bss)
	}
}