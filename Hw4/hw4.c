#include<stdio.h>

int semicolon_conter = 0;

char first_initial(FILE *id_fp, int id){
    char c, name_first_letter; 
    int current_id;


    while (fscanf(id_fp, "%d", &current_id) != EOF){
        if (current_id == id){
            while (semicolon_conter < 1){
                fscanf(id_fp, "%c", &c);
                if (c ==';'){
                    semicolon_conter++;
                }
            }
            fscanf(id_fp, "%c", &name_first_letter);
            return name_first_letter;
        }else {
             do {
                fscanf(id_fp, "%c", &c);
            } while (c != '\n');
            semicolon_conter = 0;
        }
    }
    return '\0';
}

char last_initial(FILE *id_fp, int id){
    char c, surname_first_initial;
    int current_id;


    while (fscanf(id_fp, "%d", &current_id) != EOF){
        if (current_id == id){
            while (semicolon_conter < 2){
                fscanf(id_fp, "%c", &c);
                if (c == ';'){
                    semicolon_conter++;
                }
            }
            fscanf(id_fp, "%c", &surname_first_initial);
            return surname_first_initial;
        }else {
             do {
                fscanf(id_fp, "%c", &c);
            } while (c != '\n');
            semicolon_conter = 0;
        }
    }
    return '\0';
}
int get_id_fi(FILE *id_fp, char first_initial) {
   char c, current_initial;
    int current_id;


    while (fscanf(id_fp, "%d", &current_id) != EOF) {
        semicolon_conter = 0; 
        while (semicolon_conter < 1 && fscanf(id_fp, "%c", &c) == 1 && c != EOF) {
            if (c == ';') {
                semicolon_conter++;
            }
        }
        fscanf(id_fp, " %c", &current_initial);
        if (current_initial == first_initial) {
           printf("ID with first initial '%c' is: %d\n", first_initial, current_id);
        }
        while (fscanf(id_fp, "%c", &c) == 1) {
            if (c == '\n' || c == EOF) 
            break;
        }
    }

    return -1;
}



int get_id_li(FILE * id_fp, char first_initial){
    int current_id;
    char c, current_last_initial;
    
    while (fscanf(id_fp, "%d", &current_id) != EOF) {
        semicolon_conter = 0;
        while (semicolon_conter < 2 && fscanf(id_fp, "%c", &c) == 1 && c != EOF) {
            if (c == ';') {
                semicolon_conter++;
            }
        }
        fscanf(id_fp, "%c", &current_last_initial);
        if(current_last_initial == first_initial){
            printf("ID with last initial '%c' is: %d\n", first_initial, current_id);
        }
        while (fscanf(id_fp, "%c", &c) == 1) {
            if (c == '\n' || c == EOF) 
            break;
        }
    }
    return -1; 
}


char get_letter_grade(float gpa) {
    char letter_grade;
    
    if (gpa == 4.0) {
        letter_grade = 'A';
    } else if (gpa >= 3.5) {
        letter_grade = 'B';
    } else if (gpa >= 3.0) {
        letter_grade = 'C';
    } else if (gpa >= 2.5) {
        letter_grade = 'D';
    } else if (gpa >= 1.0) {
        letter_grade = 'F';
    } else {
        letter_grade = 'X'; 
    }
    
    return letter_grade;
}


float average_grade(FILE *info_fp, int studentid, float mid_avg, float final_avg) {
    
    info_fp = fopen("first 1.txt", "r");
    
    float mid_Gpa, final_Gpa, Gpa;
    int id, midterm, midterm1, midterm2, final, lecture;
    
    while (fscanf(info_fp,"%d;", &id) == 1){
        
        if(studentid == id){
            if(id > 220000000){
                fscanf(info_fp, "%d;%d;%d;%d", &midterm1, &midterm2, &final, &lecture);
                midterm = (midterm1 + midterm2)/2;
            }
            else if(id > 210000000 && id < 220000000){
                fscanf(info_fp, "%d;%d;%d", &midterm, &final, &lecture);
            }
        }
    }
    
    if (midterm < 40 && midterm < mid_avg) {
        mid_Gpa = 1.0;
    } else if (midterm > 40 && midterm < mid_avg) {
        mid_Gpa = 2.5;
    } else if (midterm > 40 && midterm > mid_avg) {
        mid_Gpa = 3.0;
    } else if (midterm < 90 && midterm > mid_avg) {
        mid_Gpa = 3.5;
    } else if (midterm >= 90) {
        mid_Gpa = 4.0;
    } else {
        mid_Gpa = 0.0;
    }
    
    if(final < 40 && final < final_avg){
        final_Gpa = 1.0;
    }else if (final > 40 && final < final_avg) {
        final_Gpa = 2.5;
    } else if (final > 40 && final > final_avg ) {
        final_Gpa = 3.0;
    } else if (final < 90 && final > final_avg ) {
        final_Gpa = 3.5;
    } else if (midterm >= 90 ) {
        final_Gpa = 4.0;
    } else {
        final_Gpa = 0.0;
    }
    
    Gpa = (final_Gpa + mid_Gpa)/2;
    if(Gpa !=1.0 || Gpa !=2.5 || Gpa !=3.0 || Gpa !=3.5 || Gpa !=4.0){
        int temp1, temp2;
        temp1 = Gpa * 100;
        temp2 = temp1 % 100;
        Gpa = (temp1 - temp2)/100;
        if (Gpa == 2){
            Gpa = 2.5;
        }
    }
    
    char letter_grade = get_letter_grade(Gpa);
    
    printf("GPA: %.2f, Letter Grade: %c\n", Gpa, letter_grade);

    return letter_grade;
}

