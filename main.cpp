#include <iostream>
#include "book_structure.h"
#include "sort_module.h"
#include "library_module.h"
#include "freq_used.h"

struct Book;


int main(int argc, char* argv[]) {

    addInitialCategories();

    Library myLib{};
    initBooksCollection(myLib);

    help();

    char choice[10];

    std::string fileName = (argc > 1) ? argv[1] : "/Users/elhidze/Desktop/Лабы прога/sem1_final/text.txt";

    do {
        printf("Type 'h' to see all the commands or enter your choice: ");

        if (scanf("%9s", choice) != 1) {
            printf("Error reading input. Please input number in range 1-8 or 'h' for help.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (strlen(choice) == 1) {
            switch (choice[0]) {
                case '1':
                    printTheCollection(myLib);
                    break;
                case '2':
                    Book newBook;
                    initBook(newBook);
                    addNewBook(myLib, &newBook);
                    break;
                case '3':
                    deleteChoice(myLib);
                    break;
                case '4':
                    saveToFile(myLib, fileName);
                    break;
                case '5':
                    loadBookFromFile(myLib, fileName);
                    break;
                case '6':
                    insertionSort(myLib);
                    break;
                case '7':
                    printBooksByAuthor(&myLib);
                    break;
                case '8':
                    printf("Exiting.\n");
                    flushCollection(myLib);
                    freeCategories();
                    break;
                case 'h':
                    help();
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        } else {
            printf("Invalid input. Please enter a single character.\n");
        }

    } while (choice[0] != '8');

    return 0;
}
