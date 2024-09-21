#include "../include/students.h"

Student **student_database_initialization(char *filename) {
    Student **students = malloc(MAX_STUDENTS_NUMBER * sizeof(Student *));
    if (students == NULL)
        return NULL;

    for (int i = 0; i < MAX_STUDENTS_NUMBER; i++) {
        students[i] = malloc(sizeof(Student));
        students[i]->student_number = malloc(MAX_STUDENT_NUMBER_LENGTH * sizeof(char));
        strcpy(students[i]->student_number, "");
        students[i]->lastname = malloc(MAX_STUDENT_DATA_LENGTH * sizeof(char));
        strcpy(students[i]->lastname, "");
        students[i]->firstname = malloc(MAX_STUDENT_DATA_LENGTH * sizeof(char));
        strcpy(students[i]->firstname, "");
        students[i]->faculty = malloc(MAX_STUDENT_DATA_LENGTH * sizeof(char));
        strcpy(students[i]->faculty, "");
        students[i]->speciality = malloc(MAX_STUDENT_DATA_LENGTH * sizeof(char));
        strcpy(students[i]->speciality, "");
    }
    students_file_parse(filename, students);
    return students;
}

void student_database_free(Student **students) {
    if (students != NULL) {
        for (int i = 0; i < MAX_STUDENTS_NUMBER; i++) {
            if (students[i] != NULL) {
                free(students[i]->student_number);
                free(students[i]->lastname);
                free(students[i]->firstname);
                free(students[i]->faculty);
                free(students[i]->speciality);
                free(students[i]);
            }
        }
        free(students);
    }
}

void students_file_parse(char *filename, Student **students) {
    FILE *students_file = fopen(filename, "r");
    if (students_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    int max_string_size = MAX_STUDENT_NUMBER_LENGTH + (4 * MAX_STUDENT_DATA_LENGTH) + 4;

    char *string = malloc(max_string_size * sizeof(char));

    int number_of_students = 0;
    while (fgets(string, max_string_size, students_file) != NULL) {
        if (number_of_students >= MAX_STUDENTS_NUMBER) {
            break;
        }

        strcpy(students[number_of_students]->student_number, strtok(string, ","));
        strcpy(students[number_of_students]->lastname, strtok(NULL, ","));
        strcpy(students[number_of_students]->firstname, strtok(NULL, ","));
        strcpy(students[number_of_students]->faculty, strtok(NULL, ","));
        strcpy(students[number_of_students]->speciality, strtok(NULL, "\n"));

        number_of_students++;
    }

    free(string);
    fclose(students_file);
}

void save_students(Student **students, char *filename) {
    FILE *students_file = fopen(filename, "w");
    if (students_file == NULL) {
        fprintf(stderr, "Error file opening");
        return;
    }

    for (int i = 0; i < MAX_STUDENTS_NUMBER; i++) {
        if (strcmp(students[i]->student_number, "") != 0 && i == 0) {
            fprintf(students_file, "%s,%s,%s,%s,%s", students[i]->student_number, students[i]->lastname,
                    students[i]->firstname,
                    students[i]->faculty, students[i]->speciality);
        } else if (strcmp(students[i]->student_number, "") != 0) {
            fprintf(students_file, "\n%s,%s,%s,%s,%s", students[i]->student_number, students[i]->lastname,
                    students[i]->firstname,
                    students[i]->faculty, students[i]->speciality);
        } else break;
    }

    student_database_free(students);
    fclose(students_file);
}

int search_student(Student **students, char *student_number) {
    for (int student_index = 0; student_index < MAX_STUDENTS_NUMBER; student_index++) {
        if (strcmp(students[student_index]->student_number, student_number) == 0) {
            return student_index;
        }
    }
    return STUDENT_NOT_FOUND;
}

void add_student(Student **students) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number");
    scanf("%s", student_number);
    getchar();

    if (search_student(students, student_number) != STUDENT_NOT_FOUND) {
        fprintf(stderr, "The student with this number is already in the library database\n");
        return;
    }

    for (int i = 0; i < MAX_STUDENTS_NUMBER; i++) {
        if (strcmp(students[i]->student_number, "") == 0) {
            strcpy(students[i]->student_number, student_number);
            puts("Enter the student's lastname:");
            scanf("%s", students[i]->lastname);
            getchar();
            puts("Enter the student's firstname:");
            scanf("%s", students[i]->firstname);
            getchar();
            puts("Enter the student's faculty:");
            scanf("%[^\n]", students[i]->faculty);
            getchar();
            puts("Enter the student's speciality:");
            scanf("%[^\n]", students[i]->speciality);
            getchar();
            return;
        }
    }
    fprintf(stderr, "Student library database is full\n");
}

void view_student(Student **students) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number:");
    scanf("%s", student_number);

    int student_index = search_student(students, student_number);

    if (student_index == STUDENT_NOT_FOUND) {
        fprintf(stderr, "There is no student with this number\n");
        return;
    } else {
        puts("-----------------------------------------------------------------------");
        printf("Student\n"
               "Last name: %s\n"
               "First name: %s\n"
               "Faculty: %s\n"
               "Speciality: %s\n", students[student_index]->lastname, students[student_index]->firstname,
               students[student_index]->faculty, students[student_index]->speciality);
        puts("-----------------------------------------------------------------------");
    }
}

void edit_student(Student **students) {
    char student_number[MAX_STUDENT_NUMBER_LENGTH];

    puts("Enter the student's number:");
    scanf("%s", student_number);
    getchar();

    int student_index = search_student(students, student_number);

    if (student_index == STUDENT_NOT_FOUND) {
        fprintf(stderr, "There is no student with this number\n");
        return;
    } else {
        puts("Enter the student's lastname:");
        scanf("%s", students[student_index]->lastname);
        getchar();
        puts("Enter the student's firstname:");
        scanf("%s", students[student_index]->firstname);
        getchar();
        puts("Enter the student's faculty:");
        scanf("%[^\n]", students[student_index]->faculty);
        getchar();
        puts("Enter the student's speciality:");
        scanf("%[^\n]", students[student_index]->speciality);
        getchar();
    }
}

void lastname_search(Student **students) {
    char lastname[MAX_STUDENT_DATA_LENGTH];

    puts("Enter lastname:");
    scanf("%s", lastname);

    int match_found = 0;
    for (int i = 0; i < MAX_STUDENTS_NUMBER; i++) {
        if (strcmp(students[i]->lastname, lastname) == 0) {
            match_found = 1;
            puts("-----------------------------------------------------------------------");
            printf("%8s %14s %14s %9s %19s\n", students[i]->student_number,
                   students[i]->lastname, students[i]->firstname,
                   students[i]->faculty, students[i]->speciality);
            puts("-----------------------------------------------------------------------");
        }
    }

    if (!match_found) {
        fprintf(stderr, "There are no students with this lastname\n");
        return;
    }
}

