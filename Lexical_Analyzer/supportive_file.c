#include "lexer.h"

/*To print the data stored in the list*/
void print_lexer(Token **token_table) {

    if (token_table == NULL) return; //exit if the list is empty

    printf("\033[30:1m%-7s%15s%20s\033[0m\n", "Sl.No.", "Token-Types", "Tokens"); //to store the head

    
    for (int i = 0, index = 1; i < MAX_KEYWORDS; i++) {

        if (token_table[i] != NULL) { //if data exests

            printf("%3d    ", index++); //printing the index

            /*Printing the token types*/
            switch(i) { 
                case PREPROCCESSOR: printf("%-20s", "Pre-Proccesser"); break;
                case HEADER: printf("%-20s", "Header file"); break;
                case KEYWORD: printf("%-20s", "Keywords"); break;
                case OPERATOR: printf("%-20s", "Operators"); break;
                case SPECIAL_CHARACTER: printf("%-20s", "Special Character"); break;
                case BRACKETS: printf("%-20s", "Brackets"); break;
                case CONSTANT: printf("%-20s", "Constents"); break;
                case MACRO: printf("%-20s", "Macros"); break;
                case IDENTIFIER: printf("%-20s", "Identifiers"); break;
                case STRING: printf("%-20s", "Strings"); break;
                default: printf("%-20s", "UnKnown");
            }

            Token *head = token_table[i];

            /*Printing the data*/
            while (head) {
                if (head->next) printf("%s\033[30:1m,\033[0m ", head->lexeme);
                else printf("%s", head->lexeme);
                head = head->next;
            }

            printf("\n");
        }
    }

}

/*Inserting the data to list*/
int insert_at_last(Token **head, char *str) {

    Token *temp = *head;
    while (temp) { //if data found in the list, exit
        if (!strcmp(str, temp->lexeme)) return SUCCESS;
        temp = temp->next;
    }

    /*creating the node*/
    Token *new = (Token *) malloc (sizeof(Token));
    if ( new == NULL ) return FAILURE;

    strcpy(new->lexeme, str); //store the commands
    new->next = NULL;

    if ( *head == NULL ) { //if head is empty
        *head = new;
        return SUCCESS;
    }

    temp = *head;

    /*travers till end if the data exests*/
    while ( temp->next != NULL ) temp = temp->next;

    temp->next = new;

    return SUCCESS;

}

/*To remove the multi line and single line commands*/
void remove_comments(char *str) {
    
    int i = 0, j = 0;
    int in_single_comment = 0, in_multi_comment = 0;

    while (str[i]) {
        // Detect `//` single-line comments
        if (!in_multi_comment && str[i] == '/' && str[i + 1] == '/') in_single_comment = 1;

        // Detect `/* */` multi-line comments
        if (!in_single_comment && str[i] == '/' && str[i + 1] == '*') in_multi_comment = 1;

        // End of single-line comment (newline found)
        if (in_single_comment && str[i] == '\n') in_single_comment = 0;

        // End of multi-line comment (`*/` found)
        if (in_multi_comment && str[i] == '*' && str[i + 1] == '/') {
            in_multi_comment = 0;
            i += 2; // Skip `*/`
            continue;
        }

        // Copy only if not in a comment
        if (!in_single_comment && !in_multi_comment) str[j++] = str[i];

        i++;
    }
    
    str[j] = '\0';

    int len = strlen(str);

    // Move backwards to find the last non-space character
    while (len > 0 && isspace((unsigned char)str[len - 1])) len--;

    str[len] = '\0'; // Null-terminate the cleaned string
}