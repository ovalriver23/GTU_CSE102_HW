#include <stdio.h>

/*Given alphabet of characters*/
char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int main(){
    char c, comment_marker = '@'; /*Variable to hold input character and comment marker*/
    long long int student_id = 230104004903;  /*Student ID*/
    int key, sum = 0, ch; /* Key and variable to store sum of the digits from studen ID*/
    

    if(student_id < 0){ /*If student ID less than zero it will give error */
        printf("Student ID must be a positive number!!!!\n");
        return -1;
    }
    
    while (student_id > 0 || sum > 9){ /*Calculates the key from student ID */
        if (student_id == 0){
            student_id = sum; /*Adds the last digit to the sum*/
            sum = 0; /*Removes the last digit from the student ID*/
        }
        sum += student_id % 10;
        student_id /= 10;
    }

    key = sum; /*Assings the sum of the digits in the student ID to the key value*/


    /*Decryption part*/

    while (scanf("%c", &c) != EOF){ /*Reads the charecter until the file is ended*/

        if (c == comment_marker) {   /*Check if the current character is a comment marker*/
            scanf("%d", &ch); /*Scans the numbers after the comment marker*/
            printf("/* There is %d characters as comment. */", ch);   
        } else {
            int i;
            for ( i = 0; i < 61; i++){ /*Iterates throught the alphabet array*/
                if (c == alphabet[i]){ /*Checks if the current character c from the input matches with the character at index i in the alphabet array. */
                    printf("%c", alphabet[(i - key + 61) % 61]); /*If the character c matches with the character at index i, it means we found the character in the alphabet array.
                                                                 Now, it's decrypting the character using the Caesar's method.*/
                    break;
                }   
            }
          
        }            
            if (c == '\n' || c == ' '){ /*Skips the new line and spaces*/
                printf("%c", c);
            }
    }
    
    return 0;

}