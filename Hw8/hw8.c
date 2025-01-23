#include <stdio.h>
#include<string.h>

#define max_sci 100
#define MAX_ROW_COUNT 50
#define MAX_COL_COUNT 50

/*Function Prototypes*/
void sort_people_by_age(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]);
void sort_people_by_branch(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]);
void filter_people_by_branch(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]);
void filter_people_by_profession(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]);
void search_p1(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches);
void search_p2(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches);
void search_p3(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches);

int main() {
    /*Open files for reading*/
    FILE *inp1 = fopen("input1.txt", "r");
    FILE *inp2 = fopen("input2.txt", "r");
    int choice, age[max_sci];
    /*Arrays for names, surnames and branches*/
    char name[max_sci][50], surname[max_sci][50], branch1[max_sci][50], branch2[max_sci][50];

    int num_rows = 0,num_match_p1 = 0, num_match_p2 = 0, num_match_p3 = 0, i;
    char pattern[MAX_ROW_COUNT][MAX_COL_COUNT]; /*Array for the patterns*/
    /*Arrays for the matches*/
    int match_p1[MAX_ROW_COUNT * MAX_COL_COUNT][2]; 
    int match_p2[MAX_ROW_COUNT * MAX_COL_COUNT][2]; 
    int match_p3[MAX_ROW_COUNT * MAX_COL_COUNT][2];

    /*Check if the files are opened successfully*/
    if (inp1 == NULL){
        printf("ERROR OPENING THE INPUT1.TXT FILE!!!");
        return 0;
    }
    if (inp2 == NULL){
        printf("ERROR OPENING THE INPUT2.TXT FILE!!!");
        return 0;
    }
    printf("\n\n******Menu******************\n");
    while (1) {
        printf("1. Sort and display all individuals by age\n");
        printf("2. Sort and display individuals in the branch by age\n");
        printf("3. Show individuals with the branch 'SCIENCE'\n");
        printf("4. Show computer scientists who are not mathematicians\n");
        printf("5. Test the Part 2 of the assignment\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        /*Check if the choice is valid*/
        if (choice < 1 || choice > 6) {
            printf("ENTER A VALID NUMBER!!!\n");
        } else {
            switch (choice) {
                case 1: /*Sorts and displays all people by age*/
                    fopen("input1.txt", "r"); 
                    sort_people_by_age(inp1, name, surname, age, branch1, branch2);
                    fclose(inp1);
                    break;
                case 2: /*Sort and display all people by branches*/
                    fopen("input1.txt", "r");
                    sort_people_by_branch(inp1, name, surname, age, branch1, branch2);
                    fclose(inp1);
                    break;
                case 3: /*Show individuals with the branch 'SCIENCE'*/
                    fopen("input1.txt", "r");
                    filter_people_by_branch(inp1, name, surname, age, branch1, branch2);
                    fclose(inp1);
                    break;
                case 4: /*Show computer scientists who are not mathematicians*/
                    fopen("input1.txt", "r");
                    filter_people_by_profession(inp1, name, surname, age, branch1, branch2);
                    fclose(inp1);
                    break;
                case 5: /*Testing the part 2 of the hw*/
                    num_rows = 0;
                    num_match_p1 = 0;
                    num_match_p2 = 0;
                    num_match_p3 = 0;

                    fopen("input2.txt", "r");

                    /*Read patterns from the file*/
                    while (num_rows < MAX_ROW_COUNT && fgets(pattern[num_rows], MAX_COL_COUNT, inp2) != NULL){
                        for ( i = 0; i < strlen(pattern[num_rows]); i++){
                            if (pattern[num_rows][i] == '\n'){ /*If new line character is found*/
                                pattern[num_rows][i] = '\0'; /*It will replace it with null terminator*/
                                break;
                            }
                        }
                        num_rows++;
                    }

                    fclose(inp2);

                    /*Call the function to search pattern 1 the input and then prints the match*/
                    search_p1(pattern, num_rows, match_p1, &num_match_p1);
                    for (i = 0; i < num_match_p1; i++) {
                        printf("\nP1 @ (%d,%d)\n", match_p1[i][0], match_p1[i][1]);
                    }
                    
                    printf("\n");

                    /*Call the function to search pattern 2 the input and then prints the match*/
                    search_p2(pattern, num_rows, match_p2, &num_match_p2);
                    for (i = 0; i < num_match_p2; i++) {
                        printf("P2 @ (%d,%d)\n", match_p2[i][0], match_p2[i][1]);
                    }
                    
                    printf("\n");
                    /*Call the function to search pattern 1 the input and then prints the match*/
                    search_p3(pattern, num_rows, match_p3, &num_match_p3);
                    for (i = 0; i < num_match_p3; i++) {
                        printf("P3 @ (%d,%d)\n", match_p3[i][0], match_p3[i][1]);
                    }
                    printf("\n");
                    
                    break;
                case 6:
                    printf("SEE YOU SOON!\n");
                    fclose(inp1);
                    fclose(inp2);
                    return 0;
                default:
                    break;
            }
        }
    }
    return 0;
}

void sort_people_by_age(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]){
    int i, j, temp_age;
    int sci_count = 0, comma_count = 0;
    char line[200], temp_words[50]; /*Declare array for storing current line and temporary strings*/
   
    /*DIVIDE THE LINE BASED ON THE COMMAS*/
    while (sci_count < max_sci && fgets(line, 200, inp)){
        comma_count = 0;
        char *divider = strtok(line, ",");  /*Break the line based on the commas*/
        while (divider){ /*Itareate over words until NULL is encountered*/
            if (comma_count == 0){ /*First word before the comma (First token)*/
                strcpy(name[sci_count], divider);  /*Copy the word to the array*/
            }else if(comma_count == 1){
                strcpy(surname[sci_count], divider);
            }else if(comma_count == 2){
                sscanf(divider, "%d", &age[sci_count]);
            }else if(comma_count == 3){
                strcpy(branch1[sci_count], divider);
            }else if(comma_count == 4){
                strcpy(branch2[sci_count], divider);
            }
            comma_count++;
            divider = strtok(NULL, ",");
        }
        sci_count++;
    }
    
    /*Bubble sort*/
    for ( i = 0; i < sci_count - 1; i++){ /*Itarte over each scientists*/
        for (j = 0; j < sci_count - i - 1; j++){ /*Compare with the remaining scientists*/
            if (age[j] > age[j+1]){ /*Compare ages*/

                /*Swap ages*/
                temp_age = age[j];
                age[j] = age[j+1];
                age[j+1] = temp_age;

                /*Swap names*/
                strcpy(temp_words, name[j]);
                strcpy(name[j], name[j+1]);
                strcpy(name[j+1], temp_words);

                /*Swap surnames*/
                strcpy(temp_words, surname[j]);
                strcpy(surname[j], surname[j+1]);
                strcpy(surname[j+1], temp_words);

                /*Swap Branch1*/
                strcpy(temp_words, branch1[j]);
                strcpy(branch1[j], branch1[j+1]);
                strcpy(branch1[j+1], temp_words);

                /*Swap Branch2*/
                strcpy(temp_words, branch2[j]);
                strcpy(branch2[j], branch2[j+1]);
                strcpy(branch2[j+1], temp_words);
            }
        }
    }
    
    /*Print the sorted data*/
    printf("\n\n%-15s %-15s %-5s %-15s %-15s\n\n", "Name", "Surname", "Age", "Branch1", "Branch2");
    for ( i = 0; i < sci_count; i++){
        printf("%-15s %-15s %-5d %-15s %-15s\n", name[i], surname[i], age[i], branch1[i], branch2[i]);
    } 
}

