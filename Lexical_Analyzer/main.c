#include "lexer.h"

int main(int argc, char *argv[]) {
    
    /*Very the file name*/
    if (verify_lexer(argc, argv) == FAILURE) exit(EXIT_FAILURE);

    /*To store the data*/
    Token *token_table[MAX_KEYWORDS] = {NULL};

    /*Geting the data*/
    if (Extract_Token(token_table, argv[1]) == FAILURE) exit(EXIT_FAILURE);

    /*To print the stored data*/
    print_lexer(token_table);

    return 0;
}

/*Verify the file name and arguments*/
int verify_lexer(int argc, char *argv[]) {

    /*Verify the number of arguments*/
    if (argc != 2) {
        printf("Error: Invaild number of arguments\n");
        printf("Usage: ./output <filename.c>\n");
        return FAILURE;
    } 

    //verify the .c file
    if ( strcmp( argv[1] + (strlen(argv[1]) - 2),".c") != 0 ) {
        printf("Error: %s Invaild .c file\n", argv[1]);
        return FAILURE;
    }

    //check file is existing or not
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        perror(argv[1]);
        return FAILURE;
    }

    fclose(fptr);
}