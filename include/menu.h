#ifndef GRAND_TASK_MENU_H
#define GRAND_TASK_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_books.h"

void main_menu(Student **students, Book **books, Student_book **student_books);

void book_menu(Student **students, Book **books, Student_book **student_books);

void student_menu(Student **students, Book **books, Student_book **student_books);

#endif //GRAND_TASK_MENU_H
