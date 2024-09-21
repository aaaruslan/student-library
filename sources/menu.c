#include "../include/menu.h"

void main_menu(Student **students, Book **books, Student_book **student_books) {
    enum {
        EXIT = 0,
        BOOK_MENU,
        STUDENT_MENU
    };
    int choice = -1;
    while (choice != EXIT) {
        printf("Main menu\n"
               "1. Books\n"
               "2. Students\n"
               "0. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case BOOK_MENU:
                book_menu(students, books, student_books);
                continue;
            case STUDENT_MENU:
                student_menu(students, books, student_books);
                continue;
            case EXIT:
                break;
            default:
                puts("Wrong choice");
                continue;
        }
    }
}

void book_menu(Student **students, Book **books, Student_book **student_books) {
    enum {
        EXIT = 0,
        ADD_BOOK,
        DELETE_BOOK,
        VIEW_BOOK,
        VIEW_ALL_BOOK,
        EDIT_BOOK,
        COUNT_BOOKS_NUMBER,
        CHANGE_BOOKS_NUMBER,
        BORROW_BOOK,
        ACCEPT_BOOK,
        STUDENTS_WITH_BOOK
    };
    int choice = -1;
    while (choice != 0) {
        printf("Book menu\n"
               "1. Add new book\n"
               "2. Delete book\n"
               "3. View book information\n"
               "4. Display all books\n"
               "5. Edit book\n"
               "6. Count the number of books in the library\n"
               "7. Change the number of books in the library\n"
               "8. Borrow a book\n"
               "9. Accept a book\n"
               "10. View students who took the book\n"
               "0. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case ADD_BOOK:
                add_book(books);
                continue;
            case DELETE_BOOK:
                delete_book(books, student_books);
                continue;
            case VIEW_BOOK:
                view_book(books);
                continue;
            case VIEW_ALL_BOOK:
                view_all_books(books);
                continue;
            case EDIT_BOOK:
                edit_book(books);
                continue;
            case COUNT_BOOKS_NUMBER:
                count_books_number(books, student_books);
                continue;
            case CHANGE_BOOKS_NUMBER:
                change_books_number(books);
                continue;
            case BORROW_BOOK:
                borrow_book(students, books, student_books);
                continue;
            case ACCEPT_BOOK:
                accept_book(students, books, student_books);
                continue;
            case STUDENTS_WITH_BOOK:
                students_with_book(students, books, student_books);
                continue;
            case EXIT:
                break;
            default:
                puts("Wrong choice");
                continue;
        }
    }
}

void student_menu(Student **students, Book **books, Student_book **student_books) {
    enum {
        EXIT = 0,
        ADD_STUDENT,
        DELETE_STUDENT,
        EDIT_STUDENT,
        VIEW_STUDENT,
        LASTNAME_SEARCH,
        ALL_STUDENT_BOOKS
    };
    int choice = -1;
    while (choice != EXIT) {
        printf("Student menu\n"
               "1. Add student\n"
               "2. Delete student\n"
               "3. Edit student\n"
               "4. View student\n"
               "5. Lastname student search\n"
               "6. View all student books\n"
               "0. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case ADD_STUDENT:
                add_student(students);
                continue;
            case DELETE_STUDENT:
                delete_student(students, student_books);
                continue;
            case EDIT_STUDENT:
                edit_student(students);
                continue;
            case VIEW_STUDENT:
                view_student(students);
                continue;
            case LASTNAME_SEARCH:
                lastname_search(students);
                continue;
            case ALL_STUDENT_BOOKS:
                all_student_books(students, books, student_books);
                continue;
            case 0:
                break;
            default:
                puts("Wrong choice");
                continue;
        }
    }
}