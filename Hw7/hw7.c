#include <stdio.h>

#define row 2
#define column 7
#define stones_in_cup 4

void initializeGame(int board[row][column], int stones_in_Cup);
void printBoard(int board[row][column]);
void gamePlay(int board[row][column]);
void move(int board[row][column], int choice, int player);

int main() {
    int board[row][column];

    initializeGame(board, stones_in_cup);
    printBoard(board);
    gamePlay(board);

    return 0;
}
/* Initialize the game board with stones in each cup */
void initializeGame(int board[row][column], int stones_in_Cup) {
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            board[i][j] = stones_in_Cup;
        }
        board[i][6] = 0; /*Large cups is initially empty*/
    }
}

/*Print the game board*/
void printBoard(int board[row][column]) {
    int i;
    printf("+----+----+----+----+----+----+----+----+\n");
    printf("|    |");

    for (i = 0; i < 6; i++) {
        printf(" %2d |", board[0][i]);
    }

    printf("    |\n| %2d ", board[0][6]);
    printf("|----+----+----+----+----+----| %2d |\n", board[1][6]);
    printf("|    |");

    for (i = 0; i < 6; i++) {
        printf(" %2d |", board[1][i]);
    }

    printf("    |\n+----+----+----+----+----+----+----+----+\n");
}

/*Game Play logic*/
void gamePlay(int board[row][column]) {
    int choice, computer_choice, i, player_empty = 1, computer_empty = 1;

    while (1) {
        do {
            printf("Enter your move (1-6): ");
            scanf("%d", &choice);
            if (choice < 1 || choice > 6 || board[1][choice - 1] == 0) {
                printf("PLEASE ENTER A VALID MOVE!!!\n");
            }
        } while (choice < 1 || choice > 6 || board[1][choice - 1] == 0);

        move(board, choice, 1); /*Players move*/

        /* Computers turn */
        for (i = 5; i >= 0; i--) { 
            if (board[0][i] != 0) {
                computer_choice = i + 1;
                break;
            }
        }

        printf("Computer chooses cup %d.\n", computer_choice);
        move(board, computer_choice, 0); /*Computer move*/
        
        /* Check if player's side is empty */
        player_empty = 1;
        for (i = 0; i < 6; i++) {
            if (board[1][i] != 0) {
                player_empty = 0;
                break;
            }
        }
        
        /* If player's side is empty, end the game */
        if (player_empty) {
            break; 
        }
    }

    /* Check who is the winner */
    if (board[1][6] > board[0][6]) {
        printf("\nPlayer WON\n");
    }
    else if (board[1][6] < board[0][6]) {
        printf("\nComputer WON\n");
    } else {
        printf("\nBoth won\n");
    }
}


/*Move stones in the board based on the player's choice*/
void move(int board[row][column], int choice, int player) {
    int stones, current_cup, last_cup;
    int computer_side = !player; 
    
    stones = board[player][choice - 1]; /*Number of stones in the chosen cup.*/
    board[player][choice - 1] = 0; 

    current_cup = choice - 1; /*Index of the chosen cup.*/

    do {
        last_cup = -1; 
        while (stones > 0) {
           
            if (player == 1) {
                current_cup = (current_cup + 1) % column; 
            } else { 
                current_cup = (current_cup - 1 + column) % column; 
            }
            
            /*Skip the large cup if it's not the player's turn*/
            if (player == 0 && current_cup == 6) {
                current_cup = (current_cup - 1 + column) % column; 
            }
            
            /*If the last stone lands in the player's large cup, get another move*/
            if (player == 1 && current_cup == 6) {
                board[player][current_cup]++;
                stones--; 
                if (stones > 0) {
                    player = 0;
                    current_cup = 0; 
                }
                continue; 
            }
            
            board[player][current_cup]++;
            stones--; 
            
            printBoard(board);
            
            
            if (stones == 0) {
                last_cup = current_cup;
            }
        }
        
        /*If the last stone lands in an empty cup on the player's side, capture stones from opposite side*/
        if (last_cup != -1 && board[player][last_cup] > 1) {
            stones = board[player][last_cup];
            board[player][last_cup] = 0; 
            
            
            if (last_cup == 0 && player == 0) {
            player = 1;
            current_cup = 0; 
            }
        }
        
    } while (stones > 0);

    /* If the last stone lands in the player's large cup, get another move*/
    if (current_cup == 6 && player == 1) {
        printf("Last stone landed in the large cup. Choose another cup (1-6): ");
        scanf("%d", &choice);
        move(board, choice, 1);
    }
}
