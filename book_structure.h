#ifndef BOOK_STRUCTURE_H
#define BOOK_STRUCTURE_H

#define AUTHOR_SIZE 50
#define TITLE_SIZE 50
#define CATEGORY_SIZE 50
#define MAX_CATEGORIES 10
#define MIN_YEAR 751
#define MAX_YEAR 2024

extern char** categoryStrings;
extern int categoryCount;

struct Book {
    char author[AUTHOR_SIZE];
    char title[TITLE_SIZE];
    int year;
    double price;
    const char* category;
};

void printBook(const Book &book);
void initBook(Book &book);
void addCategory(const char* newCategory);
void freeCategories();
void addInitialCategories();

#endif