void sort_people_by_branch(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]) {
    int i, j, temp_age;
    int sci_count = 0, comma_count = 0; 
    char line[200], temp_words[50]; /*Declare array for storing current line and temporary strings*/

    /*Read the file line by line and break each line based on the commas*/
    while (sci_count < max_sci && fgets(line, 200, inp)){
        comma_count = 0;
        char *divider = strtok(line, ",");
        while (divider){
            if (comma_count == 0){
                strcpy(name[sci_count], divider); /*Store names*/
            }else if(comma_count == 1){
                strcpy(surname[sci_count], divider); /*Store surnames*/
            }else if(comma_count == 2){
                sscanf(divider, "%d", &age[sci_count]); /*Store age*/
            }else if(comma_count == 3){
                strcpy(branch1[sci_count], divider); /*Store branch1*/
            }else if(comma_count == 4){
                strcpy(branch2[sci_count], divider); /*Store branch2*/
            }
            comma_count++; 
            divider = strtok(NULL, ","); 
        }
        sci_count++;
    }

    /*Sorting by branch1, branch2, and age*/
    for (i = 0; i < sci_count - 1; i++) {
        for (j = 0; j < sci_count - i - 1; j++) {
            /*Compare the branch1*/
            int branch1_compare = strcmp(branch1[j], branch1[j + 1]);
            if (branch1_compare > 0 || 
               (branch1_compare == 0 && strcmp(branch2[j], branch2[j + 1]) > 0) || 
               (branch1_compare == 0 && strcmp(branch2[j], branch2[j + 1]) == 0 && age[j] > age[j + 1])) {
                /*Swap the scientists if the conditions are met*/
                /*Swap names*/
                strcpy(temp_words, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], temp_words);
                /*Swap surnames*/
                strcpy(temp_words, surname[j]);
                strcpy(surname[j], surname[j + 1]);
                strcpy(surname[j + 1], temp_words);
                /*Swap ages*/
                temp_age = age[j];
                age[j] = age[j + 1];
                age[j + 1] = temp_age;
                /*Swap branch1*/
                strcpy(temp_words, branch1[j]);
                strcpy(branch1[j], branch1[j + 1]);
                strcpy(branch1[j + 1], temp_words);
                /*Swap branch2*/
                strcpy(temp_words, branch2[j]);
                strcpy(branch2[j], branch2[j + 1]);
                strcpy(branch2[j + 1], temp_words);
            }
        }
    }

    /*Print sorted data*/
    printf("\n\n%-15s %-15s %-5s %-15s %-15s\n", "Name", "Surname", "Age", "Branch1", "Branch2");
    for (i = 0; i < sci_count; i++) {
        printf("%-15s %-15s %-5d %-15s %-15s\n", name[i], surname[i], age[i], branch1[i], branch2[i]);
    }
}


