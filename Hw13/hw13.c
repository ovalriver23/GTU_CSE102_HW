#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INP_LEN 100 /*Maximum length for input string*/ 

/*Structure for storing species information*/
typedef struct SpeciesInfo {
    char class[MAX_INP_LEN];
    char order[MAX_INP_LEN];
    char family[MAX_INP_LEN];
    char genus[MAX_INP_LEN];
    char species[MAX_INP_LEN];
} SpeciesInfo;

/*Node structure*/
typedef struct Node {
    SpeciesInfo data;
    struct Node *next_species;
} Node;

/*Function prototypes*/
void add_species(Node **head);
void print_ll(Node *head);
void free_ll(Node *head);
void sort_the_ll(Node** head, char* criteria);
void delete_species(Node** head);
void modifySpecies(Node* head);


int main() {
    Node *head = NULL; /*Head of the linked list*/
    int choice;
    char list_cri[MAX_INP_LEN];
    do { /*Menu*/
        printf("1. Add Species\n");
        printf("2. Sort by criteria\n");
        printf("3. Display all species\n");
        printf("4. Modify species\n");
        printf("5. Delete species\n");
        printf("6. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: /*ADD SPECIES*/
                add_species(&head);
                break;
            case 2: /*SORT THE LINKED LIST*/
                printf("Enter list criteria (class, order, family, genus, species): ");
                scanf("%s", list_cri);
                sort_the_ll(&head, list_cri);
                print_ll(head);
                break;
            case 3: /*DISPLAY THE LINKED LIST*/
                print_ll(head);
                break;
            case 4: /*MODIFY THE LINKED LIST*/
                modifySpecies(head);
                break;
            case 5: /*DELETE A NODE FROM THE LINKED LIST*/
                delete_species(&head);
                break;
            case 6:
                printf("SEE YOU SOON\n");
                break;
            default:
                printf("CHOOSE FROM PROVIDED OPTIONS!!!\n");
                break;
        }
    } while (choice != 6);

    free_ll(head); /*FREE THE LINKED LIST*/
    return 0;
}


void add_species(Node **head) {
    SpeciesInfo specific_data;
    
    /*Get species information from the user*/
    printf("Enter class: ");
    fgets(specific_data.class, sizeof(specific_data.class), stdin); /*Read the class from the user*/
    specific_data.class[strcspn(specific_data.class, "\n")] = '\0'; /*Remove the newline character*/

    printf("Enter order: ");
    fgets(specific_data.order, sizeof(specific_data.order), stdin); /*Read the order from the user*/
    specific_data.order[strcspn(specific_data.order, "\n")] = '\0'; /*Remove the newline character*/

    printf("Enter family: ");
    fgets(specific_data.family, sizeof(specific_data.family), stdin); /*Read the family from the user*/
    specific_data.family[strcspn(specific_data.family, "\n")] = '\0'; /*Remove the newline character*/

    printf("Enter genus: ");
    fgets(specific_data.genus, sizeof(specific_data.genus), stdin); /*Read the genus from the user*/
    specific_data.genus[strcspn(specific_data.genus, "\n")] = '\0'; /*Remove the newline character*/

    printf("Enter species: ");
    fgets(specific_data.species, sizeof(specific_data.species), stdin); /*Read the species from the user*/
    specific_data.species[strcspn(specific_data.species, "\n")] = '\0'; /*Remove the newline character*/

    Node *newNode = (Node *)malloc(sizeof(Node)); /*Allocate memory for a new node*/
    newNode->data = specific_data; /*Assign the species information to the new node*/
    newNode->next_species = NULL; /*Set the next pointer to NULL*/

    if (*head == NULL) { /*If the linked list is empty*/
        *head = newNode; /*Set the new node as the head*/
    } else {
        Node *current = *head;
        while (current->next_species != NULL) { /*Traverse to the end of the linked list*/
            current = current->next_species;
        }
        current->next_species = newNode; /*Append the new node to the end of the linked list*/
    }
    printf("\n\nSpecies added\n\n");
}


void print_ll(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("Class: %s\n", current->data.class); /*Print the class of the species*/
        printf("Order: %s\n", current->data.order); /*Print the order of the species*/
        printf("Family: %s\n", current->data.family); /*Print the family of the species*/
        printf("Genus: %s\n", current->data.genus); /*Print the genus of the species*/
        printf("Species: %s\n\n", current->data.species); /*Print the species name*/
        current = current->next_species; /*Move to the next species in the linked list*/
    }
}

