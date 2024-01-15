#include <iostream>
#include "sort_module.h"

void insertionSort(Library &lib) {
    printDivLine();
    if (lib.numberOfBooks == 0) {
        printf("The library is empty!\n");
        return;
    } else if (lib.numberOfBooks == 1) {
        printf("There is only 1 book in the library. No need to sort.\n");
        return;
    }

    printf("[1] - Author\n");
    printf("[2] - Title\n");
    printf("[3] - Year\n");
    printf("[4] - Price\n");
    printf("[5] - Category\n");
    int choice = 0;
    while(true) {
        printf("Enter the number of the field by which you want to sort the library: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("Invalid input. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }

    for (int i = 1; i < lib.numberOfBooks; ++i) {
        Book *keyBook = lib.books[i];
        int j = i - 1;

        switch (choice) {
            case 1:
                while (j >= 0 && strcmp(lib.books[j]->author, keyBook->author) > 0) {
                    lib.books[j + 1] = lib.books[j];
                    --j;
                }
                break;
            case 2:
                while (j >= 0 && strcmp(lib.books[j]->title, keyBook->title) > 0) {
                    lib.books[j + 1] = lib.books[j];
                    --j;
                }
                break;
            case 3:
                while (j >= 0 && lib.books[j]->year > keyBook->year) {
                    lib.books[j + 1] = lib.books[j];
                    --j;
                }
                break;
            case 4:
                while (j >= 0 && lib.books[j]->price > keyBook->price) {
                    lib.books[j + 1] = lib.books[j];
                    --j;
                }
                break;
            case 5:
                while (j >= 0 && strcmp(lib.books[j]->category, keyBook->category) > 0) {
                    lib.books[j + 1] = lib.books[j];
                    --j;
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        lib.books[j + 1] = keyBook;
    }
    printf("Library sorted successfully.\n");
    printDivLine();
}
