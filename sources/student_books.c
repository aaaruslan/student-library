#include "../include/student_books.h"

Student_book **student_book_database_initialization(char *filename) {
    Student_book **student_books = malloc(MAX_LIBRARY_SIZE * sizeof(Student_book *));
    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        student_books[i] = malloc(sizeof(Student_book));
        student_books[i]->ISBN = -1;
        student_books[i]->student_number = malloc(MAX_STUDENT_NUMBER_LENGTH * sizeof(char));
        strcpy(student_books[i]->student_number, "");
        student_books[i]->return_date = malloc(MAX_RETURN_DATE_LENGTH * sizeof(char));
        strcpy(student_books[i]->return_date, "");
    }
    student_books_file_parse(filename, student_books);
    return student_books;
}

void student_books_database_free(Student_book **student_books) {
    if (student_books != NULL) {
        for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
            if (student_books[i] != NULL) {
                free(student_books[i]->student_number);
                free(student_books[i]->return_date);
                free(student_books[i]);
            }
        }
        free(student_books);
    }
}

void student_books_file_parse(char *filename, Student_book **student_books) {
    FILE *student_books_file = fopen(filename, "r");
    if (student_books_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    int max_string_size = MAX_ISBN_LENGTH + MAX_STUDENT_NUMBER_LENGTH + MAX_RETURN_DATE_LENGTH + 2;

    char *string = malloc(max_string_size * sizeof(char));

    int number_of_student_books = 0;
    while (fgets(string, max_string_size, student_books_file) != NULL) {
        if (number_of_student_books >= MAX_LIBRARY_SIZE) {
            break;
        }

        student_books[number_of_student_books]->ISBN = strtol(strtok(string, ","), NULL, 10);
        strcpy(student_books[number_of_student_books]->student_number, strtok(NULL, ","));
        strcpy(student_books[number_of_student_books]->return_date, strtok(NULL, "\n"));

        number_of_student_books++;
    }

    free(string);
    fclose(student_books_file);
}

void save_student_books(Student_book **student_books, char *filename) {
    FILE *student_books_file = fopen(filename, "w");
    if (student_books_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        if (student_books[i]->ISBN != -1 && i == 0) {
            fprintf(student_books_file, "%d,%s,%s", student_books[i]->ISBN,
                    student_books[i]->student_number, student_books[i]->return_date);
        } else if (student_books[i]->ISBN != -1) {
            fprintf(student_books_file, "\n%d,%s,%s", student_books[i]->ISBN,
                    student_books[i]->student_number, student_books[i]->return_date);
        }
    }

    fclose(student_books_file);
    student_books_database_free(student_books);
}

int find_students_with_book(Student_book **student_books, int book_number, int start_index) {
    for (int student_index = start_index; student_index < MAX_LIBRARY_SIZE; student_index++) {
        if (student_books[student_index]->ISBN == book_number)
            return student_index;
        else if (student_books[student_index]->ISBN == -1)
            return STUDENT_NOT_FOUND;
    }
    return STUDENT_NOT_FOUND;
}

void delete_book(Book **books, Student_book **student_books) {
    int ISBN;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    } else if (find_students_with_book(student_books, ISBN, 0) != STUDENT_NOT_FOUND) {
        fprintf(stderr, "You can't delete a book that is owned by students\n");
        return;
    }

    for (int i = book_index; i < MAX_LIBRARY_SIZE - 1; i++) {
        books[i] = books[i + 1];
    }
    books[MAX_LIBRARY_SIZE - 1] = NULL;
}


int find_books_by_student(Student_book **student_books, char *student_number, int start_index) {
    for (int book_index = start_index; book_index < MAX_LIBRARY_SIZE; book_index++) {
        if (strcmp(student_books[book_index]->student_number, student_number) == 0) return book_index;
        else if (student_books[book_index]->ISBN == -1) return BOOK_NOT_FOUND;
    }
    return BOOK_NOT_FOUND;
}

void delete_student(Student **students, Student_book **student_books) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number:");
    scanf("%s", student_number);

    int student_index = search_student(students, student_number);

    if (student_index == STUDENT_NOT_FOUND) {
        fprintf(stderr, "There is no student with this number\n");
        return;
    } else if (find_books_by_student(student_books, student_number, 0) != BOOK_NOT_FOUND) {
        fprintf(stderr, "You can't delete a student who has books\n");
        return;
    }


    for (int i = student_index; i < MAX_STUDENTS_NUMBER - 1; i++) {
        students[i] = students[i + 1];
    }
    students[MAX_STUDENTS_NUMBER - 1] = NULL;
}


void count_books_number(Book **books, Student_book **student_books) {
    int ISBN, count = 0;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    }

    for (int i = 0; i < MAX_LIBRARY_SIZE; i++)
        if (student_books[i]->ISBN == ISBN)
            count++;

    books[book_index]->current_count = books[book_index]->total_count - count;
    printf("There are %d books available in the library\n", books[book_index]->current_count);
}

