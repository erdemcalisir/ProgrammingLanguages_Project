#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void write(char[],FILE*); // File writer method.
char* lower(char[],char[]); // method of reducing letters.
int isKeyword(char[], char[], char[]); // keyword control method
int isIdentifier(char[], FILE*); // Identifier control method.
int isIntegerCons(char[], FILE*); // Integer control method.




int main()
{
	FILE *fp = NULL; // reader file pointer.
	FILE *fp2 = NULL;// writer file pointer.

	fp = fopen("code.psi.txt", "r"); // reader definition.	
	fp2 = fopen("code.lex.txt", "w"); // writer definition.


	int count = 0;
	char character;
	while (!feof(fp)) // file read and counter increased. 
	{
		character = getc(fp);
		count++;

	}
	fclose(fp); // file closed.
	fp = fopen("code.psi.txt", "r"); // file reopen and the pointer at the beginning.
	char* charArray;
	charArray = (char*)malloc((count+1) * sizeof(char)); // memory allocated.
	char* ptr;
	ptr = charArray;
	while ((character = getc(fp))!=EOF) // file read and char array created.
	{
		*ptr = character;
		ptr++;

	}
	*ptr = '\0';
	ptr -= count-1;
	char keywords[] = "break case char const continue do else enum float for goto if int long record return static while" ; // keywords defined.
	
	char *currentWord;
	currentWord = (char*)malloc(20 * sizeof(char));// memory allocated.
	
	char *ret ;
	ret = malloc(31 * sizeof(char));// memory allocated.

	char *chars;
	chars = (char*)malloc(31 * sizeof(char));// memory allocated.

	char* strMemory;
	strMemory = (char*)malloc(1 * sizeof(char));// memory allocated.

	int counter = 0;
	

	while (1)
	{
		
		
		
		if (*ptr == '\0') {
			break;
		}
		else if(*ptr !='+'&& *ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != ':' && *ptr != '(' && *ptr != ')' && *ptr != '[' &&  *ptr != ']' &&
			*ptr != '{' && *ptr != '}' && *ptr != ';' && *ptr != 32 && *ptr != '\0' && *ptr != '\"' && *ptr != '\n') // stopping points defined.
		{

			counter = 0;
		

			while (*ptr != '+'&& *ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != ':' && *ptr != '(' && *ptr != ')' && *ptr != '[' &&  *ptr != ']' &&
				*ptr != '{' && *ptr != '}' && *ptr != ';' && *ptr != 32 && *ptr != '\0'  && *ptr != '\"' && *ptr != '\n')
			{
				if (counter > 29) {
					write(" Identifier can not be longer than 30 characters", fp2);
					exit(0);
					//error(Identifier can not be longer than 30 characters.)
				}

				else {
					chars[counter] = *ptr;
					ptr++; // pointer increased.
					counter++;
				}
			}

			chars[counter] = '\0'; 
			


			
			char *word = lower(chars,ret); // letters downsized.
			if (isKeyword(keywords, word, currentWord)) { 
				//the method worked and it was determined whether it was keyword.
				write("Keyword(",fp2); // written to file.
				write(word, fp2);
				write(")\n\n", fp2);
			}
			else if (isIntegerCons(word,fp2)) {
				//the method worked and it was determined whether it was integer.
				write("IntConst(", fp2);// written to file.
				write(word, fp2);
				write(")\n\n", fp2);
			}
			else if (isIdentifier(word,fp2)) {
				//the method worked and it was determined whether it was identifier.
				write("Identifier(", fp2);// written to file.
				write(word, fp2);
				write(")\n\n", fp2);
			}

			
		}
		else if (*ptr == 32 || *ptr == '\n') {
			//if the character is a space, the pointer increased.
			ptr++;
		}

		else if (*ptr == ';') { //if the character is a end of line
			write("EndOfLine\n\n", fp2); // written to file.
			ptr++; // pointer increased.
		}

		else if (*ptr == '(') { //if the character is a space.
			write("LeftPar\n\n", fp2); // written to file 
			ptr++; // pointer increased.
		}
		
		else if (*ptr == ')') {  //if the character is a rightpar.
			write("RightPar\n\n", fp2); // written to file 
			ptr++; // pointer increased.
		}
		else if (*ptr == '[') {  //if the character is a LeftSquareBrakcet.
			write("LeftSquareBracket\n\n", fp2);// written to file 
			ptr++;// pointer increased.
		}
		else if (*ptr == ']') {  //if the character is a RightSquareBracket.
			write("RightSquareBracket\n\n", fp2);// written to file 
			ptr++;// pointer increased.
		}
		else if (*ptr == '{') {  //if the character is a LeftCurlyBracket.
			write("LeftCurlyBracket\n\n", fp2);// written to file 
			ptr++; // pointer increased.
		}
		else if (*ptr == '}') {  //if the character is a RightCurlyBracket.
			write("RightCurlyBracket\n\n", fp2);// written to file 
			ptr++; // pointer increased.
		}
		else if (*ptr == '*'){  //if the character is a *.
			write("Operator(*)\n\n", fp2);// written to file 
			ptr++; // pointer increased.
		}
		else if (*ptr == '+') {  //if the character is a +.
			ptr++; // pointer increased.
			if (*ptr == '+') {
				write("Operator(++)\n\n", fp2);// written to file 
				
			}
			else { //if the character is a ++
				write("Operator(+)\n\n", fp2);// written to file 
				ptr--;
			}
			ptr++; // pointer increased.

		}
		else if (*ptr == '-') { //if the character is a -
			ptr++; // pointer increased.
			if (*ptr == '-') {
				write("Operator(--)\n\n", fp2);// written to file 

			}
			else { //if the character is a --
				write("Operator(-)\n\n", fp2);// written to file 
				ptr--;
			}
			ptr++; // pointer increased.


		}
		else if (*ptr == '/') {  //if the character is a / 
			ptr++;
			if (*ptr == '*') { // comment line controller.
				ptr++;
				while (1) {
					if (*ptr == '\0') {
						// error (never ending comment line).
						write("never ending comment line", fp2);// written to file 
						exit(0);
					}
					if (*ptr == '*') {
						ptr++;
						if (*ptr == '/') {
							break;
						}
						else {
						
							continue;
							
						}
					}
					ptr++; // pointer increased.
				}
				
			}
			else {
				write("Operator(/)\n\n", fp2);// written to file 
				ptr--;
			}
			ptr++; // pointer increased.

		}
		else if (*ptr == ':') {  //if the character is a :.
			ptr++;
			if (*ptr == '=') {
				write("Operator(:=)\n\n", fp2);// written to file 
			}
			else {
				// error (: operator error.)
				write(": operator error.", fp2);// written to file 
				exit(0); 
			}
			ptr++; // pointer increased.

		}
		else if (*ptr == '\"') { //if the character is a \"(string).
			int counter = 0;
			ptr++;

			while (*ptr != '\"') {
				if (*ptr == '\0') {
					//error: missing'"'.
					write("missing'\"'.", fp2);// written to file 
					exit(0);
					
				}
				counter++; // counter increased.
				ptr++; // pointer increased.
			}

			strMemory = realloc(strMemory, (counter + 1) * sizeof(char)); // memory reallocated.
			ptr -= counter; 

			for (int i = 0; i<counter; i++) {
				strMemory[i] = *ptr;
				ptr++;
			}

			strMemory[counter] = '\0';

			write("String(", fp2);// written to file 
			write(strMemory, fp2);
			write(")\n\n", fp2);

			ptr++; // pointer increased.
		}



	}



	
	
	return 0;

}

