#ifndef GRAND_TASK_STUDENTS_H
#define GRAND_TASK_STUDENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS_NUMBER 1000
#define MAX_STUDENT_DATA_LENGTH 50
#define MAX_STUDENT_NUMBER_LENGTH 10
#define STUDENT_NOT_FOUND -1

typedef struct Student_t {
    char *student_number;
    char *lastname;
    char *firstname;
    char *faculty;
    char *speciality;
} Student;

Student **student_database_initialization(char *filename);

void students_file_parse(char *filename, Student **students);

void save_students(Student **students, char *filename);

int search_student(Student **students, char *student_number);

void add_student(Student **students);

void view_student(Student **students);

void edit_student(Student **students);

void lastname_search(Student **students);

#endif //GRAND_TASK_STUDENTS_H