void borrow_book(Student **students, Book **books, Student_book **student_books) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number:");
    scanf("%s", student_number);

    if (search_student(students, student_number) == STUDENT_NOT_FOUND) {
        fprintf(stderr, "There is no student with this number\n");
        return;
    }

    char input_ISBN[MAX_ISBN_LENGTH];
    puts("Enter the ISBN number:");
    scanf("%s", input_ISBN);
    int ISBN = atoi(input_ISBN);

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    } else if (books[book_index]->current_count == 0) {
        fprintf(stderr, "There are no books available in the library\n");
        return;
    }

    char return_date[MAX_RETURN_DATE_LENGTH];
    puts("Enter the return date (dd.mm.yy):");
    scanf("%s", return_date);

    int available_index = -1;
    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        if (available_index == -1 && student_books[i]->ISBN == -1) {
            available_index = i;
        }
    }

    if (available_index == -1) {
        fprintf(stderr, "The library is full\n");
        return;
    }

    student_books[available_index]->ISBN = ISBN;
    strcpy(student_books[available_index]->student_number, student_number);
    strcpy(student_books[available_index]->return_date, return_date);
    books[book_index]->current_count--;
}

void accept_book(Student **students, Book **books, Student_book **student_books) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number:");
    scanf("%s", student_number);

    int student_index = search_student(students, student_number);
    if (student_index == STUDENT_NOT_FOUND) {
        fprintf(stderr, "There is no student with this number\n");
        return;
    }

    int ISBN;
    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    int book_index = search_book(books, ISBN);

    if (book_index == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    }

    if (books[book_index]->current_count == books[book_index]->total_count) {
        fprintf(stderr, "You can't return the book because no one has taken it\n");
        return;
    }

    int found_student_book_index = -1;
    for (int i = 0; i < MAX_LIBRARY_SIZE; i++) {
        if (strcmp(student_books[i]->student_number, student_number) == 0 && student_books[i]->ISBN == ISBN) {
            books[book_index]->current_count++;
            found_student_book_index = i;
            break;
        }
    }

    if (found_student_book_index == -1) {
        fprintf(stderr, "You can't return the book because you didn't take it\n");
        return;
    }

    for (int i = found_student_book_index; i < MAX_LIBRARY_SIZE - 1; i++) {
        student_books[i] = student_books[i + 1];
    }
    students[MAX_STUDENTS_NUMBER - 1] = NULL;
}

void all_student_books(Student **students, Book **books, Student_book **student_books) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number:");
    scanf("%s", student_number);

    if (search_student(students, student_number) == STUDENT_NOT_FOUND) {
        fprintf(stderr, "There is no student with this number\n");
        return;
    }

    int book = find_books_by_student(student_books, student_number, 0);

    if (book == BOOK_NOT_FOUND) {
        fprintf(stderr, "This student has no books\n");
        return;
    } else puts("Books this student has:");

    int ISBN, book_index;

    while (book != BOOK_NOT_FOUND) {
        ISBN = student_books[book]->ISBN;
        book_index = search_book(books, ISBN);
        if (book_index != BOOK_NOT_FOUND) {
            puts("-----------------------------------------------------------------------");
            printf("%d %19s %19s %3d %3d %9s\n", books[book_index]->ISBN, books[book_index]->author,
                   books[book_index]->title, books[book_index]->total_count,
                   books[book_index]->current_count, student_books[book]->return_date);
            puts("-----------------------------------------------------------------------");
        }
        book = find_books_by_student(student_books, student_number, book + 1);
    }
}

void students_with_book(Student **students, Book **books, Student_book **student_books) {
    int ISBN;

    puts("Enter the ISBN number:");
    scanf("%d", &ISBN);

    if (search_book(books, ISBN) == BOOK_NOT_FOUND) {
        fprintf(stderr, "This book is not in the library\n");
        return;
    }

    int student = find_students_with_book(student_books, ISBN, 0);

    if (student == STUDENT_NOT_FOUND) {
        fprintf(stderr, "None of the students took this book\n");
        return;
    } else puts("Students who took this book:");

    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    int student_index;

    while (student != STUDENT_NOT_FOUND) {
        strcpy(student_number, student_books[student]->student_number);
        student_index = search_student(students, student_number);
        if (student_index != STUDENT_NOT_FOUND) {
            puts("-----------------------------------------------------------------------");
            printf("%8s %14s %14s %9s %14s %19s\n", students[student_index]->student_number,
                   students[student_index]->lastname,
                   students[student_index]->firstname, students[student_index]->faculty,
                   students[student_index]->speciality, student_books[student]->return_date);
            puts("-----------------------------------------------------------------------");
        }
        student = find_students_with_book(student_books, ISBN, student + 1);
    }
}