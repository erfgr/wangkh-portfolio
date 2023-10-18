#include <stdio.h>
#include <string.h>

#define INDENT_SIZE 4

enum STATEMENT{
    FOR, IF, WHILE, ELSE, OTHERS, CLOSE_BRACE, ELSEIF
};

void printIndent(int n) {
    for(int i = 0; i < n; i++) {
        printf(" ");
    }
}

// Skip leading spaces
void removeLeadingSpaces(char *str){
    char buffer[80] = "";
    strcpy(buffer, str);
    int idx = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] != ' ') {
            idx = i;
            break;
        }
    }
    strcpy(str, buffer+idx);
}

enum STATEMENT checkStatement(char *line){
    char buffer[80] = "";
    strncpy(buffer, line, 1);
    if(strcmp(buffer, "}") == 0) {
        return CLOSE_BRACE;
    }
    strncpy(buffer, line, 2);
    if(strcmp(buffer, "if") == 0) {
        return IF;
    }
    strncpy(buffer, line, 3);
    if(strcmp(buffer, "for") == 0) {
        return FOR;
    }
    strncpy(buffer, line, 4);
    if(strcmp(buffer, "else") == 0) {
        return ELSE;
    }
    strncpy(buffer, line, 5);
    if(strcmp(buffer, "while") == 0) {
        return WHILE;
    }
    strncpy(buffer, line, 7);
    if(strcmp(buffer, "else if") == 0) {
        return ELSEIF;
    }
    return OTHERS;
}


void removeOpenBrace(char *line){
    int len = strlen(line);
    char buffer[80] = "";
    strcpy(buffer, line);
    int ptr = 0;
    int found = 0;
    for(int i = len - 1; i >=0; i--){
        if(line[i] != '{' && line[i] != ' ') {
            ptr = i;
            break;
        }
    }
    memset(line, '\0', strlen(buffer));
    strncpy(line, buffer, ptr+1);
}


int main(){
    int line_of_code = 0;
    char line[80] = "";
    char buffer[80] = "";
    const char semicolon[2] = ";";

    scanf("%d\n", &line_of_code);

    int indent = 0;
    while(line_of_code--) {
        gets(line);
        removeLeadingSpaces(line);
        enum STATEMENT statement = checkStatement(line);
        if(statement == FOR || statement == IF || statement == WHILE ||
           statement == ELSE || statement == ELSEIF) {
            removeOpenBrace(line);
            printIndent(indent);
            printf("%s {\n", line);
            indent += INDENT_SIZE;
        }
        else if(statement == CLOSE_BRACE){
            indent -= INDENT_SIZE;
            printIndent(indent);
            printf("}\n");
        }
        else if(statement == OTHERS){
            char *token = strtok(line, semicolon);
            while(token != NULL) {
                removeLeadingSpaces(token);
                printIndent(indent);
                printf("%s;\n", token);
                token = strtok(NULL, semicolon);
            }
        }
    }
    return 0;
}
