void paging()
{
	unsigned long *page_directory	= (unsigned long *) 0x9C000;
	unsigned long *page_table		= (unsigned long *) 0x9D000; // the page table comes right after the page directory
	unsigned long address=0; // holds the physical address of where a page is
	unsigned int i;

	// map the first 4MB of memory
	for(i=0; i<1024; i++)
	{
		page_table[i] = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
		address = address + 4096; // 4096 = 4kb
	};

	// fill the first entry of the page directory
	page_directory[0] = page_table; // attribute set to: supervisor level, read/write, present(011 in binary)
	page_directory[0] = page_directory[0] | 3;
	// fill the rest of the page directory
	for(i=1; i<1024; i++)
	{
		page_directory[i] = 0 | 2; // attribute set to: supervisor level, read/write, not present(010 in binary)
	};


void bin(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i)? printf("1"): printf("0");
}

int main (){
	printf("HEllo");
	int v = 0 | 3;
	bin(3);

}