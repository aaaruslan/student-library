#ifndef GRAND_TASK_USERS_H
#define GRAND_TASK_USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha_256.h"

#define MAX_USERS_NUMBER 50
#define MAX_LOGIN_LENGTH 100
#define MAX_HASH_LENGTH 32
#define MAX_PASSWORD_LENGTH 100

enum {
    NO_ACCESS = 2,
    STUDENTS_DATABASE_ACCESS,
    BOOKS_DATABASE_ACCESS,
    STUDENTS_AND_BOOKS_DATABASES_ACCESS
};

typedef struct User_t {
    char *login;
    char *hash_password;
    int student_access;
    int book_access;
} User;

User **user_database_initialization(char *filename);

void user_database_free(User **users);

void users_file_parse(char *filename, User **users);

int authorization(User **users);

#endif //GRAND_TASK_USERS_H
