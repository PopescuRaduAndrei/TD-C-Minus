// C-Minus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <symbols.h>
#include <errno.h>

extern FILE* yyin;
extern int yylex(void);

int main()
{
	const char* lexUnits[] = {
	"END",
	"INT",
	"LONG",
	"DOUBLE",
	"SHORT",
	"UNSIGNED",
	"VOID",
	"VOLATILE",
	"WHILE",
	"FLOAT",
	"IF",
	"ELSE", 
	"RETURN",
	"CONSTANT", 
	"STRING_LITERAL", 
	"ASSIGN", 
	"ADD", 
	"SUBSTRACT", 
	"IDENTIFIER", 
	"END_OF_INSTRUCTION",
	"EQUAL", 
	"NOTEQUAL", 
	"LOWER",
	"LOWEROREQUAL", 
	"GREATER", 
	"GREATEROREQUAL", 
	"MULTIPLY", 
	"DIVIDE", 
	"LPAREN", 
	"RPAREN", 
	"LBRACKET", 
	"RBRACKET", 
	"LBRACE", 
	"RBRACE", 
	"COMMA", 
	"NUM" 
	};

	int tokenValue = 0;
	yyin = fopen("input.csrc", "rt");

	if (yyin != NULL) {
		while ((tokenValue = yylex()) != END) {
			printf(" -> TOKEN ID: %d; TOKEN VALUE: %s \n", tokenValue, lexUnits[tokenValue]);
		}
	}
	else {
		printf("Fisierul de intrare nu poate fi deschis. Erorare: %d", errno);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
