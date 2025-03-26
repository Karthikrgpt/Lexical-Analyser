#include "lexer.h"

/*To extract the token line by line*/
int Extract_Token(Token **token_table, const char* filename) {

    fptr = fopen(filename, "r"); //opening the file
    if (fptr == NULL) {
        perror(filename);
        return FAILURE;
    }

    char buffer[BUFSIZ];
    memset(buffer,'\0', BUFSIZ);

    /*Extracting the line and passing for the tokenizetion*/
    while (fscanf(fptr, "%[^\n] ", buffer) == 1) store_token(token_table, buffer);

    fclose(fptr); //closeing the file

    return SUCCESS;
}

/*Tokenizing the string*/
void store_token(Token **token_table, char *str) {

    /*Removing the comments*/
    remove_comments(str);

    /*To store the preprocesser directive and macros*/
    if (isPredirective(token_table, str) == SUCCESS) return;

    /*Need to store the string before tokenizetion because space is present in string*/
    isString(token_table, str);

    /*Get identifiers which present after data types*/
    isIdentifier(token_table, str);

    /*Tokenizing the string*/
    char *token = strtok(str, " ");

    /*Till the token become empty*/
    while (token != NULL) {

        isKeyword(token_table, token); //for the keywords
        isOperator(token_table, token);  //for the operators
        isSpecialCharacter(token_table, token); //for the special character
        isConstant(token_table, token); //for the constants
        isBrackets(token_table, token); //for brackets

        token = strtok(NULL, " ");
    }
}