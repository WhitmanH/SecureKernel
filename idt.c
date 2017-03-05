#include "system.h"

struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;		/*kernel segment*/
	unsigned char always0;  /*This will ALWAYS be 0*/
	unsigned char flags;    /* Set using th eabove tabe! */
	unsigned short base_hi;
};


struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
};


struct idt_entry dit[256];
struct idt_ptr idtp;

/*From kernel.asm*/
extern void idt_load()

void idt_set_gate(unsigned char num, unsigned long base, unsigned shot sel, unsigned char flags){

/* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */

    return

}



/* Initalizes the IDT */
void idt_init(void){
    /* Sets the special IDT pointer up */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}