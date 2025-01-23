#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customDict.h"

int main(){
    char filename[50], key[50], data_type[50];
    int num_values, i, j;
    Value value;
    int choose;
    /*Promt user for the filename*/
    printf("Enter the filename: ");
    scanf("%s", filename);

    /*Create a new dictionary and read data from the csv file*/
    CustomDict *dict = create_dict();
    read_csv(dict, filename);

    while (choose != 8){

        /*Display menu*/
        printf("1. Add an item to the dictionary.\n");
        printf("2. Delete item from the dictionary.\n");
        printf("3. Set the value of an item.\n");
        printf("4. Search for an item in the dictionary.\n");
        printf("5. Sort the dictionary.\n");
        printf("6. Print the dictionary.\n");
        printf("7. Free the dictionary.\n");
        printf("8. Exit.\n\n");
        printf("Choose an option: ");
        scanf("%d", &choose);

        switch(choose){
            case 1: /*Add item*/
                printf("Enter the key: ");
                scanf("%s", key);

                printf("Enter the data type: ");
                scanf("%s", data_type);

                printf("Enter the number of values: ");
                scanf("%d", &num_values);

                /*Allocate memory for the values*/
                if (strcmp(data_type, "int") == 0) {
                    value.int_val = malloc(num_values * sizeof(int));
                    for (i = 0; i < num_values; i++) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%d", &value.int_val[i]);
                    }
                } else if (strcmp(data_type, "float") == 0) {
                    value.float_val = malloc(num_values * sizeof(float));
                    for (i = 0; i < num_values; i++) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%f", &value.float_val[i]);
                    }
                }else if (strcmp(data_type, "double") == 0) {
                    value.double_val = malloc(num_values * sizeof(double));
                    for (i = 0; i < num_values; i++) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%lf", &value.double_val[i]);
                    }
                }else if (strcmp(data_type, "char") == 0) {
                    value.char_val = malloc(num_values * sizeof(char *));
                    for (i = 0; i < num_values; i++) {
                        value.char_val[i] = malloc(2 * sizeof(char));
                        printf("Enter value %d: ", i + 1);
                        scanf("%s", value.char_val[i]);
                    }
                }
                /*Add the item to the dictionary*/
                add_item(dict, key, value, data_type, num_values);
                break;
            case 2: /*Delete item*/
                printf("Enter the key: ");
                scanf("%s", key);
                delete_item(dict, key);
                break;
            case 3: /*Set value*/
                printf("Enter the key: ");
                scanf("%s", key);

                printf("Enter the data type: ");
                scanf("%s", data_type);

                printf("Enter the number of values: ");
                scanf("%d", &num_values);

                /*Allocate memory for the values*/
                if (strcmp(data_type, "int") == 0) {
                    value.int_val = malloc(num_values * sizeof(int));
                    for (i = 0; i < num_values; i++) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%d", &value.int_val[i]);
                    }
                } else if (strcmp(data_type, "float") == 0) {
                    value.float_val = malloc(num_values * sizeof(float));
                    for (i = 0; i < num_values; i++) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%f", &value.float_val[i]);
                    }
                }else if (strcmp(data_type, "double") == 0) {
                    value.double_val = malloc(num_values * sizeof(double));
                    for (i = 0; i < num_values; i++) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%lf", &value.double_val[i]); 
                    }
                }else if (strcmp(data_type, "char") == 0) {
                    value.char_val = malloc(num_values * sizeof(char *));
                    for (i = 0; i < num_values; i++) {
                        value.char_val[i] = malloc(2 * sizeof(char));
                        printf("Enter value %d: ", i + 1);
                        scanf("%s", value.char_val[i]);
                    }
                }
                set_value(dict, key, &value, data_type, num_values); /*Set the value of the item*/
                break;
            case 4: /*Search item*/
                printf("Enter the key to search: ");
                scanf("%s", key);
                search_item(dict, key);
                break;
            case 5: /*Sort dictionary*/
                sort_dict(dict);
                break;
            case 6: /*Print dictionary*/
                print_dict(dict);
                break;
            case 7: /*Free dictionary*/
                free_dict(dict);            
                printf("Dictionary is freed.\n");
                break;
            case 8: /*Exit*/
                printf("Exiting...\n");
                return 0;
                break;
            default:
                break;
        }
    }
}


