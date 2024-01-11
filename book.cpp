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
    char *title = NULL;
    size_t titleBuffer = 100;
    size_t titleLen;

    title = (char *) malloc(titleBuffer * sizeof(char));
    while (true) {
        printf("Input title (no more than 50 symbols): ");
        if (fgets(title, (int)titleBuffer, stdin) == NULL) {
            printf("Error reading input.\n");
            break;
        }
        fflush(stdin);

        titleLen = strlen(title);
        if (titleLen > 0 && title[titleLen - 1] == '\n') {
            title[titleLen - 1] = '\0';
            titleLen--;
        }

        if (titleLen > TITLE_SIZE) {
            printf("Input is too large. Please try again.\n");
            titleBuffer += 100;
            title = (char *) realloc(title, titleBuffer * sizeof(char));
        } else {
            break;
        }
    }
    strcpy(book.title, title);
    free(title);

    char *author = NULL;
    size_t authorBuffer = 100;
    size_t authorLen;

    author = (char *) malloc(authorBuffer * sizeof(char));
    while (true) {
        printf("Input author (no more than 50 symbols): ");
        if (fgets(author, (int)authorBuffer, stdin) == NULL) {
            printf("Error reading input. \n");
            break;
        }
        fflush(stdin);

        authorLen = strlen(author);
        if (authorLen > 0 && author[authorLen - 1] == '\n') {
            author[authorLen - 1] = '\0';
            authorLen--;
        }

        if (authorLen > AUTHOR_SIZE) {
            printf("Input is too large. Please try again.\n");
            authorBuffer += 100;
            author = (char *) realloc(author, authorBuffer * sizeof(char));
        } else {
            break;
        }
    }
    strcpy (book.author, author);
    free(author);

//    char title[TITLE_SIZE];
//    while (true) {
//        printf("Enter title: ");
//        if (scanf("%49s", title) != 1) {
//            printf("Input too large. Please try again.\n");
//            fflush(stdin);
//            continue;
//        }
//        break;
//    }
//    strcpy(book.title, title);
//
//    char author[AUTHOR_SIZE];
//    while (true) {
//        printf("Enter author: ");
//        if (scanf("%49s", author) != 1) {
//            printf("Input too large. Please try again.\n");
//            fflush(stdin);
//            continue;
//        }
//        break;
//    }
//    strcpy(book.author, author);

    int year = 0;
    while (true) {
        printf("Enter year (between 751 and 2024): ");
        if (scanf("%d", &year) != 1 || year < 751 || year > 2024) {
            printf("Invalid input. Please try again.\n");
            clearInputBuffer();
            continue;
        }
        break;
    }
    book.year = year;
    clearInputBuffer();

    double price = 0.0;
    while (true) {
        printf("Enter price (>0): ");
        if (scanf("%lf", &price) != 1 || price < 0) {
            printf("Invalid input. Please try again.\n");
            clearInputBuffer();
            continue;
        }
        break;
    }
    book.price = price;
    clearInputBuffer();


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

        while (true) {
            printf("Choose category: [1...%d]\n", categoryCount + 1);
            if (scanf("%d", &categoryID) != 1) {
                printf("Invalid input. Please try again.\n");
                clearInputBuffer();
                continue;
            }
            break;
        }


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
    printf("New book added successfully!\n");
}
