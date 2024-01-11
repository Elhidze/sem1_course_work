#include <iostream>
#include "freq_used.h"
#include "library_module.h"

const int INIT_SIZE = 3;
const char textTxt[] = "/Users/elhidze/Desktop/Лабы прога/sem1_final/text.txt";

void initBooksCollection(Library &lib) {
    lib.numberOfBooks = 0;
    lib.capacity = INIT_SIZE;
    lib.books = new Book*[INIT_SIZE]();
}

void addNewBook(Library &lib, Book* book) {
    if (lib.numberOfBooks <= lib.capacity) {
        insertBook(lib, book);
        if (lib.numberOfBooks == lib.capacity) {
            enlargeTheCollection(lib);
        }
    }
    else {
        enlargeTheCollection(lib);
        insertBook(lib, book);
    }
}

void enlargeTheCollection(Library &lib) {
    Book** tmp = new Book*[lib.capacity];
    int prevCap = lib.capacity;
    int newCapacity = lib.capacity + INIT_SIZE;
    for (int i = 0; i < lib.capacity; i++) {
        tmp[i] = lib.books[i];
    }
    delete[] lib.books;
    lib.books = new Book*[newCapacity];
    lib.capacity = newCapacity;
    for (int i = 0; i < prevCap; i++) {
        lib.books[i] = tmp[i];
    }
}

void insertBook(Library &lib, Book* book) {
    Book* addingThisBook = new Book(*book);
    lib.numberOfBooks++;
    lib.books[lib.numberOfBooks - 1] = addingThisBook;
}

void printTheCollection(const Library &lib) {
    using namespace std;
    if (isEmpty(lib)) {
        cout << "There are no books in the collection!" << endl;
    } else {
        printDivLine();
        cout << "    *** COLLECTION OF BOOKS ***" << endl;
        printDivLine();
        for (int i = 0; i < lib.numberOfBooks; i++) {
            printf("\tBOOK - [%d]\n", i + 1);
            printBook(*lib.books[i]);
        }
        printDivLine();
    }
}

void printBooksByAuthor(const Library *lib) {
    if (lib->numberOfBooks == 0) {
        printf("Library is empty!\n");
        return;
    }

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

    printf("    *** BOOKS BY AUTHOR: %s ***\n", author);

    int found = 0;

    for (int i = 0; i < lib->numberOfBooks; i++) {
        if (strcmp(lib->books[i]->author, author) == 0) {
            printBook(*lib->books[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found by the author: %s\n", author);
    }

    printDivLine();
}

bool isEmpty(const Library &lib) {
    if (lib.numberOfBooks == 0) {
        return true;
    }
    else {
        return false;
    }
}

void deleteChoice(Library &lib) {
    if (lib.numberOfBooks == 0) {
        printf("Library is empty!\n");
        return;
    }
    int choice;
    while (true) {
        printf("Enter '1' if you want to delete one book or '2' if you want to delete books in range: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
            printf("Invalid input. Please try again\n");
            fflush(stdin);
            continue;
        }
        break;
    }

    printTheCollection(lib);
    if (choice == 1) {
        deleteBook(lib);
    } else {
        deleteBooksInRange(lib);
    }

}

void deleteBook(Library &lib) {
    int index;

    while (true) {
        printf("Enter index: ");

        if (scanf("%d", &index) != 1 || index <= 0 || index > lib.numberOfBooks){
            printf("Invalid index. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }
    index--;

    delete lib.books[index];
    for (int i = index; i < lib.numberOfBooks - 1; i++) {
        lib.books[i] = lib.books[i + 1];
    }
    lib.numberOfBooks--;
    printf("Book deleted successfully!\n");
}

void deleteBooksInRange(Library &lib) {
    int start, end;
    while (true) {
        printf("Enter range - two integers separated by space: ");

        if (scanf("%d %d", &start, &end) != 2 || start <= 0 || start > end || start > lib.numberOfBooks || end <= 0 || end > lib.numberOfBooks) {
            printf("Invalid range. Please try again.\n");
            fflush(stdin);
            continue;
        }
        break;
    }

    start--;
    end--;

    for (int i = start; i <= end; i++) {
        delete lib.books[i];
    }
    for (int i = start; i < lib.numberOfBooks - (end - start + 1); i++) {
        lib.books[i] = lib.books[i + (end - start + 1)];
    }
    lib.numberOfBooks -= (end - start + 1);
    printf("Books deleted successfully!\n");
}

void flushTheStruct(Library &lib) {
    for (int i = 0; i < lib.numberOfBooks; i++) {
        delete lib.books[i];
    }
    lib.capacity = INIT_SIZE;
    lib.numberOfBooks = 0;
    delete[] lib.books;
}

void saveToFile(const Library &lib, const std::string &fileName) {
    if (isEmpty(lib)) {
        printf("Library is empty!\n");
        return;
    }

    FILE *file = fopen(fileName.c_str(), "a");
    if (!file) {
        printf("ERROR: Couldn't open the file.\n");
        return;
    }

    for (int i = 0; i < lib.numberOfBooks; i++) {
        Book book = *lib.books[i];
        fprintf(file, "%s %s %d %.2lf %s\n", book.author, book.title, book.year, book.price, book.category);
    }

    fclose(file);
    printf("Save successful.\n");
}

void loadBookFromFile(Library &lib, const std::string &fileName) {
    FILE *file = fopen(fileName.c_str(), "r");
    if (!file) {
        printf("ERROR: Couldn't open the file.\n");
        printf("Using the default file instead.\n");
        return;
    }

    while (true) {
        Book *book = new Book();
        int result = scanBook(file, *book);

        if (result == 1) {
            addNewBook(lib, book);
            continue;
        } else {
            delete book;
            printf("All books added from file.\n");
            break;
        }
    }

    if (fclose(file) == EOF) {
        printf("ERROR: Couldn't close the file.\n");
    }
}

int scanBook(FILE* file, Book &book) {
    const int bufferSize = 256;
    char buffer[bufferSize];

    int result = fscanf(file, "%s %s %d %lf", book.author, book.title, &book.year, &book.price);

    if (result != 4) {
        //ошибка при чтении
        return 0;
    }

    result = fscanf(file, " %255[^\n]", buffer);

    if (result != 1) {
        return 0;
    }

    book.category = strdup(buffer);

    if (book.category == nullptr) {
        return 0;
    }

    return 1;
}

int countNumberOfLines(FILE* file) {
    unsigned int numberOfLines = 0;
    char ch;
    while (EOF != (ch = getc(file))) {
        if (ch == '\n')
            numberOfLines++;
    }
    fclose(file);
    return numberOfLines;
}

void printFileError() {
    puts("ERROR: Couldn't open the file!\n");
}

void flushFile() {
    FILE* file = fopen(textTxt, "w");
    if (file) {
        fflush(file);
        fclose(file);
    }
}

void flushCollection(Library &lib) {
    lib.capacity = INIT_SIZE;
    lib.numberOfBooks = 0;
    delete[] lib.books;
    lib.books = new Book*[lib.capacity];
}
