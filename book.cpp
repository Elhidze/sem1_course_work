#include <iostream>
#include <cstring>
#include "book_structure.h"
#include "freq_used.h"

char** categoryStrings = new char*[MAX_CATEGORIES];
int categoryCount = 0;

void addCategory(const char* newCategory) {
    if (categoryCount < MAX_CATEGORIES - 1) {
        categoryStrings[categoryCount] = strdup(newCategory);

        if (categoryStrings[categoryCount] == nullptr) {
            printf("Failed to allocate memory for the new category.\n");
            return;
        }

        categoryCount++;
        categoryStrings[categoryCount] = nullptr;
        printf("Category '%s' was added successfully.\n", newCategory);
    } else {
        printf("Categories are already full.\n");
    }
}

void freeCategories() {
    for (int i = 0; i < categoryCount; ++i) {
        free(categoryStrings[i]);
    }
    delete[] categoryStrings;
}

void addInitialCategories() {
    addCategory("Programming");
    addCategory("Horror");
    addCategory("Sci-Fi");
}

void printBook(const Book &book) {
    printf("TITLE:\t\t%s\nAUTHOR:\t\t%s\nCATEGORY:\t%s\nRELEASE DATE:\t%d\nPRICE:\t\t%.2lf RUR\n",
           book.title, book.author, book.category, book.year, book.price);
    printDivLine();
}

void initBook(Book &book) {
    char title[TITLE_SIZE];
    while (true) {
        printf("Enter title: ");
        if (scanf("%49s", title) != 1) {
            printf("Input too large. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }
    strcpy(book.title, title);

    char author[AUTHOR_SIZE];
    while (true) {
        printf("Enter author: ");
        if (scanf("%49s", author) != 1) {
            printf("Input too large. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }
    strcpy(book.author, author);

    int year = 0;
    while (true) {
        printf("Enter year: ");
        if (scanf("%d", &year) != 1 || year < 751 || year > 2024) {
            printf("Invalid input. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }
    book.year = year;

    double price = 0.0;
    while (true) {
        printf("Enter price: ");

        if (scanf("%lf", &price) != 1 || price < 0) {
            printf("Invalid input. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }
    book.price = price;


    int categoryID = 0;
    while (true) {
        printDivLine();
        printf("Available categories: ");
        printDivLine();

        for (int i = 0; i < categoryCount; ++i) {
            printf("[%d] - %s\n", (i + 1), categoryStrings[i]);
        }

        printf("[%d] - New Category\n", categoryCount + 1);
        printDivLine();

        printf("Choose category: [1...%d]\n", categoryCount + 1);
        scanf("%d", &categoryID);

        if (categoryID < 1 || categoryID > categoryCount + 1) {
            printf("You've entered a wrong category.\n");
        } else if (categoryID == categoryCount + 1) {
            char newCategoryName[CATEGORY_SIZE];
            while (true) {
                printf("Enter the name for a new category: ");
                if (scanf("%49s", newCategoryName) != 1) {
                    printf("Invalid input. Please try again.\n");
                    fflush(stdin);
                    continue;
                }
                break;
            }
            addCategory(newCategoryName);
            book.category = categoryStrings[categoryCount - 1];
            break;
        } else {
            book.category = categoryStrings[categoryID - 1];
            break;
        }
    }
}
