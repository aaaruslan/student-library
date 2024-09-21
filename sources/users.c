#include "../include/users.h"

User **user_database_initialization(char *filename) {
    User **users = malloc(MAX_USERS_NUMBER * sizeof(User *));
    if (users == NULL)
        return NULL;

    for (int i = 0; i < MAX_USERS_NUMBER; i++) {
        users[i] = malloc(sizeof(User));
        users[i]->login = malloc(MAX_LOGIN_LENGTH * sizeof(char));
        strcpy(users[i]->login, "");
        users[i]->hash_password = malloc(MAX_PASSWORD_LENGTH * sizeof(char));
        strcpy(users[i]->hash_password, "");
        users[i]->student_access = -1;
        users[i]->book_access = -1;
    }
    users_file_parse(filename, users);
    return users;
}

void user_database_free(User **users) {
    if (users != NULL) {
        for (int i = 0; i < MAX_USERS_NUMBER; i++) {
            if (users[i] != NULL) {
                free(users[i]->login);
                free(users[i]->hash_password);
                free(users[i]);
            }
        }
        free(users);
    }
}

void users_file_parse(char *filename, User **users) {
    FILE *users_file = fopen(filename, "r");
    if (users_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    int max_string_size = MAX_LOGIN_LENGTH + MAX_HASH_LENGTH + 3 + 2;

    char *string = malloc(max_string_size * sizeof(char));

    int number_of_users = 0;
    while (fgets(string, max_string_size, users_file)) {
        if (number_of_users >= MAX_USERS_NUMBER) {
            break;
        }

        strcpy(users[number_of_users]->login, strtok(string, ","));
        strcpy(users[number_of_users]->hash_password, strtok(NULL, ","));
        users[number_of_users]->student_access = atoi(strtok(NULL, ","));
        users[number_of_users]->book_access = atoi(strtok(NULL, "\n"));

        number_of_users++;
    }

    free(string);
    fclose(users_file);
}

int authorization(User **users) {
    char login[MAX_LOGIN_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login:\n");
    scanf("%s", login);

    printf("Password:\n");
    scanf("%s", password);

    uint8_t hash[MAX_HASH_LENGTH];
    calc_sha_256(hash, password, strlen(password));

    char char_hash[MAX_PASSWORD_LENGTH * 2 + 1];
    for (int i = 0; i < MAX_HASH_LENGTH; i++) {
        sprintf(char_hash + (i * 2), "%02x", hash[i]);
    }

    for (int i = 0; i < MAX_USERS_NUMBER; i++) {
        if (users[i] != NULL &&
            strcmp(users[i]->login, login) == 0 &&
            strcmp(users[i]->hash_password, char_hash) == 0) {

            printf("Welcome %s\n", login);

            int rights = 0;
            if (users[i]->student_access == 0 && users[i]->book_access == 0)
                rights = NO_ACCESS;
            else if (users[i]->student_access == 1 && users[i]->book_access == 0)
                rights = STUDENTS_DATABASE_ACCESS;
            else if (users[i]->student_access == 0 && users[i]->book_access == 1)
                rights = BOOKS_DATABASE_ACCESS;
            else if (users[i]->student_access == 1 && users[i]->book_access == 1)
                rights = STUDENTS_AND_BOOKS_DATABASES_ACCESS;

            return rights;
        }
    }
}