float avg_mid(FILE *info_fp){
    
    info_fp = fopen("first.txt", "r");
    
    int id, midterm, midterm1, midterm2;
    int counter=0;
    float totMidterm=0, average=0;
    
    do{
        fscanf(info_fp, "%d;", &id);
        if(id / 10000000 == 22){
            fscanf(info_fp, "%d;", &midterm1);
            fscanf(info_fp, "%d;", &midterm2);
               
            midterm = (midterm1 + midterm2)/2;
        }
        else if(id / 10000000 == 21){
            fscanf(info_fp, "%d;", &midterm);
        }
        totMidterm = totMidterm + midterm;
        counter += 1;
    } while (fscanf(info_fp, "%d;", &id) == 1);
    
    fclose(info_fp);
    
    average= totMidterm/counter;
    return average;
}

float avarage_final(FILE *info_fp){
    info_fp = fopen("first.txt", "r");
    
    int id, midterm, midterm1, midterm2; 
    int final, counter=0;
    float totFinal =0.0, average=0.0;
    
    
    do{
        fscanf(info_fp, "%d;", &id);
        if(id / 10000000 == 22){
            fscanf(info_fp, "%d;", &midterm1);
            fscanf(info_fp, "%d;", &midterm2);
            fscanf(info_fp, "%d;", &final);
        }
        else if(id / 10000000 == 21){
            fscanf(info_fp, "%d;", &midterm);
            fscanf(info_fp, "%d;", &final);
        }
        totFinal = totFinal + final;
        counter += 1;
    } while (fscanf(info_fp, "%d;", &id) == 1);
    
    fclose(info_fp);
    
    if (counter > 0) {
        average = totFinal / counter;
    }

    return average;
}





int instr_class(FILE * fp, int id){
    int current_id, class_count, dep;

    while (fscanf(fp, "%d;%d;%d", &current_id, &class_count, &dep) == 3) {
        if (current_id == id) {
            printf("Number of classes for instructor with ID %d is %d.\n", id, class_count);
            return class_count; 
        }
        
        char c;
        do {
            fscanf(fp, "%c", &c);
        } while (c != '\n' && c != EOF);
    }
    return 0; 
}


int role(FILE *fp, char role){
    int id, department, counter= 0;
    char rolef_letter, namef, c;
    
    while (fscanf(fp, "%d;%c", &id, &namef) == 2){
    
        
        do{
            fscanf(fp, "%c", &c);
        }while(c != ';');

        do{
            fscanf(fp, "%c", &c);
        }while(c != ';');
        
        fscanf(fp, "%c", &rolef_letter);
        
        if(role == rolef_letter){
            printf("%d ", id);
            do{
                fscanf(fp, "%c", &c);
            }while(c != ';');
        
            fscanf(fp, "%d", &department);
            printf("%d\n", department);
          
            counter++;
        }
        do{
            fscanf(fp, "%c", &c);
        }while(c != '\n');
    }
    
    return counter;
    
}

int find_course(FILE *info_fp, int stu_id){
    
    int current_id, midterm, midterm1, midterm2, final, lecture;
    
    while (fscanf(info_fp, "%d;", &current_id) == 1){ 
        
        if(stu_id == current_id){ 
            if(current_id > 220000000){
                fscanf(info_fp, "%d;%d;%d;%d", &midterm1, &midterm2, &final, &lecture);
                printf("Lecture: %d\n", lecture);
            }
            else if(current_id > 210000000 && current_id < 220000000){
                fscanf(info_fp, "%d;%d;%d", &midterm, &final, &lecture);
                printf("COURSE ID: %d\n", lecture);
            }
            else{
                printf("Please, enter a valid ID\n\n");
            }
            return lecture; 
        }
    }
    printf("ID not found.\n");
    return -1;
}

int main() {
    
    FILE *id_fp = fopen("second 1.txt", "r");
    FILE *info_fp = fopen("first 1.txt", "r");

    float midterm_avg = avg_mid(info_fp);
    float final_avg = avarage_final(info_fp);

    if (id_fp == NULL || info_fp == NULL) {
        printf("Error opening file");
        return -1;
    }

    char choice;
    int id;

    do {
        printf("\nMenu:\n");
        printf("p: Print all users pass or fail\n");
        printf("n: Print only the user with a specific first initial\n");
        printf("g: Calculate the GPA of a given student\n");
        printf("c: Print whether each user passed or failed the same class\n");
        printf("t: Print the number of classes for the instructor\n");
        printf("d: Print the department of all persons according to the role\n");
        printf("l: Print the course_id of a given student\n");
        printf("e: Quit the program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case 'p':
                 
                break;
            case 'n':
                char ch;
                printf("Enter the initial: ");
                scanf("%c", &ch);
                break;
            case 'g':
                printf("Enter student ID: ");
                scanf("%d", &id);
                average_grade(info_fp, id, midterm_avg, final_avg);
                break;
            case 'c':
                
                break;
            case 't':
                printf("Enter an ID: ");
                scanf("%d", &id);
                instr_class(info_fp, id);
                break;
            case 'd':
                char role_initial;
                printf("Enter the role initial ('s' for student, 'i' for instructor): ");
                scanf(" %c", &role_initial);
                role(id_fp, role_initial);
                break;
            case 'l':
                printf("Enter the ID: ");
                scanf("%d", &id);
                find_course(info_fp,id);
                break;
            case 'e':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 'e');

    fclose(id_fp);
    fclose(info_fp);

    return 0;
}

