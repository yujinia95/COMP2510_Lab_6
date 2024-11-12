/**
* Author: Yujin Jeong
* Date: 17th Oct 2024
* Purpose: Has constants, data structures, and function prototypes
 *
 */
#ifndef STUDENT_H //Checking if STUDENT_H is not defined
#define STUDENT_H

#define MAX_LINE_LENGTH 150 //Max number of length per line (Using for malloc when read file).
#define MAX_NAME_LENGTH 50 //Max number of name.
#define MAX_STUDENT 150 //Max number of students.

typedef struct {    //Domestic struct
    char *name;
    float gpa;
    char domestic_char;
} Domestic;

typedef struct {    //International struct
    char *name;
    float gpa;
    char international_char;
    int toefl;
} International;

//Function prototypes

//Function for opening file with specific mode
FILE *open_file(const char* file_name, const char* mode);

//Allocate memory for a line of text file(Max = 150)
char* allocate_memory_for_line(FILE *file1, FILE *file2);

// Allocating memory for number of students of both domestic and international(Max = 150).
void allocate_memory_for_students(Domestic **domestic_students, International **international_students);

//Parsing each line of input file (domestic cases, international cases)
void parse_line_of_file(char *line, Domestic *domestic, International *international);

//Fill up parsed data into Domestic struct
void fill_domestic_up(Domestic *domestic, const char *first_name, const char *last_name, const char *gpa_in_line,
    const char *student_status_char);

//Fill up parsed data into International struct
void fill_international_up(International *international, const char *first_name, const char *last_name,
    const char *gpa_in_line, const char *student_status_char, const char *toefl);

//Function to validate for domestic student data
int validate_domestic(Domestic *domestic);

//Function to validate for international student data
int validate_international(International *international);

//Function to reallocate memory if domestic student is more than allocated memory.
void reallocate_domestic(Domestic **domestic, int domestic_students_count, int *max_student);

//Function to reallocate memory if international student is more than allocated memory.
void reallocate_international(International **international, int international_students_count, int *max_student);

//Function to get only domestic students with GPA > 3.9
void domestic_with_good_GPA(FILE *file2, Domestic *domestic, int num_of_student);

//Function to get only international students with GPA > 3.9 and TOEFL >= 70
void internation_with_good_GPA_and_toefl(FILE *file2, International *international, int num_of_student);

//Function to get all students with GPA > 3.9 and TOEFL >= 70
void all_student_with_good_GPA(FILE *file2, Domestic *domestic, International *international,
    int num_of_domestic, int num_of_international);

//Function to organise students' gpa in descending order by using selection sort
void fprintf_sorted_gpa(FILE *file2, Domestic *domestic_students, International *international_students,
                                int domestic_count, int international_count);

//Freeing all allocated memory
void free_all_allocate_memory(Domestic *domestic_students, International *international_students, int domestic_count,
    int international_count, char * file_line);

#endif // Ending #ifndef block