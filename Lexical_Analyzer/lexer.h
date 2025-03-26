#ifndef LEXER_H
#define LEXER_H

/*Header files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/*Macros*/
#define MAX_KEYWORDS        20
#define MAX_TOKEN_SIZE      100
#define SUCCESS             0
#define FAILURE             -1

/*Enums*/
typedef enum {
    PREPROCCESSOR, //for pre prosesor
    HEADER, //for headeer files
    KEYWORD, //for keywords
    OPERATOR, //for opertors
    SPECIAL_CHARACTER, //for special character
    BRACKETS, //for brackets
    CONSTANT, //for constrants
    MACRO, //for macros
    IDENTIFIER, //for identifiers
    STRING, //for strings
    UNKNOWN //for undefines
} TokenType;

/*List to store the data*/
typedef struct token{
    char lexeme[MAX_TOKEN_SIZE];
    struct token *next;
} Token;

FILE *fptr;

/*key words*/
static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct"
};

/*Pre processores*/
static const char* header[] = {"#include", "#define", "#ifndef", "#endif", "#if", "elif"};

/*Operators*/
static const char* operators = "+-*/%=!<>|&~?:";

/*Brackets*/
static const char* brackets = "{}()[]";

/*Special Characters*/
static const char* specialCharacters = ",;'\"";

/*To verify the file name and arguments*/
int verify_lexer(int argc, char *argv[]);

/*To Extract the token*/
int Extract_Token(Token **token_table, const char* filename);

/*To store the token*/
void store_token(Token **token_table, char *str);

/*To print the data*/
void print_lexer(Token **token_table);

/*for store the pre prossesive directory*/
int isPredirective(Token **token_table, char* str);

/*for store the keywords*/
int isKeyword(Token **token_table, char* str);

/*for store the Operators*/
int isOperator(Token **token_table, char* str);

/*for store the Special characters*/
int isSpecialCharacter(Token **token_table, char* str);

/*for store the constant*/
int isConstant(Token **token_table, char* str);

/*for store the identifiers*/
int isIdentifier(Token **token_table, char* str);

/*for store the brackets*/
int isBrackets(Token **token_table, char* str);

/*for store the strings*/
int isString(Token **token_table, char* str);

/*for store the data to the list*/
int insert_at_last(Token **head, char *str);

/*To remove the commants like single line and multi line*/
void remove_comments(char *str);

#endif