/*Function to free the memory allocated for the linked list*/
void free_ll(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next_species;
        free(tmp);
    }
}


void sort_the_ll(Node** head, char* criteria) {
    if (*head == NULL || (*head)->next_species == NULL) {
        return;
    }

    SpeciesInfo temp;
    Node *ce;
    int n = 0, cmp = 0, i;
    ce = *head;

    /*Count the number of nodes in the list*/
    while(ce != NULL) {
        n++;
        ce = ce->next_species;
    }

    /*Bubble sort*/
    for (i = 0; i < n - 1; i++) {
        ce = *head;
        while (ce->next_species != NULL) {
            /*Compare nodes based on the given criteria*/
            if (strcmp(criteria, "class") == 0) {
                cmp = strcmp(ce->data.class, ce->next_species->data.class);
            } else if (strcmp(criteria, "order") == 0) {
                cmp = strcmp(ce->data.order, ce->next_species->data.order);
            } else if (strcmp(criteria, "family") == 0) {
                cmp = strcmp(ce->data.family, ce->next_species->data.family);
            } else if (strcmp(criteria, "genus") == 0) {
                cmp = strcmp(ce->data.genus, ce->next_species->data.genus);
            } else if (strcmp(criteria, "species") == 0) {
                cmp = strcmp(ce->data.species, ce->next_species->data.species);
            }

            /*If the current node is greater than the next node, swap their data*/
            if (cmp > 0) {
                temp = ce->data;
                ce->data = ce->next_species->data;
                ce->next_species->data = temp;
            }
            ce = ce->next_species; /*Move to the next node*/
        }
    }
}


void delete_species(Node** head) {
    char species[MAX_INP_LEN];
    /*Read the species name to delete from the user input*/
    printf("Enter species to delete: ");
    fgets(species, sizeof(species), stdin);
    species[strcspn(species, "\n")] = 0;

    /*Check if the list is empty*/
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node *temp = *head, *prev = NULL;

    /*Check if the node to be deleted is the head node*/
    if (temp != NULL && strcmp(temp->data.species, species) == 0) {
        *head = temp->next_species; /*If the head node is to be deleted, update the head pointer*/
        free(temp); /*Free the memory allocated for the head node*/
        printf("Species '%s' deleted successfully.\n", species);
        return;
    }

    /*Traverse the list to find the node to be deleted*/
    while (temp != NULL && strcmp(temp->data.species, species) != 0) {
        prev = temp; /*Keep track of the previous node*/
        temp = temp->next_species; /*Move to the next node*/
    }

    /*If the species was not found in the list*/
    if (temp == NULL) {
        printf("Species '%s' not found.\n", species);
        return;
    }

    /*Unlink the node from the linked list*/
    if (prev != NULL) {
        prev->next_species = temp->next_species;
    }
    /*Free the memory allocated for the node to be deleted*/
    free(temp);
    printf("Species '%s' deleted successfully.\n", species);
}


void modifySpecies(Node* head) {
    char species[MAX_INP_LEN];
    /*Prompt user to enter the species name they want to modify*/
    printf("Enter species information to modify:\n");
    printf("Old species: ");
    fgets(species, sizeof(species), stdin);
    species[strcspn(species, "\n")] = 0;

    printf("Enter new information:\n");

    Node* ce = head;
    /*Traverse the linked list to find the node with the matching species name*/
    while (ce != NULL) {
        /*Compare the current node's species with the input species*/
        if (strcmp(ce->data.species, species) == 0) {
            /*If species matches, prompt user to enter new data for all fields*/
            printf("New class: ");
            fgets(ce->data.class, sizeof(ce->data.class), stdin);
            ce->data.class[strcspn(ce->data.class, "\n")] = 0;

            printf("New order: ");
            fgets(ce->data.order, sizeof(ce->data.order), stdin);
            ce->data.order[strcspn(ce->data.order, "\n")] = 0;

            printf("New family: ");
            fgets(ce->data.family, sizeof(ce->data.family), stdin);
            ce->data.family[strcspn(ce->data.family, "\n")] = 0;

            printf("New genus: ");
            fgets(ce->data.genus, sizeof(ce->data.genus), stdin);
            ce->data.genus[strcspn(ce->data.genus, "\n")] = 0;

            printf("New species: ");
            fgets(ce->data.species, sizeof(ce->data.species), stdin);
            ce->data.species[strcspn(ce->data.species, "\n")] = 0;

            printf("Species modified successfully.\n");
            return;
        }
        ce = ce->next_species; /*Move to the next node in the list*/
    }
    printf("Species not found.\n");
}

