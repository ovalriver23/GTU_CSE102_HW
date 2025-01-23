#include <stdio.h>

#define MAX_H 100
#define MAX_W 100
#define MAX_F 100

typedef struct {
    char map[MAX_H][MAX_W];
    int width;
    int height;
    int num_flowers;
    int flower_x[MAX_F];
    int flower_y[MAX_F];
} Forest;

typedef struct {
    int coord_x;
    int coord_y;
    int number_of_bottle;
    int collected_flowers;
} Botanist;

/*Function prototypes*/
int init_game(Forest *forest, Botanist *botanist);
void display_forest(Forest forest, Botanist botanist);
void search(Forest *forest, Botanist *botanist, char move);
void last_view(Forest forest, Botanist botanist); /*Function to save the last view of the map*/

int main() {
    Forest forest;
    Botanist botanist;
    char move;
    init_game(&forest, &botanist);
    display_forest(forest, botanist);

    do {
        printf("Enter direction (u (up), d (down), l (left), r (right), e (exit)): ");
        scanf(" %c", &move);
        if (move != 'e') {
            search(&forest, &botanist, move);
        }
        if (move == 'e') {
            printf("SEE YOU SOON!!");
            last_view(forest, botanist);
            return 0;
        }
    } while (botanist.collected_flowers < forest.num_flowers && move != 'e');

    /*IF all the rare flowers are collected, save the last view of the game and exit the program*/
    if (botanist.collected_flowers == forest.num_flowers){
        printf("Congratulations! You've collected all the flowers!\n");
        last_view(forest, botanist);
        return 0;
    }
    return 0;
}

int init_game(Forest *forest, Botanist *botanist) {
    int i, j;
    /*Open the file for reading*/
    FILE *init = fopen("init.txt", "r");
    char ch;

    /*Check if the file was opened successfully, if not print the error message*/
    if (init == NULL) {
        printf("ERROR OPENING THE FILE INIT.TXT");
        return 1;
    }
    /*Read the first two lines in the file*/
    fscanf(init, "%d,%d", &forest->height, &forest->width); 
    fscanf(init, "%d,%d,%d", &botanist->coord_x, &botanist->coord_y, &botanist->number_of_bottle);
    
    /*Initiazlize the number of collected flowers to zero*/
    botanist->collected_flowers = 0;

    /*Nested for loop to go over the map*/
    for (i = 0; i < 2 * forest->height; i++) { 
        for (j = 0; j < 2 * forest->width - 1; j++) {
            ch = fgetc(init); /*Read the character from the file*/
            if (ch == ',') {
                continue; /*Skip commas*/
            }
            if (ch == '\n') {
                break; /*Move to the next line*/
            }
            forest->map[i / 2][j / 2] = ch; /*Store the readed character to the 2d map array*/
            if (ch == 'X') { /*If the readed character is X, store the coordinates*/
                forest->flower_x[forest->num_flowers] = i / 2; 
                forest->flower_y[forest->num_flowers] = j / 2;
                forest->num_flowers++; /*Increment the number of flowers*/
            }
        }
    }
    fclose(init);
    return 0;
}

void display_forest(Forest forest, Botanist botanist) {
    int i, j;
    /*Display the number of collected flowers, left water bottles and botanist coordiantes*/
    printf("\nNumber of collected flowers: %d\n", botanist.collected_flowers);
    printf("Left water bottles: %d\n", botanist.number_of_bottle);
    printf("Botanist position: (%d, %d)\n", botanist.coord_x, botanist.coord_y);

    /*Loop over the rows and columns of the forest*/
    for (i = 0; i < forest.height; i++) {
        for (j = 0; j < forest.width; j++) {
            printf("%c", forest.map[i][j]); /*Print the charater at the current position*/
            if (j < forest.width - 1) {
                printf(","); /*Print the comma after each character exept the last one in row*/
            }
        }
        printf("\n");
    }
}

void search(Forest *forest, Botanist *botanist, char move) {
    /*Variable to store the new botanist coordinates*/
    int new_x_coord = botanist->coord_x;
    int new_y_coord = botanist->coord_y;
    int i;

    /*Update the botanist coordinates based on the user input*/
    switch (move) {
        case 'u':
            new_x_coord--; 
            break;
        case 'd':
            new_x_coord++;
            break;
        case 'l':
            new_y_coord--;
            break;
        case 'r':
            new_y_coord++;
            break;
        default:
            printf("Invalid direction!\n");
            return;
    }

    /*If the new position is outside of the forest, print the error message*/
    if (new_x_coord < 0 || new_y_coord < 0 || new_x_coord >= forest->height || new_y_coord >= forest->width) {
        printf("DON'T TRY TO ESCAPE THE FOREST!\n");
        return;
    }

    /*If there is a tree at the new position, print the error message*/
    if (forest->map[new_x_coord][new_y_coord] == 'T') {
        printf("THERE IS A TREE!!!\n");
        return;
    }

    forest->map[botanist->coord_x][botanist->coord_y] = ' '; /*Clear the current position of the botanist in the map*/ 
    botanist->coord_x = new_x_coord; /*Update the x-coordinate of the botanist*/
    botanist->coord_y = new_y_coord; /*Update the y-coordinate of the botanist*/
    forest->map[new_x_coord][new_y_coord] = 'B'; /*Mark the new position of the botanist in the map*/
    
    display_forest(*forest, *botanist); /*Display the forest*/

    for (i = 0; i < forest->num_flowers; i++) { /*Loop over the flowers*/
        /*If the botanist new position is a flower*/
        if (new_x_coord == forest->flower_x[i] && new_y_coord == forest->flower_y[i]) {
            botanist->collected_flowers++; /*Increment the number of collected flower*/
            botanist->number_of_bottle--; /*Decrement the number of water bottles*/
            display_forest(*forest, *botanist); /*Display the forest*/
            printf("I've found it\n"); /*Display the message indicating that a flower is found*/
            return;
        }
    }
    /*Ask the user input*/
    printf("Enter direction (u (up), d (down), l (left), r (right), e (exit)): ");
    scanf(" %c", &move);
    /*After reading the user input, the program calls itself to move the botanist accordingly*/
    search(forest, botanist, move);
}

void last_view(Forest forest, Botanist botanist) {
    int i, j;
    FILE *last = fopen("last.txt", "w"); /*Open file for writing*/
    if (last == NULL) { /*Check the file, if it was opened successfully*/
        printf("Error opening file for writing.");
        return;
    }

    /*Write the number of collected flowers, left water bottles and botanist last position to the file*/
    fprintf(last, "Number of collected flowers: %d\n", botanist.collected_flowers);
    fprintf(last, "Left water bottles: %d\n", botanist.number_of_bottle);
    fprintf(last, "Botanist position: (%d, %d)\n", botanist.coord_x, botanist.coord_y);

    for (i = 0; i < forest.height; i++) { /*Loop over the rows*/
        for (j = 0; j < forest.width; j++) { /*Loop over the columns*/
            fprintf(last, "%c", forest.map[i][j]); /*Print the character at the current position to the file */
            if (j < forest.width - 1) { /*If the current position is not the last one in the row write a comma after the character*/
                fprintf(last, ",");
            }
        }
        fprintf(last, "\n");
    }
    fclose(last);
}