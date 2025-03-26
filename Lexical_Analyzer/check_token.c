#include "lexer.h"

/*for the pre processer directive*/
int isPredirective(Token **token_table, char* str) {

    if (str[0] != '#') return FAILURE; //checking the pre processer

    for (int i = 0; header[i]; i++) {

        /*checking the presence of the preprocesser*/
        if (strstr(str, header[i]) != NULL) {

            /*storeing the preprocessser*/
            insert_at_last(&token_table[PREPROCCESSOR], (char *)header[i] );

            /*if space is present*/
            if (strchr(str, ' ') != NULL) {

                /*geting the tokens*/
                char *token = strtok(str, " ");

                while (token != NULL) {

                    /*Storing the data*/
                    if (isdigit(token[0])) insert_at_last(&token_table[CONSTANT], token);
                    else if (strchr(token, '<') != NULL) insert_at_last(&token_table[HEADER], token);
                    else if (strchr(token, '"') != NULL) insert_at_last(&token_table[HEADER], token);
                    else if (token[0] != '#') insert_at_last(&token_table[MACRO], token);

                    /*for next token*/
                    token = strtok(NULL, " ");
                }

            } else {
                /*if space is not present*/
                if (strchr(str + strlen(header[i]), '<') != NULL) insert_at_last(&token_table[HEADER], str + strlen(header[i]));
                else if (strchr(str + strlen(header[i]), '"') != NULL) insert_at_last(&token_table[HEADER], str + strlen(header[i]));
            }

            return SUCCESS;
        }
    }

    return FAILURE;

}

/*for the keywords*/
int isKeyword(Token **token_table, char* str) {

    for (int i = 0; keywords[i]; i++) {
        if (!strcmp(keywords[i], str)) { //checking for the presents of keywords
            insert_at_last(&token_table[KEYWORD], str); //storing the keywords
            return SUCCESS;
        }
    }

    return FAILURE;
}

/*For operators*/
int isOperator(Token **token_table, char* str) {

    int flag = 0;
    for (int i = 0; str[i]; i++)
        if (strchr(operators, str[i]) != NULL) flag = 1; //checking for the presencs of keywords
    if (!flag) return FAILURE;

    char *ch;

    for (int i = 0; operators[i]; i++) {

        ch = strchr(str, operators[i]);
        if ( ch != NULL) { //checking for the presencs of keywords
            char temp[25]; //create the copy
            strcpy(temp, ch);

            if ( strchr(operators, temp[1]) != NULL && strchr(operators, temp[2]) != NULL) temp[3] = '\0'; //to store a multi operator like >>= etc..
            else if ( strchr(operators, temp[1]) != NULL) temp[2] = '\0'; //to store a multi operator like += >> etc..
            else temp[1] = '\0'; //to store a single opperator like + = - etc..
            
            insert_at_last(&token_table[OPERATOR], temp); //storing the data
        }
    }

    return SUCCESS;
}

/*for the special characters*/
int isSpecialCharacter(Token **token_table, char* str) {

    int flag = 0;

    for (int i = 0; str[i]; i++)
        if (strchr(specialCharacters, str[i]) != NULL) flag = 1; //checking for the presents of special characters

    if (!flag) return FAILURE;

    for (int i = 0; str[i] ; i++) {

        //storing the special characters
        switch (str[i]) {
            case ',': insert_at_last(&token_table[SPECIAL_CHARACTER], ","); break;
            case ';': insert_at_last(&token_table[SPECIAL_CHARACTER], ";"); break;
            case '\'': insert_at_last(&token_table[SPECIAL_CHARACTER], "'"); break;
            case '"': insert_at_last(&token_table[SPECIAL_CHARACTER], "\""); break;
        }
    }

    return SUCCESS;
}

