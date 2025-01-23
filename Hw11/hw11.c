#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>

#define STREET_MAX 5
#define AVENUE_MAX 5
#define DECK_SIZE 52

/*Structure for the hospital*/
struct Hospital {
    char* name;
    char* citiesServed[3];
};

/*Structure for the cards*/
struct card{
    const char *face;
    const char *suit;
};

/*Function prototypes*/
int numPathHome(int street, int avenue);
int cities_Served(char *cities[], int cities_Count, struct Hospital *hospitals, int hospitals_Count, int *hospital_Used, int num_Hospitals, int *selected_Hospitals, int *selected_Count);
void shuffle(struct card *deck);

int main(){
    int choose;
    printf("\n*****WELCOME*****\n");
    printf("YOU CAN CHOOSE WHICH GAME YOU WANT TO PLAY BELOW\n\n");
    do{
        printf("1. Smart City Navigation\n");
        printf("2. Sustainable Health Services\n");
        printf("3. Virtual Card Game Mixer\n");
        printf("4. EXIT\n");
        printf("Choose the game to play: ");
        scanf("%d", &choose);

        /*Smart city nagivation*/
        if (choose == 1){
            int street, avenue;
            printf("Enter the street number: ");
            scanf("%d", &street);
            printf("Street: %d\n", street);
            printf("Enter the avenue number: ");
            scanf("%d", &avenue);
            printf("Avenue: %d\n", avenue);
            /*Calculate optimal paths to reach home*/
            int path_num = numPathHome(street, avenue);
            printf("Number of optimal paths to take back home: %d\n\n", path_num);
        }else if(choose == 2){ /*Sustainable Health Services*/
            int i, j;
            /*List of cities*/
            char* cities[] = { "A", "B", "C", "D", "E", "F" };
            /*List of hospital locations*/
            struct Hospital locations[] = {
                {"Hospital1", {"A", "B", "C"}},
                {"Hospital2",  {"A", "C", "D"}},
                {"Hospital3", {"B", "F"}},
                {"Hospital4", {"C", "E", "F"}},
            };
            int hospitalsCount = sizeof(locations) / sizeof(locations[0]); /*Calculate the number of hospitals*/
            int citiesCount = sizeof(cities) / sizeof(cities[0]); /*Calculate the number of cities*/
            int hospitalUsed[hospitalsCount]; /*Array to track used hospitals*/
            for (i = 0; i < hospitalsCount; i++) {
                hospitalUsed[i] = 0; /*Initialize hospital usage status*/
            }
            int selectedHospitals[hospitalsCount]; /*Array to store selected hospitals*/
            int selectedCount = 0; /*Variable to store the count of selected hospitals*/

            int numHospitals;
            printf("Enter the maximum number of hospitals that can be constructed: ");
            scanf("%d", &numHospitals);

            int result = cities_Served(cities, citiesCount, locations, hospitalsCount, hospitalUsed, numHospitals, selectedHospitals, &selectedCount);
            if (result) {
                printf("Yes, can offer health care to all!\n"); /*Display result if all cities are served*/
                for (i = 0; i < selectedCount; i++) { 
                    printf("Hospital - %d\n", i + 1);
                    printf("Hospital locations: ");
                    for (j = 0; j < 3; j++) {
                        if (locations[selectedHospitals[i]].citiesServed[j] != NULL) {
                            printf("%s ", locations[selectedHospitals[i]].citiesServed[j]); /*Display the cities served by each hospital*/
                        }
                    }
                    printf("\n");
                }
            } else {
                printf("No, it is not possible to offer health care to all with %d hospitals.\n", numHospitals);
            }
        }else if(choose == 3){ /*Virtual Card Game Mixer*/
            int i;
            const char *faces[] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; /*List of card faces*/
            const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"}; /*List of card suits*/
            struct card deck[DECK_SIZE]; /*Deck of cards*/

            /* Initialize the deck of cards*/
            for (i = 0; i < DECK_SIZE; i++) {
                deck[i].face = faces[i % 13];
                deck[i].suit = suits[i / 13];
            }
            shuffle(deck); /*Shuffle the deck of cards*/
        }else if(choose == 4){
            /*Exit the program*/
            printf("SEE YOU SOON!!!\n");
        }else{
            printf("INVALID INPUT. PLEASE CHOOSE FROM 1 TO 4\n");
        }
    }while(choose != 4); /*Repeat until the user chooses to exit*/

    return 0;
}

/*Function to calculate the number of optimal paths to reach target point*/
int numPathHome(int street, int avenue){
    if(street == 1 && avenue == 1){ /*Base case: reached target point*/
        return 1;
    }

    int left_path = 0;
    int down_path = 0;

    /*Recursive calls for left and down movements*/
    if (avenue > 1){
        left_path = numPathHome(street, avenue - 1); /*Move left*/
    }

    if (street > 1){
        down_path = numPathHome(street - 1, avenue); /*Move down*/
    }
    return left_path + down_path; /*Total paths*/
}

/*Function to check if all cities are served by selected hospitals*/
int cities_Served(char *cities[], int cities_Count, struct Hospital *hospitals, int hospitals_Count, int *hospital_Used, int num_Hospitals, int *selected_Hospitals, int *selected_Count) {
    int i, j, k;
    if (num_Hospitals == 0) { /*Base case: no more hospitals*/
        for (i = 0; i < cities_Count; i++) {
            int isCovered = 0; /*Flag to track city coverage*/
            for (j = 0; j < hospitals_Count; j++) {
                if (hospital_Used[j]) { /* Check if the hospital is selected*/
                    for (k = 0; k < 3; k++) {
                        if (hospitals[j].citiesServed[k] != NULL && strcmp(hospitals[j].citiesServed[k], cities[i]) == 0) {
                            isCovered = 1; /*Mark city as covered*/
                            break;
                        }
                    }
                }if (isCovered) break; /*Exit loop if city is covered*/
            }if (!isCovered) return 0; /*Return false if any city is not covered*/
        }
        return 1; /*Return true if all cities are covered*/
    }

    /*Recursive function to select hospitals and check city coverage*/
    for (i = 0; i < hospitals_Count; i++) {
        if (!hospital_Used[i]) { /*If hospital is not selected*/
            hospital_Used[i] = 1; /*Mark hospital as selected*/
            selected_Hospitals[*selected_Count] = i; /*Store selected hospital index*/
            (*selected_Count)++; /*Increment selected hospitals count*/
            if (cities_Served(cities, cities_Count, hospitals, hospitals_Count, hospital_Used, num_Hospitals - 1, selected_Hospitals, selected_Count)) {
                return 1; /*Recursively check city coverage*/
            }
            hospital_Used[i] = 0; /*Backtrack: mark hospital as not selected*/
            (*selected_Count)--; /*Decrement selected hospitals count*/
        }
    }
    return 0;
}

/*Function to shuffle a deck of cards*/
void shuffle(struct card *deck) {
    srand(time(NULL));  
    int i, j;
    for (i = DECK_SIZE - 1; i > 0; i--) {
        j = rand() % (i + 1);  /*Generate a random index*/
        struct card temp = deck[i]; /*Swap cards*/
        deck[i] = deck[j];
        deck[j] = temp;
    }
    /*Print shuffled deck*/
    for (i = 0; i < DECK_SIZE / 2; i++) {
        printf("%-5s of %-7s\t%-5s of %-8s\n", deck[i].face, deck[i].suit, deck[i + DECK_SIZE / 2].face, deck[i + DECK_SIZE / 2].suit);
    }
}



