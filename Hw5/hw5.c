#include<stdio.h>
#include<locale.h>

/* Function prototypes */
int display_news(); 
int menu(int news_read[]); 
void save_read_news(int news_read[]);
void load_read_news(int news_read[]);
int f(int num);
int g(int num);

int main(){
    setlocale(LC_ALL, "Turkish"); /*Set the locale to turkish to display turkish characters*/
    int news_read[4] = {0}; /* Array to store read status of news */
    load_read_news(news_read);
    display_news();
    menu(news_read);
    save_read_news(news_read);

    return 0;
}
/* Function to save news to a file */
void save_read_news(int news_read[]) {
    FILE *write_status = fopen("readed_news_id.txt", "w"); /* Open file for writing */
    if (write_status == NULL) { /* Check if file opening is successful */
        printf("ERROR OPENING THE FILE FOR WRITING!!!"); /* Print error message if opening fails */
        return;
    }
    for (int i = 0; i < 4; i++) { /* Loop through each news item */
        fprintf(write_status, "%d\n", news_read[i]);  /* Write read news to file */
    }
    fclose(write_status); /* Close the file */
}

/* Function to read the news status from the file */
void load_read_news(int news_read[]) {
    FILE *read_status = fopen("readed_news_id.txt", "r"); /* Open file for reading */
    if (read_status != NULL) { /* Check if file opening is successful */
        for (int i = 0; i < 4; i++) {  /* Loop through each news item */
            fscanf(read_status, "%d", &news_read[i]); /* Read the status of the news from the file*/
        }
        fclose(read_status); /* Close the file */
    } else {
        printf("ERROR OPENING THE FILE FOR READING!!!"); /* Print error message if opening fails */
    }
}

/* Function to display news */
int display_news() {
    char c;
    int title_no = 1;
    FILE *first, *second, *third, *fourth;

    /*Open the files for reading*/
    first = fopen("1.txt", "r");
    second = fopen("2.txt", "r");
    third = fopen("3.txt", "r");
    fourth = fopen("4.txt", "r");

    /*Check if all files are opened successfully*/
    if (first == NULL || second == NULL || third == NULL || fourth == NULL) {
        printf("ERROR IN OPENING ONE OF THE FILES\n");
        return -1; /*Return -1 to indicate error */
    }

    printf("\n\n**************Daily Press**************\n\n");
    printf("Today's news are listed for you :\n\n");

    /*Printing the title of news*/
    printf("Title of %d. news: ", title_no++);
    while (fscanf(first, "%c", &c) != EOF && c != '\n') {
        printf("%c", c); /*Printing the characters until the new line*/
    }
    printf("\n");

    printf("Title of %d. news: ", title_no++);
    while (fscanf(second, "%c", &c) != EOF && c != '\n') {
        printf("%c", c);
    }
    printf("\n");

    printf("Title of %d. news: ", title_no++);
    while (fscanf(third, "%c", &c) != EOF && c != '\n') {
        printf("%c", c);
    }
    printf("\n");

    printf("Title of %d. news: ", title_no++);
    while (fscanf(fourth, "%c", &c) != EOF && c != '\n') {
        printf("%c", c);
    }
    printf("\n");

    /*Close all the files*/
    fclose(first);
    fclose(second);
    fclose(third);
    fclose(fourth);

    return 0;
}

/*Function to calculate the x^3 - X^2 + 2*/
int f(int x) {
    return x * x * x - x * x + 2;
}

/*Function to calculate the X^2*/
int g(int x) {
    return x * x;
}

