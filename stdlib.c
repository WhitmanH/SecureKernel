

/*@brief Takes a pointer to 2 strings, returns a pointer to a new string that is the concatenation of the 2 input strings.
* @param s1 pointer to the first index of the first string.
* @param s2 pointer to first index of the second string, the string to be concatenated to s1. 
* @return result:, a pionter to the first index of the string that stores the concatenation of s1 and s2.
*/
char* strcat(char* s1, char* s2){
	int i=0, j=0;
	char* result;

	/*Legnth of the first word*/
	for(i=0; s1[i] != '\0'; ++i) result[i]=s1[i] ;

	/*Add the second string to the first string*/
	for(j=0; s2[j] != '\0'; ++j, ++i) result[i] = s2[j];

	result[i] ='\0';	
	return result;
}


/*@brief Takes a pointer to 2 strings, returns a integer value 0 if the 2 strings are the same other wise a nonzero number.  
* @param s1 A pointer to the first index of the first string to be compared.
* @param s2 A pointer to the first index of the second string to be compared.
* @return An integer, 0 if s1==s2 otherwise will return a non zero value.
*/
int strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2) { ++s1; ++s2; }
    return *s1 - *s2;
}
