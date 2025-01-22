#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define board_size 16  
#define empty_place '.' /* Represents an empty cell */
#define wall '#'  /* Represents a wall */
#define first_year '1' /* Symbol for first-year ECTS */
#define second_year '2'  /* Symbol for second-year ECTS */
#define point 'P'  /* Symbol for player position */
#define finish 'X' /* Symbol for the finish point */
#define dis_wall_1 2  /* Distance of first wall from the center */
#define dis_wall_2 4 /* Distance of second wall from the center */

/* Function prototypes */
int find_index(int column, int row);
void initialize_game();
void print_board();
void move_player(char direction);

/* Global variables */
char board[board_size * board_size];
int p_pos, new_pos;
int total_ects = 0, total_move = 0;

int main(){
    char direction;

    initialize_game();
    print_board();

    while (1){

        printf("Total ECTS: %d\n", total_ects);
        printf("Enter your move: ");
        scanf(" %c", &direction);

        move_player(direction); /* Move the player according to the input direction */
        print_board(); /* Print the updated board */

        total_move++; /* Increment the total moves */

         /* Check if the player has reached the finish point */
        if (p_pos == find_index(board_size - 1, board_size - 1)){
        printf("Congratulations! You have reached the finish point.\n");
        printf("Total ECTS: %d\n", total_ects);
        printf("Total movements: %d\n", total_move);
        break;
        }
    }
    return 0;
}

/* Function to calculate the index in the board array from column and row */
int find_index(int column, int row){
    int index = column * board_size + row;
    return index;
}
/* Function to initialize the game board */
void initialize_game(){
    int i, j,center, x, y, counter = 0;
    srand(time(NULL));

     /* Initialize the board with empty places */
    for (i = 0; i < board_size * board_size; i++){
        board[i] = empty_place;
    }


    center = board_size / 2;
    /* Place the player at the center of the board */
    board[find_index(center, center)] = point;
    p_pos = find_index(center, center);

       /* Place walls around the center */
    for (i = center - dis_wall_1; i <= center + dis_wall_1; i++){
        for (j = center - dis_wall_1; j  <= center + dis_wall_1; j++){
            if (i == center - dis_wall_1 || i == center + dis_wall_1 || j == center - dis_wall_1 || j == center + dis_wall_1){
                board[find_index(i, j)] = wall;
            }
        }
    }

    /* Place second set of walls */
    for (i = center - dis_wall_2; i <= center + dis_wall_2; i++) {
        for (j = center - dis_wall_2; j <= center + dis_wall_2; j++) {
            if (i == center - dis_wall_2 || i == center + dis_wall_2 || j == center - dis_wall_2 || j == center + dis_wall_2) {
                board[find_index(i, j)] = wall;
            }
        }
    }


    /* Place first-year ECTS */
    counter = 0;
    while (counter < 4) {
        int x = center - 1 + rand() % 3;
        int y = center - 1 + rand() % 3;
        if (board[find_index(x, y)] == empty_place) {
            board[find_index(x, y)] = first_year;
            counter++;
        }
    }

    /* Place second-year ECTS */
    counter = 0;
    while(counter < 3) {
        int x = rand() % (board_size - 8) + 4;
        int y = rand() % (board_size - 8) + 4; 

        if (board[find_index(x, y)] == empty_place && (x < center - 1 || x > center + 1 || y < center - 1 || y > center + 1)) {
            board[find_index(x, y)] =  second_year;
            counter++;
        }
    }
}


/* Function to print the game board */
void print_board(){
    int x, y;
    for (x = 0; x < board_size; x++){
        for (y = 0; y < board_size; y++){
            if (x == board_size -1 && y == board_size -1){
                printf("%c ", finish);
            }else{
                printf("%c ", board[find_index(x, y)]);
            } 
        }
        printf("\n");
    }
}


/* Function to move the player */
void move_player(char direction){
    new_pos = p_pos;

    if (direction == 'a' || direction == 'A'){
        if (p_pos % board_size == 0){
            printf("YOU CAN'T MOVE OUTSIDE OF THE BOARD\n");
            return ;
        }
        new_pos = p_pos - 1;
    }else if(direction == 'w' || direction == 'W'){
        if (p_pos / board_size == 0){
            printf("YOU CAN'T MOVE OUTSIDE OF THE BOARD\n");
            return ;
        }
        new_pos = p_pos - board_size;
    }else if(direction == 's' || direction == 'S'){
        if (p_pos / board_size == (board_size - 1)){
            printf("YOU CAN'T MOVE OUTSIDE OF THE BOARD\n");
            return ;
        }
        new_pos = p_pos + board_size;
    }else if(direction == 'd' || direction == 'D'){
        if (p_pos % board_size == board_size -1){
            printf("YOU CAN'T MOVE OUTSIDE OF THE BOARD\n");
            return ;
        }
        new_pos = p_pos + 1;   
    }else{
        printf("PLEASE ENTER A VALID DIRECTION!!!");
        return ;
    }

     /* Collect ECTS if present in the new position */
    if (board[new_pos] == first_year || board[new_pos] == second_year){
        total_ects = total_ects + 8;
    }

    
    /* Check if the player encounters a wall and has enough ECTS to pass */
    if (board[new_pos] == wall){
        int center = board_size / 2;
        int i = new_pos / board_size;
        int j = new_pos % board_size;
        if ((i >= center - 2 && i <= center + 2 && j >= center - 2 && j <= center + 2) && total_ects < 32){
            printf("Warning: You have not collected enough ECTS to pass the first wall.\n");
            return;
        }
        else if ((i < center - 2 || i > center + 2 || j < center - 2 || j > center + 2) && total_ects < 56){
            printf("Warning: You have not collected enough ECTS to pass the second wall.\n");
            return;
        }
    }
    
    board[p_pos] = empty_place; /*Update the current position of the player to empty*/
    p_pos = new_pos; /*Update the player's position*/
    board[p_pos] = point; /*Place the player symbol in the new position*/

}