void filter_people_by_branch(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]) {
    int i, sci_count = 0, comma_count = 0;
    char line[200];
    char keyword[50] = "SCIENCE";
    printf("\n\n%-15s %-15s %-5s %-15s %-15s\n", "Name", "Surname", "Age", "Branch1", "Branch2");
     /*Read the file line by line and break each line based on the commas*/
    while (sci_count < max_sci && fgets(line, 200, inp)) {
        comma_count = 0;
        char *divider = strtok(line, ","); /*Break the line based on the commas*/
        while (divider) {
            if (comma_count == 0) {
                strcpy(name[sci_count], divider); /*Store names*/
            } else if (comma_count == 1) {
                strcpy(surname[sci_count], divider); /*Store surname*/
            } else if (comma_count == 2) {
                sscanf(divider, "%d", &age[sci_count]); /*Store age*/
            } else if (comma_count == 3) {
                strcpy(branch1[sci_count], divider); /*Store branch1*/
            } else if (comma_count == 4) {
                strcpy(branch2[sci_count], divider); /*Store branch2*/
            }
            comma_count++;
            divider = strtok(NULL, ","); /*Move to the next line*/
        }

        /*Check if the person's branch matches the keyword SCIENCE*/
        if (strstr(branch1[sci_count], keyword) != NULL || strstr(branch2[sci_count], keyword) != NULL) {
            /*IF either branch1 or branch2 matches the keyword, print the scientist other information*/
            printf("%-15s %-15s %-5d %-15s %-15s\n", name[sci_count], surname[sci_count], age[sci_count], branch1[sci_count], branch2[sci_count]);
        }
        sci_count++;
    }
}

