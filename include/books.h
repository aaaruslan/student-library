#ifndef GRAND_TASK_BOOKS_H
#define GRAND_TASK_BOOKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIBRARY_SIZE 1000
#define MAX_ISBN_LENGTH 10
#define MAX_AUTHOR_LENGTH 50
#define MAX_BOOK_NAME_LENGTH 50
#define BOOK_NOT_FOUND -2

typedef struct Book_t {
    int ISBN;
    char *author;
    char *title;
    int total_count;
    int current_count;
} Book;

Book **book_database_initialization(char *filename);

void book_database_free(Book **books);

void books_file_parse(char *filename, Book **books);

void save_books(Book **books, char *filename);

int search_book(Book **books, int ISBN);

void add_book(Book **books);

void view_book(Book **books);

void view_all_books(Book **books);

void edit_book(Book **books);

void change_books_number(Book **books);

#endif //GRAND_TASK_BOOKS_H
