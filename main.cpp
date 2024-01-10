#include <iostream>
#include "book_structure.h"
#include "sort_module.h"
#include "library_module.h"
#include "freq_used.h"

struct Book;

int main() {

    addInitialCategories();

    Library myLib{};
    initBooksCollection(myLib);

    help();

    char choice;
    char inputBuffer[256];
    int charsConsumed;
    do {
        printf("Type 'h' to see all the commands or enter your choice: ");

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            printf("Error reading input.\n");
            break;
        }

        size_t len = strlen(inputBuffer);
        if (len > 0 && inputBuffer[len - 1] == '\n') {
            inputBuffer[len - 1] = '\0';
        }

        if (strlen(inputBuffer) == 1) {
            sscanf(inputBuffer, "%c", &choice);

            switch (choice) {
                case '1':
                    printf("You chose 1\n");
                    break;
                case '2':
                    printf("You chose 2\n");
                    break;
                case '3':
                    deleteChoice(myLib);
                    break;
                case '4':
                    saveToFile(myLib);
                    break;
                case '5':
                    loadBookFromFile(myLib);
                    break;
                case '6':
                    insertionSort(myLib);
                    break;
                case '7':
                    printBooksByAuthor(&myLib);
                    break;
                case '8':
                    printf("Exiting.\n");
                    break;
                case 'h':
                    printf("Help\n");
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        } else {
            printf("Invalid input. Please enter a single character.\n");
        }
    } while (choice != '8');

    return 0;
}
