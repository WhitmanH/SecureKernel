/*
* Haley Whitman & Andrew Hill
* Derived from Arjun Sreedharan
*/

OUTPUT_FORMAT(elf32-i386)
ENTRY(entry)
SECTIONS
{
	. = 0x100000;
	.text : {*(.text)}
	.data : {*(.data)}
	.bss : {*(.bss)}
}