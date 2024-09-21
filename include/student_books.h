#ifndef GRAND_TASK_STUDENT_BOOKS_H
#define GRAND_TASK_STUDENT_BOOKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "students.h"
#include "books.h"

#define MAX_RETURN_DATE_LENGTH 10

typedef struct Student_Book_t {
    int ISBN;
    char *student_number;
    char *return_date;
} Student_book;

Student_book **student_book_database_initialization(char *filename);

void student_books_database_free(Student_book **student_books);

void student_books_file_parse(char *filename, Student_book **student_books);

void save_student_books(Student_book **student_books, char *filename);

int find_students_with_book(Student_book **student_books, int book_number, int start_index);

void delete_book(Book **books, Student_book **student_books);

int find_books_by_student(Student_book **student_books, char *student_number, int start_index);

void delete_student(Student **students, Student_book **student_books);

void count_books_number(Book **books, Student_book **student_books);

void borrow_book(Student **students, Book **books, Student_book **student_books);

void accept_book(Student **students, Book **books, Student_book **student_books);

void all_student_books(Student **students, Book **books, Student_book **student_books);

void students_with_book(Student **students, Book **books, Student_book **student_books);

#endif //GRAND_TASK_STUDENT_BOOKS_H