void filter_people_by_profession(FILE *inp, char name[][50], char surname[][50], int age[], char branch1[][50], char branch2[][50]) {
    int i, sci_count = 0, comma_count = 0;
    char line[200];

    printf("\n\n%-15s %-15s %-5s %-15s %-15s\n", "Name", "Surname", "Age", "Branch1", "Branch2");

    /*Read the file line by line and break each line based on the commas*/
    while (sci_count < max_sci && fgets(line, 200, inp)) {
        comma_count = 0;
        char *divider = strtok(line, ","); /*Break the line based on the commas*/
        while (divider) {
            if (comma_count == 0) {
                strcpy(name[sci_count], divider); /*Store names*/
            } else if (comma_count == 1) {
                strcpy(surname[sci_count], divider); /*Store surnames*/
            } else if (comma_count == 2) {
                sscanf(divider, "%d", &age[sci_count]); /*Store ages*/
            } else if (comma_count == 3) {
                strcpy(branch1[sci_count], divider); /*Store branch1*/
            } else if (comma_count == 4) {
                strcpy(branch2[sci_count], divider); /*Store branch2*/
            }
            comma_count++;
            divider = strtok(NULL, ",");
        }
        /*Check if the scientist is a computer sci and not a mathematician*/
        if (strstr(branch1[sci_count], "COMPUTER SCIENCE") != NULL && strstr(branch2[sci_count], "MATHEMATICS") == NULL) {
            /*Print the other inforamtion about scientists if the condition satisified*/
            printf("\n%-15s %-15s %-5d %-15s %-15s\n", name[sci_count], surname[sci_count], age[sci_count], branch1[sci_count], branch2[sci_count]);
        }
        sci_count++;
    }
}

/*Serach row*/
void search_p1 (char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){
    const char target_pattern[] = "***++++***++++***"; /*Target pattern*/
    int pattern_len = strlen(target_pattern); /*Calculate the lenght of the target pattern*/
    int i, j;

    /*Iterate over each row in the array of strings */
    for (i = 0; i < num_rows; i++){
        char *current = strs[i]; /*Get the current row*/
        j = 0;

        /*Iterate over each character in the current row*/
        while (current[j] != 0){ /*Loop until the null terminator*/
            /*Check if the substring starting at current[j] matches the target pattern*/
            if (strncmp(&current[j], target_pattern, pattern_len) == 0){
                /*If the match is found, it stores the row and column indices in the matches array*/
                matches[*num_matches][0] = i + 1; /*Store the row index*/
                matches[*num_matches][1] = j + 1; /*Store the column index*/
                (*num_matches)++; /*Increment the number of matches*/
            }
            j++; /*Move to the next char in the current row*/
        }   
    }
}

/*Search column*/
void search_p2(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){
    const char target_pattern[] = "+*+*+"; /*Target pattern*/
    int pattern_len = strlen(target_pattern); /*Calculate the lenght of the target pattern*/
    int i, j;

    /*Iterate over each column in the array of strings*/
    for (j = 0; j < MAX_COL_COUNT; j++){
        char column[MAX_ROW_COUNT]; /*Define an array to store the current column*/
        /*Extract the column from the array of strings*/
        for (i = 0; i < num_rows; i++){
            column[i] = strs[i][j]; /*Copy the character from the column to the row*/
        }
        column[num_rows] = '\0'; /*Add a null terminator to the end of the column array*/

        /* Iterate over the characters in the column, searching for the target pattern*/
        for (i = 0; i < num_rows - pattern_len + 1; i++){
            /*Check if the substring starting at column[i] matches the target pattern*/
            if (strncmp(&column[i], target_pattern, pattern_len) == 0){
                matches[*num_matches][0] = i + 1; /*Store the row index*/
                matches[*num_matches][1] = j + 1; /*Store the column index*/
                (*num_matches)++; /*Increment the number of matches*/
            }
        }
    }
}

/*Search diagonally*/
void search_p3(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){
    const char target_pattern[] = "“+**+++****+++**+"; /*Target pattern*/
    int pattern_len = strlen(target_pattern); /*Get the lenght of the target pattern*/
    int i, j, k;

    /*Loop through rows*/
    for (i = 0; i < num_rows - pattern_len + 1; i++) {
        /*Loop through column*/
        for (j = 0; j < MAX_COL_COUNT - pattern_len + 1; j++) {
            /*Loop through characters in the target pattern*/
            for (k = 0; k < pattern_len; k++) {
                /*Check if the characters match*/
                if (strs[i+k][j+k] != target_pattern[k]) {
                    /*IF charachers dont match, break the loop*/
                    break;
                }
            }
            /*IF the pattern match this part gets the index*/
            if (k == pattern_len) {
                matches[*num_matches][0] = i+1; /*Index of the row*/
                matches[*num_matches][1] = j+1; /*Index of the column*/
                (*num_matches)++; /*Increment the number of matches*/
            }
        }
    }
}