void write(char token[],FILE *file ) { // file writer method.
	fprintf(file, "%s", token);

}

char* lower(char text[], char ret[]) { // method of reducing letters.
	
	int lenght = strlen(text);

	char character;
	for (int i = 0; i < lenght; i++) {
		character = text[i];
		
		if (character > 64 && character < 91) {
			ret[i] = character+32;
		}
		else {
			ret[i] = character;
		}

	}
	ret[lenght] = '\0';
	return ret;


}

int isIntegerCons(char word[], FILE *file) { // Integer control method.
	for (int i = 0; i<strlen(word); i++) {
		if (!(word[i]>47 && word[i]<58)) {
			return 0;
		}
	}
	if (strlen(word) > 10) {
		// error(Integer can not be longer than 10 digits)
		write("Integer can not be longer than 10 digits.", file);
		exit(0);

	}
	return 1;
}

int isIdentifier(char word[], FILE *file) {  // Identifier control method.
	if ((word[0]>64 && word[0]<91) || (word[0]>96 && word[0]<123)) {

		for (int i = 1; i<strlen(word); i++) {

			if (!((word[i]>64 && word[i]<91) || (word[i]>96 && word[i]<123) || word[i] == 95 || (word[i]>47 && word[i]<58))) {
				//error(The identifier may only contain letters, numbers, or underscores)
				write("The identifier may only contain letters, numbers, or underscores.", file);
				exit(0);
				return 0;
			}
		}

		return 1;
	}
	else {
		//error (The identifier must start with letter)
		write("The identifier must start with letter.", file);
		exit(0);
		return 0;
	}

}

int isKeyword(char keywords[], char targetWord[], char currentWord[]) { // keyword control method.
	char *ptr = keywords;


	while (1) { // main loop.
		if (*ptr == '\0') return 0; 



		char* cwPtr = currentWord;

		while (*ptr != 32 && *ptr !='\0') { // assignment loop.
			*cwPtr = *ptr;
			cwPtr++;
			ptr++;
		}
		*cwPtr = '\0';
		ptr++;

		int match = 1;

		if (strlen(targetWord) != strlen(currentWord)) { 
			continue; 
		}
		else {
			for (int i = 0; i < strlen(targetWord); i++) {
				if (targetWord[i] != currentWord[i])
				{
					match = 0; // if there is a difference, match is 0.
					break;
				}
			}
		}

		if (match) {
			return 1;
		}


	}
}
