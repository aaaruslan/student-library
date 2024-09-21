#include "../include/books.h"

Book **book_database_initialization(char *filename) {
    Book **books = malloc(MAX_LIBRARY_SIZE * sizeof(Book *));
    if (books == NULL)
        return NULL;

    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        books[i] = malloc(sizeof(Book));
        books[i]->ISBN = -1;
        books[i]->author = malloc(MAX_AUTHOR_LENGTH * sizeof(char));
        strcpy(books[i]->author, "");
        books[i]->title = malloc(MAX_BOOK_NAME_LENGTH * sizeof(char));
        strcpy(books[i]->title, "");
        books[i]->total_count = -1;
        books[i]->current_count = -1;
    }
    books_file_parse(filename, books);
    return books;
}

void book_database_free(Book **books) {
    if (books != NULL) {
        for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
            if (books[i] != NULL) {
                free(books[i]->author);
                free(books[i]->title);
                free(books[i]);
            }
        }
        free(books);
    }
}

void books_file_parse(char *filename, Book **books) {
    FILE *books_file = fopen(filename, "r");
    if (books_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    int max_string_size = MAX_ISBN_LENGTH + MAX_AUTHOR_LENGTH + MAX_BOOK_NAME_LENGTH + 100 + 4;
    char *string = malloc(max_string_size * sizeof(char));

    int number_of_books = 0;
    while (fgets(string, max_string_size, books_file) != NULL) {
        if (number_of_books >= MAX_LIBRARY_SIZE) {
            break;
        }

        books[number_of_books]->ISBN = atoi(strtok(string, ","));
        strcpy(books[number_of_books]->author, strtok(NULL, ","));
        strcpy(books[number_of_books]->title, strtok(NULL, ","));
        books[number_of_books]->total_count = atoi(strtok(NULL, ","));
        books[number_of_books]->current_count = atoi(strtok(NULL, "\n"));

        number_of_books++;
    }

    free(string);
    fclose(books_file);
}


void save_books(Book **books, char *filename) {
    FILE *books_file = fopen(filename, "w");
    if (books_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        if (books[i]->ISBN != -1 && i == 0) {
            fprintf(books_file, "%d,%s,%s,%d,%d", books[i]->ISBN, books[i]->author, books[i]->title,
                    books[i]->total_count, books[i]->current_count);
        } else if (books[i]->ISBN != -1) {
            fprintf(books_file, "\n%d,%s,%s,%d,%d", books[i]->ISBN, books[i]->author, books[i]->title,
                    books[i]->total_count, books[i]->current_count);
        } else break;
    }

    fclose(books_file);
    book_database_free(books);
}

int search_book(Book **books, int ISBN) {
    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        if (books[i]->ISBN == ISBN)
            return i;
    }
    return BOOK_NOT_FOUND;
}

void add_book(Book **books) {
    int ISBN;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    if (search_book(books, ISBN) != BOOK_NOT_FOUND) {
        fprintf(stderr, "The book with this number is already in the library\n");
        return;
    }

    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        if (books[i]->ISBN == -1) {
            books[i]->ISBN = ISBN;
            printf("Enter book author:\n");
            scanf(" %[^\n]", books[i]->author);
            printf("Enter book title:\n");
            scanf(" %[^\n]", books[i]->title);
            printf("Enter the total number of books:\n");
            scanf("%d", &books[i]->total_count);
            printf("Enter the available number of books:\n");
            scanf("%d", &books[i]->current_count);
            return;
        }
    }

    fprintf(stderr, "The database is full\n");
}

void view_book(Book **books) {
    int ISBN;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    } else {
        puts("-----------------------------------------------------------------------");
        printf("Book\n"
               "Author: %s\n"
               "Title: %s\n"
               "Total count: %d\n"
               "Current count: %d\n", books[book_index]->author, books[book_index]->title,
               books[book_index]->total_count, books[book_index]->current_count);
        puts("-----------------------------------------------------------------------");
    }
}

void view_all_books(Book **books) {
    int count_book = 0;
    while (books[count_book]->ISBN != -1) {
        count_book++;
    }

    for (int i = 0; i < count_book - 1; i++) {
        for (int j = 0; j < count_book - i - 1; j++) {
            if (books[j]->ISBN > books[j + 1]->ISBN) {
                Book *temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    puts("-----------------------------------------------------------------------");
    puts("Book list");
    for (int i = 0; i < count_book; i++) {
        printf("%d %19s %19s %3d %3d\n", books[i]->ISBN, books[i]->author,
               books[i]->title, books[i]->total_count, books[i]->current_count);
    }
    puts("-----------------------------------------------------------------------");
}

void edit_book(Book **books) {
    int ISBN;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);
    getchar();

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    } else {
        puts("Enter book author:");
        scanf("%[^\n]", books[book_index]->author);
        getchar();
        puts("Enter book title:");
        scanf("%[^\n]", books[book_index]->title);
        getchar();
    }
}

void change_books_number(Book **books) {
    int ISBN;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    }

    int new_books_number;
    puts("Enter the new number of books:");
    scanf("%d", &new_books_number);
    int books_number_difference = books[book_index]->total_count - books[book_index]->current_count;
    if (new_books_number >= books_number_difference) {
        books[book_index]->total_count = new_books_number;
        books[book_index]->current_count = new_books_number - books_number_difference;
    } else
        fprintf(stderr, "There are %d books were taken."
                        "You cannot change the number of books below this number.\n", books_number_difference);
}

