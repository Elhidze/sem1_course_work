#include <iostream>
#include "freq_used.h"

using namespace std;

void printDivLine() {
    printf("----------------------------------------------------\n");
}

void printUserInvitation() {
    printf("user > ");
}

void printUserInvitation(char* string) {
    printf("user/%s > ", string);
}

void help() {
    printDivLine();
    printf("HELP\n");
    printDivLine();
    printf("[1] - PRINT the collection;\n");
    printf("[2] - ADD new book;\n");
    printf("[3] - DELETE one book or books in range;\n");
    printf("[4] - SAVE to the file;\n");
    printf("[5] - LOAD books from file;\n");
    printf("[6] - SORT books;\n");
    printf("[7] - Find books by author;\n");
    printDivLine();
    printf("[8] - Exit;\n");
    printDivLine();
}