/**
* Author: Yujin Jeong
* Date: 17th Oct 2024
* Purpose: Writing a program that reads the content of a file and sorting students based on the options.
*          Option1 - Only domestic students with GPA > 3.9.
*          Option2 - Only international students with GPA > 3.9 && TOEFL >= 70.
*          Option3 - All students with GPA > 3.9 (Domestic and International with TOEFL >= 70).
*          Option4 - All students with GPA in descending order.
*/

#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main( int argc, char *argv[]) {

    //argc has 4 arguments(Program name, Input file, Output file, Options).
    if(argc < 4 || argc > 5) {
        puts("Not enough arguments or more arguments have been typed :p\n");
        exit(1);
    }

    const char* input_file_name     = argv[1];          //Input file for reading
    const char* output_file_name    = argv[2];          //Output file for writing
    int options                     = atoi(argv[3]);    //Options to choose which files want to be written

    FILE *file1;    //file1 for reading
    FILE *file2;    //file2 for writing

    //Function for opening file with specific mode
    file1 = open_file(input_file_name, "r");
    file2 = open_file(output_file_name, "w");

    // Allocating memory for a line of text file(Max = 150).
    char* file_line;
    file_line = allocate_memory_for_line(file1, file2);

    Domestic        *domestic_students;
    International   *international_students;

    // Allocating memory for number of students of both domestic and international(Max = 150).
    allocate_memory_for_students(&domestic_students, &international_students);

    int domestic_students_count      = 0;
    int international_students_count = 0;
    int max_student                  = MAX_STUDENT;

    //Reading file line by line until the end of the file.
    while (fgets(file_line, MAX_LINE_LENGTH, file1) != NULL) {

        //Parsing function
        parse_line_of_file(file_line, &domestic_students[domestic_students_count],
            &international_students[international_students_count]);

        //If domestic student data is valid, increase the count of domestic student
        if(validate_domestic(&domestic_students[domestic_students_count])) {
            domestic_students_count++;
           }

        //If domestic student is more than allocated memory, reallocate memory.
        reallocate_domestic(&domestic_students, domestic_students_count, &max_student);

        //If international student data is valid, increase the count of international student
        if(validate_international(&international_students[international_students_count])) {
            international_students_count++;
        }

        //If the number of international student is more than allocated memory, reallocate memory.
        reallocate_international(&international_students, international_students_count, &max_student);
    }

    //For command line argument
    switch(options) {
        case 1:
            domestic_with_good_GPA(file2, domestic_students, domestic_students_count);
            break;
        case 2:
            internation_with_good_GPA_and_toefl(file2, international_students, international_students_count);
            break;
        case 3:
            all_student_with_good_GPA(file2, domestic_students, international_students,
                domestic_students_count, international_students_count);
            break;
        case 4:
            fprintf_sorted_gpa(file2, domestic_students, international_students, domestic_students_count,
                international_students_count);
            break;
        default:
            puts("No options available :( \n");
            break;
    }

    //Freeing all allocated memory
    free_all_allocate_memory(domestic_students, international_students, domestic_students_count,
        international_students_count, file_line);

    //File close
    fclose(file1);
    fclose(file2);
    return 0;
}