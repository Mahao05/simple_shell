#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_LENGTH 100

typedef struct {
    char name[MAX_ALIAS_LENGTH];
    char value[MAX_ALIAS_LENGTH];
} Alias;

Alias aliases[MAX_ALIAS_COUNT];
int aliasCount = 0;

void printAliases() {
    printf("List of aliases:\n");
    for (int i = 0; i < aliasCount; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void printAlias(char* name) {
    for (int i = 0; i < aliasCount; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
    printf("Alias '%s' not found\n", name);
}

void setAlias(char* name, char* value) {
    for (int i = 0; i < aliasCount; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            strcpy(aliases[i].value, value);
            return;
        }
    }
    if (aliasCount >= MAX_ALIAS_COUNT) {
        printf("Cannot define more aliases. Maximum limit reached.\n");
        return;
    }
    strcpy(aliases[aliasCount].name, name);
    strcpy(aliases[aliasCount].value, value);
    aliasCount++;
    printf("Alias '%s' set to '%s'\n", name, value);
}

void processAliasCommand(int argc, char** argv) {
    if (argc <= 1) {
        printAliases();
    } else if (argc == 2) {
        printAlias(argv[1]);
    } else {
        for (int i = 1; i < argc; i++) {
            char* equalSignIndex = strchr(argv[i], '=');
            if (equalSignIndex == NULL) {
                printAlias(argv[i]);
            } else {
                *equalSignIndex = '\0';
                setAlias(argv[i], equalSignIndex+1);
            }
        }
    }
}

int main(int argc, char** argv) {
    processAliasCommand(argc, argv);
    return 0;
}
