#include "include/students.h"
#include "include/books.h"
#include "include/student_books.h"
#include "include/users.h"
#include "include/menu.h"

#define STUDENTS_DATA "../data/students.csv"
#define BOOKS_DATA "../data/books.csv"
#define STUDENT_BOOKS_DATA "../data/student_books.csv"
#define USERS_DATA "../data/users.csv"

enum {
    SUCCESS = 0,
    AUTHORIZATION_ERROR
};

int main() {
    Student **student_database = student_database_initialization(STUDENTS_DATA);
    User **user_database = user_database_initialization(USERS_DATA);
    Book **book_database = book_database_initialization(BOOKS_DATA);
    Student_book **student_book_database = student_book_database_initialization(STUDENT_BOOKS_DATA);

    int user_rights = authorization(user_database);
    //Passwords: admin - admin / students - students / books - books / user - noaccess
    if (user_rights == NO_ACCESS) {
        puts("You don't have any rights");
        return SUCCESS;
    } else if (user_rights == STUDENTS_DATABASE_ACCESS) {
        puts("You have an access to the students database");
        student_menu(student_database, book_database, student_book_database);
    } else if (user_rights == BOOKS_DATABASE_ACCESS) {
        puts("You have an access to the books database");
        book_menu(student_database, book_database, student_book_database);
    } else if (user_rights == STUDENTS_AND_BOOKS_DATABASES_ACCESS) {
        puts("You have an access to both students and books databases");
        main_menu(student_database, book_database, student_book_database);
    } else {
        puts("The user is not found");
        return AUTHORIZATION_ERROR;
    }

    save_students(student_database, STUDENTS_DATA);
    save_books(book_database, BOOKS_DATA);
    save_student_books(student_book_database, STUDENT_BOOKS_DATA);
    user_database_free(user_database);
    return SUCCESS;
}
