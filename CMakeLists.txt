cmake_minimum_required(VERSION 3.24)
project(BigHomework C)

set(CMAKE_C_STANDARD 23)

add_executable(BigHomework main.c sources/books.c include/books.h sources/students.c
        include/students.h sources/users.c include/users.h sources/student_books.c
        include/student_books.h sources/sha_256.c include/sha_256.h sources/menu.c include/menu.h)
