#ifndef LIBRARY_MODULE_H
#define LIBRARY_MODULE_H

#include "book_structure.h"
#include <iostream>

struct Library {
    int numberOfBooks;
    int capacity;
    Book** books;
};

void initBooksCollection(Library &lib);

void printTheCollection(const Library &lib);
void printBooksByAuthor(const Library *lib);

void enlargeTheCollection(Library &lib);
void addNewBook(Library &lib, Book* book);
void insertBook(Library &lib, Book* book);

void deleteChoice(Library &lib);
void deleteBook(Library &lib);
void deleteBooksInRange(Library &lib);

void flushTheStruct(Library &lib);
bool isEmpty(const Library &lib);

void saveToFile(const Library &lib);
void printFileError();
int countNumberOfLines(FILE* file);
void loadBookFromFile(Library &lib);
int scanBook(FILE* file, Book &book);

void flushFile();
void flushCollection(Library &lib);

#endif