/*for constents*/
int isConstant(Token **token_table, char* str) {

    int flag = 0;

    for (int i = 0; str[i]; i++) {
        if (isdigit(str[i])) flag = 1; //checking for presence of constents
    }
    if (!flag) return FAILURE;

    char temp_str[100];
    int j = 0;

    /*storing only digits, dot*/
    for (int i = 0; str[i]; i++) if (!isalpha(str[i])) temp_str[j++] = str[i];
    temp_str[j] = '\0';

    char temp[25];
    int c_flag = 0;
    j = 0;
    
    /*Estracting the digits and dot and storing it*/
    for (int i = 0; temp_str[i]; i++) {
            
        if ((isdigit(temp_str[i]) || temp_str[i] == '.') && !isalpha(temp_str[i])) temp[j++] = temp_str[i];
        if (strchr(operators, temp_str[i]) != NULL ) c_flag = 1; //if operators are present then breking the command, storing it and angain contiue this

        if (c_flag) {
            temp[j] = '\0'; //termiante with null
            j = 0;
            c_flag = 0; //make as zero for next constent
            if (temp[0]) insert_at_last(&token_table[CONSTANT], temp); //store
        }
    }

    temp[j] = '\0';
    if (temp[0]) insert_at_last(&token_table[CONSTANT], temp); //store if there is any constent

    return SUCCESS;
}

/*For identifiers*/
int isIdentifier(Token **token_table, char* str) {

    char* datatypes[] = { "int", "float", "char", "double", "void", NULL};

    int flag = 0;
    for (int i = 0; datatypes[i]; i++) 
        if (strstr(str, datatypes[i]) != NULL && str[0] == datatypes[i][0]) flag = 1; //checking for the presnts

    if (flag == 0) return FAILURE;

    char identifiers[50];
    char temp[50];
    strcpy(temp, str);

    /*geting the identifres*/
    for (int i = 0; datatypes[i]; i++) {
        if (strstr(temp, datatypes[i]) != NULL) {
            int len = strlen(datatypes[i]);
            char *pos;
            /*removing the datatypes*/
            while ((pos = strstr(temp, datatypes[i])) != NULL) {
                memmove(pos, pos + len, strlen(pos + len) + 1);
            }
        }
    }
    
    int i = 0;

    /*for multiple identifires*/
    while (temp[i]) {

        if (isalpha(temp[i]) || temp[i] == '_') { // Start of an identifier
        
            int j = 0;
            /*geting the identifers*/
            while (isalnum(temp[i]) || temp[i] == '_') identifiers[j++] = temp[i++];
            identifiers[j] = '\0'; 
            insert_at_last(&token_table[IDENTIFIER], identifiers); //store the identifers
        
        } else {
            i++;
        }
    }

    return FAILURE;
}

/*for brackets*/
int isBrackets(Token **token_table, char* str) {

    int flag = 0;

    for (int i = 0; str[i]; i++)
        if (strchr(brackets, str[i]) != NULL) flag = 1; //cheking the presents of bracket

    if (!flag) return FAILURE;

    for (int i = 0; str[i] ; i++) {

        /*if bracket found storeing the data*/
        switch (str[i]) {
            case '(': insert_at_last(&token_table[BRACKETS], "("); break;
            case ')': insert_at_last(&token_table[BRACKETS], ")"); break;
            case '{': insert_at_last(&token_table[BRACKETS], "{"); break;
            case '}': insert_at_last(&token_table[BRACKETS], "}"); break;
            case '[': insert_at_last(&token_table[BRACKETS], "["); break;
            case ']': insert_at_last(&token_table[BRACKETS], "]"); break;
        }
    }

    return SUCCESS;
}

/*for string*/
int isString(Token **token_table, char* str) {

    if (strchr(str, '"') == NULL) return FAILURE; //cheking the presence of string

    char *start = strchr(str, '"'); //geting the address of strting of string
    char sub_string[100];
    memset(sub_string, '\0', 100);
    int len = strlen(start);

    /*Get the string form  ending " to ending "*/
    for (int i = len - 1, flag = 0; i >= 0; i--) {
        if (start[i] == '"') flag = 1;
        if (flag) sub_string[i] = start[i]; //store till end
    }

    insert_at_last(&token_table[STRING], sub_string); //insert the strimng

    len = strlen(sub_string);
    memmove(start, start + len, strlen(start + len) + 1); //to remove the sub-string fome string

    return SUCCESS;
}