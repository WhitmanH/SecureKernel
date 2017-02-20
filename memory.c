/**
* Haley Whitman & Andrew Hill
* Minimal x86 Kernel
*/
#include "system.h"

void *memcpy(void *dest, const void *src, unsigned short count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, unsigned short count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned short count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short strlen(const char *str)
{
    unsigned short retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}