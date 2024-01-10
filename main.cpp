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
    do {
        printf("Type 'h' to see all the commands or enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
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
                flushCollection(myLib);
                freeCategories();
                printf("Выход из библиотеки. До свидания!\n");
                break;
            case 'h':
                help();
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != '8');

    return 0;
}
