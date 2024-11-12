/**
* Author: Yujin Jeong
* Date: 17th Oct 2024
* Purpose: student.c has implemented functions.
*		   open_file() Opening file with specific mode.
*		   allocate_memory_for_line() Allocating memory for a line of text file.
*		   allocate_memory_for_students() Allocating memory for number of students of both domestic and international.
*          parse_line_of_file() Parsing each line of input file (domestic cases, international cases).
*		   fill_domestic_up() Filling up parsed data into Domestic struct.
*		   fill_international_up() Filling up parsed data into International struct.
*		   validate_domestic() Validating for domestic student data.
*		   validate_international() Validating for international student data.
*		   reallocate_domestic() Reallocating memory if domestic student is more than allocated memory.
*		   reallocate_international() Reallocating memory if international student is more than allocated memory.
*		   domestic_with_good_GPA() Getting only domestic students with GPA > 3.9.
*		   internation_with_good_GPA_and_toefl() Getting only international students with GPA > 3.9 and TOEFL >= 70.
*		   all_student_with_good_GPA() Getting all students with GPA > 3.9 and TOEFL >= 70.
*		   fprintf_sorted_gpa() Organising students' gpa in descending order by using selection sort
*		   free_all_allocate_memory() Freeing all allocated memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//Function to open file with specific mode.
FILE *open_file(const char* file_name, const char* mode) {

	FILE *file = fopen(file_name, mode);

	//Throwing an error, if file doesn't exist.
	if (file == NULL) {
		puts("This file doesn't exist :/\n");
		exit(1);
	}
	return file;
}

//Function to allocate memory for a line of text file(Max = 150).
char* allocate_memory_for_line(FILE *file1, FILE *file2) {

	// Allocating memory for a line of text file(Max = 150).
	char* file_line = malloc(MAX_LINE_LENGTH * sizeof(char));

	//Throwing an error, if memory allocation failed.
	if (file_line == NULL) {
		puts("Memory allocation for file_line failed :(\n");
		fclose(file1);
		fclose(file2);
		exit(1);
	}
	return file_line;
}

//Function to allocate memory for number of students of both domestic and international(Max = 150).
void allocate_memory_for_students(Domestic **domestic_students, International **international_students) {

	// Allocating memory for number of students of both domestic and international(Max = 150).
	*domestic_students      = malloc(MAX_STUDENT * sizeof(Domestic));
	*international_students = malloc(MAX_STUDENT * sizeof(International));

	//Throwing an error, if memory allocation failed.
	if (domestic_students == NULL || international_students == NULL) {
		puts("Memory allocation for domestic_students or international_students are failed :(\n");
		exit(1);
	}
}

//Function to parse each line of input file (domestic cases, international cases).
void parse_line_of_file(char *line, Domestic *domestic, International *international) {

    //Splitting line of string into multiple pieces(tokens) using delimiters.(Need string.h header file)
    char *first_name            = strtok(line, " ");
    char *last_name             = strtok(NULL, " ");
    char *gpa_in_line           = strtok(NULL, " ");
    char *student_status_char   = strtok(NULL, " ");
    char *toefl                 = strtok(NULL, " ");

    //Checking if first name or last name or GPA or student status char or toefl are not empty.
    if(first_name == NULL || last_name == NULL || gpa_in_line == NULL || student_status_char == NULL) {
        puts("ERROR!!!!!! ERROR!!!!!! Where is name or GPA or student status char? :/\n");
        exit(1);
    }

    //For domestic student and international student
    //Copying data into domestic struct and international struct
    if (student_status_char[0] == 'D') {
    	fill_domestic_up(domestic, first_name, last_name, gpa_in_line, student_status_char);
    } else if (student_status_char[0] == 'I') {
    	fill_international_up(international, first_name, last_name, gpa_in_line, student_status_char, toefl);

    	//Validating toefl score to make sure it's international students' data.
    	if(international->toefl <= 0) {
    		printf("Invalid TOEFL score :/\n");
    	}
    }
}

//Function to fill up parsed data into Domestic struct.
void fill_domestic_up(Domestic *domestic, const char *first_name, const char *last_name, const char *gpa_in_line,
	const char *student_status_char) {

	//Allocating memory for domestic students' names and international students' names.
	// +2 --> 1 for space between fist name and last name. 1 for null terminator.
	domestic->name       = (char *)malloc(strlen(first_name) + strlen(last_name) + 2);

	//Throwing an error, if memory allocation failed.
	if (domestic->name == NULL) {
		puts("Memory allocation failed :(\n");
		exit(1);
	}

	//String concatenation for first and last name and make it as one name
	strcpy(domestic->name, first_name);
	strcat(domestic->name, " ");
	strcat(domestic->name, last_name);

	//Converting gpa String to float
	domestic->gpa = strtof(gpa_in_line, NULL); //Don't need a pointer. So NULL.

	//Converting status string to char
	domestic->domestic_char = student_status_char[0];
}

//Function to fill up parsed data into International struct.
void fill_international_up(International *international, const char *first_name, const char *last_name, const char *gpa_in_line,
	const char *student_status_char, const char *toefl) {

	//Allocating memory for domestic students' names and international students' names.
	// +2 --> 1 for space between fist name and last name. 1 for null terminator.
	international->name  = (char *)malloc(strlen(first_name) + strlen(last_name) + 2);

	//Throwing an error, if memory allocation failed.
	if (international->name == NULL) {
		puts("Memory allocation failed :(\n");
		exit(1);
	}

	//String concatenation for first and last name and make it as one name
	strcpy(international->name, first_name);
	strcat(international->name, " ");
	strcat(international->name, last_name);

	//Converting gpa String to float
	international->gpa = strtof(gpa_in_line, NULL);

	//Converting status string to char
	international->international_char = student_status_char[0];

	//Converting TOEFL string to int
	international->toefl = atoi(toefl);
}

//Function to validate for domestic student data.
int validate_domestic(Domestic *domestic) {
	if(domestic -> name != NULL && domestic -> gpa > 0.000f && domestic -> domestic_char == 'D') {
		return 1;
	}
	return 0;
}

//Function to validate for international student data.
int validate_international(International *international) {
	if(international -> name != NULL && international -> gpa > 0.000f && international -> international_char == 'I' &&
		international -> toefl > 0) {
		return 1;
	}
	return 0;
}

//Function to reallocate memory if domestic student is more than allocated memory.
void reallocate_domestic(Domestic **domestic, int domestic_students_count, int *max_student) {

	//If domestic student is more than max students(150), reallocate memory
	if(domestic_students_count >= *max_student) {
		*max_student *= 2;
		*domestic = realloc(*domestic, (*max_student) * sizeof(Domestic));

		//Throwing an error, if memory reallocation failed.
		if (*domestic == NULL) {
			puts("Memory reallocation failed :/ \n");
			free(*domestic);
			exit(1);
		}
	}
}

//Function to reallocate memory if international student is more than allocated memory.
void reallocate_international(International **international, int international_students_count, int *max_student) {

	//If international student is more than max students(150), reallocate memory
	if(international_students_count >= *max_student) {
		*max_student *= 2;
		*international = realloc(*international, (*max_student) * sizeof(International));

		//Throwing an error, if memory reallocation failed.
		if (*international == NULL) {
			puts("Memory reallocation failed :/ \n");
			free(*international);
			exit(1);
		}
	}
}

//Function to get only domestic students with GPA > 3.9.
void domestic_with_good_GPA(FILE *file2, Domestic *domestic, int num_of_student) {
	for(int i = 0; i < num_of_student; i++) {

		if(domestic[i].gpa > 3.900f) {
			fprintf(file2, "%s %.3f %c\n", domestic[i].name, domestic[i].gpa, domestic[i].domestic_char);
		}
	}
}

//Function to get only international students with GPA > 3.9 and TOEFL >= 70.
void internation_with_good_GPA_and_toefl(FILE *file2, International *international, int num_of_student) {
	for(int i = 0; i < num_of_student; i++) {

		if(international[i].gpa > 3.900f && international[i].toefl >= 70) {
				fprintf(file2, "%s %.3f %c %d\n", international[i].name, international[i].gpa,
					international[i].international_char, international[i].toefl);
		}
	}
}

//Function to get all students with GPA > 3.9 and TOEFL >= 70
void all_student_with_good_GPA(FILE *file2, Domestic *domestic, International *international,
	int num_of_domestic, int num_of_international){
		int index_for_domestic = 0;
		int index_for_international = 0;

		//While loop goes through within the range of both domestic and international number of students.
		while(index_for_domestic < num_of_domestic || index_for_international < num_of_international) {

			//Writing only domestic student with gpa over 3.900.
			if(index_for_domestic < num_of_domestic) {
				if(domestic[index_for_domestic].gpa > 3.900f) {

					fprintf(file2, "%s %.3f %c\n", domestic[index_for_domestic].name, domestic[index_for_domestic].gpa,
						domestic[index_for_domestic].domestic_char);
				}
				index_for_domestic++;
			}

			//Writing only international student with gpa over 3.900 adn TOEFL greater than or equal to 70.
			if(index_for_international < num_of_international) {
				if(international[index_for_international].gpa > 3.900f &&
					international[index_for_international].toefl >= 70) {

					fprintf(file2, "%s %.3f %c %d\n", international[index_for_international].name,
						international[index_for_international].gpa,
						international[index_for_international].international_char,
						international[index_for_international].toefl);
				}
				index_for_international++;
			}
		}
}

//Function to swap
void swap(void **xp, void **yp) {
	void *temp = *xp;
	*xp = *yp;
	*yp = temp;
}

//Function to organise students' gpa in descending order by using selection sort
void sort_students_gpa(void **students, int count) {
	//First for loop for first student
	for (int i = 0; i < count-1; i ++) {

		//Will hold highes gpa student
		int find_max_gpa_student = i;

		//Second for loop for second student
		for(int j = i+1; j < count; j++ ) {
			float first_student;
			float second_student;

			//First student to compare
			first_student = ((Domestic*)students[find_max_gpa_student]) -> domestic_char == 'D' ?
				((Domestic*)students[find_max_gpa_student]) -> gpa :
				((International*)students[find_max_gpa_student]) -> gpa;

			//Second student to compare
			second_student = ((Domestic*)students[j]) -> domestic_char == 'D' ?
				((Domestic*)students[j]) -> gpa :
				((International*)students[j]) -> gpa;

			if (second_student > first_student) {
				find_max_gpa_student = j;
			}
		}
		swap(&students[i], &students[find_max_gpa_student]);
	}
}

//Function to write file for students sorted their gpa in ascending order.
void fprintf_sorted_gpa(FILE *file2, Domestic *domestic_students, International *international_students,
								int domestic_count, int international_count) {

	int total_students_count = domestic_count + international_count;

	//Allocate memory for holding the entire students. Using generic pointer for any data type.
	void **all_students = malloc(total_students_count * sizeof(void*));

	//Adding domestic students in all_students array
	for(int i = 0; i < domestic_count; i++) {
		all_students[i] = &domestic_students[i];
	}
	//Adding international students in all_students array (Must be filled after domestic_student index)
	for(int i = 0; i < international_count; i++) {
		all_students[domestic_count + i] = &international_students[i];
	}

	sort_students_gpa(all_students, total_students_count);

	//Writing file
	for(int i = 0; i < total_students_count; i++) {

		if(((Domestic*)all_students[i]) -> domestic_char == 'D') {
			fprintf(file2, "%s %.3f %c\n",
				((Domestic*)all_students[i]) -> name,
				((Domestic*)all_students[i]) -> gpa,
				((Domestic*)all_students[i]) ->domestic_char);
		} else {
			fprintf(file2, "%s %.3f %c\n",
				((International*)all_students[i]) -> name,
				((International*)all_students[i]) -> gpa,
				((International*)all_students[i]) ->international_char);
		}
	}
	free(all_students);
}

//Function to free all allocated memory
void free_all_allocate_memory(Domestic *domestic_students, International *international_students, int domestic_count,
	int international_count, char * file_line) {

	for(int i = 0; i < domestic_count; i ++) {
		free(domestic_students[i].name);
	}
	for(int i = 0; i < international_count; i ++) {
		free(international_students[i].name);
	}
	free(domestic_students);
	free(international_students);
	free(file_line);
}