/* Function to display menu */
int menu(int news_read[]){
    int news_choice, i, read_again;
    char choice, cont_choice, ch, bukva;
    int magic_num, result1, result2, sum = 0;

    /*Opening files for reading*/
    FILE *first = fopen("1.txt", "r");
    FILE *second = fopen("2.txt", "r");
    FILE *third = fopen("3.txt", "r");
    FILE *fourth = fopen("4.txt", "r");
   
    /*Checking if files are opened successfully*/
    if(first == NULL || second == NULL || third == NULL || fourth == NULL){
        printf("Error in opening one of the files!!");
        return -1;
    }
    

    /*Main loop for user interaction*/
    do{
        printf("What you want to do?\na. Read a news\nb. List the read news\nc. Get decrypted information from the news\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice); 

        switch (choice){
        case 'a':
            printf("Which news you want to read?\n");

            /*Loop to ensure valid news choice input*/
            while (1){
                scanf("%d", &news_choice);
                if (news_choice >= 1 && news_choice <= 4){
                    break;
                }else{
                    printf("ENTER ONE OF THE VALID NEWS!!!!\n");
                }
            }

            /*Checking if the news is already read*/
            if (news_read[news_choice - 1] == 1){
                printf("This news is readed. Do you want to read it again? Yes(1) / No(0): ");
                scanf("%d", &read_again);
                if (read_again == 1){
                    news_read[news_choice -1] = 0;
                }else{
                    break;
                }
            }


            /*Depending on users choice this part displaying the whole text of the news*/
            if (news_choice == 1){
                fclose(first);
                first = fopen("1.txt", "r");
                while (fscanf(first, "%c", &ch) != EOF){
                    printf("%c", ch);
                }
            } else if (news_choice == 2){
                fclose(second);
                second = fopen("2.txt", "r");
                while (fscanf(second, "%c", &ch) != EOF){
                    printf("%c", ch);
                }
            } else if (news_choice == 3){
                fclose(third);
                third = fopen("3.txt", "r");
                while (fscanf(third, "%c", &ch) != EOF){
                    printf("%c", ch);
                }
            } else if (news_choice == 4){
                fclose(fourth);
                fourth = fopen("4.txt", "r");
                while (fscanf(fourth, "%c", &ch) != EOF){
                    printf("%c", ch);
                }
            }
            /*Marking the news as read*/
            news_read[news_choice - 1] = 1;
            break;
        case 'b':
            /*Listing read news*/
            printf("Readed news listed below: \n");
            for (i = 0; i < 4; i++){
                if (news_read[i] == 1){
                    printf("%d. news is readed\n", i+1);
                }
            }
            break;
        case 'c':
            int dec_news;
            printf("Which news would you like to decrypt?: ");
            scanf("%d", &dec_news);
            sum = 0;
            /*Based on user input displaying the news and decrypting it*/
            if (dec_news == 1){
                fclose(first);
                first = fopen("1.txt", "r");
                while (fscanf(first, "%c", &ch) != EOF){
                    printf("%c", ch);
                    if (ch == '#'){ /*If the read character is #*/
                        fscanf(first, "%d", &magic_num); /*It is reading next char after the #*/
                        result1 = f(magic_num); /*Decrypting the char after the #*/
                        result2 = g(result1);
                        sum = sum + result2;
                    }
                }
                printf("\n\nThe secret number is: %d\n", sum);
                sum = 0;
                /*Decrypting the second text*/
            }else if(dec_news == 2){
                fclose(second);
                second = fopen("2.txt", "r");
                 while (fscanf(second, "%c", &ch) != EOF){
                    printf("%c", ch);
                    if (ch == '#'){
                        fscanf(second, "%d", &magic_num);
                        result1 = f(magic_num);
                        result2 = g(result1);
                        sum = sum + result2;
                    }
                }
                printf("\n\nThe secret number is: %d\n", sum);
                sum = 0;
                /*Decypting the third text*/
            }else if (dec_news == 3){
                fclose(third);
                third = fopen("3.txt", "r");
                 while (fscanf(third, "%c", &ch) != EOF){
                    printf("%c", ch);
                    if (ch == '#'){
                        fscanf(third, "%d", &magic_num);
                        result1 = f(magic_num);
                        result2 = g(result1);
                        sum = sum + result2;
                    }
                }
                printf("\n\nThe secret number is: %d\n", sum);
                sum = 0;
                /*Decrypting the fourth text*/
            }else if(dec_news == 4){
                fclose(fourth);
                fourth = fopen("4.txt", "r");
                 while (fscanf(fourth, "%c", &ch) != EOF){
                    printf("%c", ch);
                    if (ch == '#'){
                        fscanf(fourth, "%d", &magic_num);
                        result1 = f(magic_num);
                        result2 = g(result1);
                        sum = sum + result2;
                    }
                }
                printf("\n\nThe secret number is: %d\n", sum);
            }
            break;
        default:
            printf("INVALID CHOICE!!!");
            break;
        }

        /*Loop for asking the user if they want to continue reading news*/
        while (1) {
            /*Prompting the user for input*/
            printf("\nDo you want to continue reading a different news item? Yes(y)/No(n) : ");
            /*Reading the user's choice*/
            scanf(" %c", &cont_choice); 
            /*Checking if the user's choice is valid*/
            if (cont_choice == 'Y' || cont_choice == 'N' || cont_choice == 'y' || cont_choice == 'n') {
                break;
            } else {
                printf("INVALID CHOICE!!!!\n");
            }
        }

    } while (cont_choice == 'Y' || cont_choice == 'y'); /*Continuing the outer loop if user wants to continue*/

    printf("Goodbye!\n");

    /*Closing opened files*/
    fclose(first);
    fclose(second);
    fclose(third);
    fclose(fourth);

    return 0;
    
}