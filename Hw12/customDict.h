#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUES 50 /*Maximum number of values for each key*/

/*Define a union to hold different types of values*/
typedef union Value {
    int *int_val;
    float *float_val;
    double *double_val;
    char **char_val; 
} Value;

/*Define a struct to hold an item in the dictionary*/
typedef struct Item {
    char *key;
    Value value;
    char *dtype;
    int num_values; 
} Item;

/*Structure to represent a custom dictionary*/
typedef struct CustomDict {
    Item *itemArr; /*Array of items*/
    int capacity; /*Capacity of the dictionary*/
    int current_size; /*Current size of the dictionary*/
} CustomDict;


/* Function prototypes */
CustomDict* create_dict();
void add_item(CustomDict *dict, char *key, Value value, char *dtype, int num_values);
union Value* search_item(struct CustomDict* dict, char* key);
void delete_item(CustomDict *dict, char *key);
void set_value(CustomDict *dict, char *key, Value *value, const char *dtype, int num_values);
void sort_dict(CustomDict *dict);
void print_dict(CustomDict *dict);
char* remove_NL(char *str);
int read_csv(CustomDict* dict, const char* filename);
void free_dict(CustomDict* dict);

/* Function to create a new dictionary*/
CustomDict* create_dict() {
    CustomDict *dict = (CustomDict *)malloc(sizeof(CustomDict)); /*Allocate memory for the dictionary*/
    dict->itemArr = NULL;
    dict->capacity = 0;
    dict->current_size = 0; 
    return dict; /*Return the created dictionary*/
}

void add_item(CustomDict *dict, char *key, Value value, char *dtype, int num_values) {
    int i, j;
    if (dict == NULL || key == NULL){ 
        return;
    }
    /*Remove leading spaces from the key*/
    while (*key == ' ') {
        key++;
    }
    /*Check if the key already exists*/
    for (i = 0; i < dict->current_size; i++) {
        if (strcmp(dict->itemArr[i].key, key) == 0) { /*If the key already exists*/
            if (strcmp(dict->itemArr[i].dtype, dtype) == 0) { /*If the data type matches*/
                int newNum = dict->itemArr[i].num_values + num_values; /*Calculate the new number of values*/

                /*Reallocate memory and append new values based on data type*/
                if (strcmp(dtype, "int") == 0) {
                    dict->itemArr[i].value.int_val = (int *)realloc(dict->itemArr[i].value.int_val, newNum * sizeof(int));
                    for (j = 0; j < num_values; j++) {
                        dict->itemArr[i].value.int_val[dict->itemArr[i].num_values + j] = value.int_val[j]; /*Append new values*/
                    }
                } else if (strcmp(dtype, "float") == 0) {
                    dict->itemArr[i].value.float_val = (float *)realloc(dict->itemArr[i].value.float_val, newNum * sizeof(float));
                    for (j = 0; j < num_values; j++) {
                        dict->itemArr[i].value.float_val[dict->itemArr[i].num_values + j] = value.float_val[j];
                    }
                } else if (strcmp(dtype, "double") == 0) {
                    dict->itemArr[i].value.double_val = (double *)realloc(dict->itemArr[i].value.double_val, newNum * sizeof(double));
                    for (j = 0; j < num_values; j++) {
                        dict->itemArr[i].value.double_val[dict->itemArr[i].num_values + j] = value.double_val[j];
                    }
                } else if (strcmp(dtype, "char") == 0) {
                    dict->itemArr[i].value.char_val = (char **)realloc(dict->itemArr[i].value.char_val, newNum * sizeof(char *));
                    for (j = 0; j < num_values; j++) {
                        int len = strlen(value.char_val[j]); 
                        dict->itemArr[i].value.char_val[dict->itemArr[i].num_values + j] = (char *)malloc(len + 1); 
                        if (dict->itemArr[i].value.char_val[dict->itemArr[i].num_values + j] != NULL) { 
                            strcpy(dict->itemArr[i].value.char_val[dict->itemArr[i].num_values + j], value.char_val[j]); 
                        }
                    }
                }
                dict->itemArr[i].num_values = newNum; /*Update the number of values*/
                return;
            } else {
                printf("DATA TYPE DOESNT MATCH FOR THE KEY: '%s'.\n", key);
                return;
            }
        }
    }

    /*If the key does not exist, proceed to add as a new item*/

    /*Check if the capacity needs to be increased*/
    if (dict->capacity <= dict->current_size) {
        dict->capacity += 1;
        /*Reallocate memory for the item array with the new capacity*/
        dict->itemArr = (Item *)realloc(dict->itemArr, dict->capacity * sizeof(Item));
        if (dict->itemArr == NULL) {
            printf("MEMORY ALLOCATION FAILED\n");
            return;
        }
    }
    /*Add the new item*/
    int key_len = strlen(key); /*Calculate the length of the key*/
    dict->itemArr[dict->current_size].key = (char*)malloc(key_len + 1); /*Allocate memory for the key*/
    if (dict->itemArr[dict->current_size].key == NULL) {
        printf("MEMORY ALLOCATION FAILED\n");
        return;
    }
    strcpy(dict->itemArr[dict->current_size].key, key); /*Copy the key to the item*/

    memcpy(&dict->itemArr[dict->current_size].value, &value, sizeof(Value)); /*Copy the value to the item*/

    int dtype_len = strlen(dtype); /*Calculate the length of the data type*/
    dict->itemArr[dict->current_size].dtype = (char *)malloc(dtype_len + 1); /*Allocate memory for the data type*/
    if (dict->itemArr[dict->current_size].dtype == NULL) {
        printf("MEMORY ALLOCATION FAILED\n");
        free(dict->itemArr[dict->current_size].key);
        return;
    }
    strcpy(dict->itemArr[dict->current_size].dtype, dtype); /*Copy the data type to the item*/

    dict->itemArr[dict->current_size].num_values = num_values; /*Set the number of values for the item*/

    dict->current_size++; /*Increment the current size of the dictionary*/
}

/*unction to search for a value associated with a given key in a custom dictionary.*/
union Value* search_item(struct CustomDict* dict, char* key) {
    int i, j;
    if (dict == NULL || key == NULL) {
        printf("INVALID INPUT\n");
        return NULL; 
    }

    /*Iterate through the dictionary's items to find the matching key.*/
    for (i = 0; i < dict->current_size; i++) {
        /*If a match is found, check the data type and print the corresponding values.*/
        if (strcmp(dict->itemArr[i].key, key) == 0) {
            /*If the data type is "int", print the integer values.*/
            if (strcmp(dict->itemArr[i].dtype, "int") == 0) {
                for (j = 0; j < dict->itemArr[i].num_values; j++) {
                    printf("%d ", dict->itemArr[i].value.int_val[j]);
                }
            /*If the data type is "float", print the float values.*/
            } else if (strcmp(dict->itemArr[i].dtype, "float") == 0) {
                for (j = 0; j < dict->itemArr[i].num_values; j++) {
                    printf("%.2f ", dict->itemArr[i].value.float_val[j]);
                }
            /*If the data type is "double", print the double values.*/
            } else if (strcmp(dict->itemArr[i].dtype, "double") == 0) {
                for (j = 0; j < dict->itemArr[i].num_values; j++) {
                    printf("%.2lf ", dict->itemArr[i].value.double_val[j]);
                }
            /*If the data type is "char", print the character values.*/
            } else if (strcmp(dict->itemArr[i].dtype, "char") == 0) {
                for (j = 0; j < dict->itemArr[i].num_values; j++) {
                    printf("%s ", dict->itemArr[i].value.char_val[j]);
                }
            }
            printf("\n");
            /*Return a pointer to the found value.*/
            return &(dict->itemArr[i].value);
        }
    }
    printf("KEY NOT FOUND\n");
    return NULL;
}


/*Function to delete an item from the custom dictionary based on the given key.*/
void delete_item(CustomDict *dict, char *key) {
    int i, j;
    if (dict == NULL || key == NULL) {
        printf("INVALID INPUT\n");
        return;
    }

    /*Iterate through the dictionary's items to find the matching key.*/
    for (i = 0; i < dict->current_size; i++) {
        /*If the key is found, proceed to delete the item.*/
        if (strcmp(dict->itemArr[i].key, key) == 0) {
            free(dict->itemArr[i].key); /*Free the memory allocated for the key.*/

            /*Free the memory allocated for the value based on its data type.*/
            if (strcmp(dict->itemArr[i].dtype, "int") == 0) {
                free(dict->itemArr[i].value.int_val);
            } else if (strcmp(dict->itemArr[i].dtype, "float") == 0) {
                free(dict->itemArr[i].value.float_val);
            } else if (strcmp(dict->itemArr[i].dtype, "double") == 0) {
                free(dict->itemArr[i].value.double_val);
            } else if (strcmp(dict->itemArr[i].dtype, "char") == 0) {
                /*Free each string in the char array.*/
                for (j = 0; j < dict->itemArr[i].num_values; j++) {
                    free(dict->itemArr[i].value.char_val[j]);
                }
                /*Free the char array itself.*/
                free(dict->itemArr[i].value.char_val);
            }
            /*Free the memory allocated for the data type.*/
            free(dict->itemArr[i].dtype);

            /*Shift the remaining items to fill the gap created by the deleted item.*/
            for (j = i; j < dict->current_size - 1; j++) {
                dict->itemArr[j] = dict->itemArr[j + 1];
            }
            /*Decrement the current size of the dictionary.*/
            dict->current_size--;
            return;
        }
    }
    printf("KEY NOT FOUND\n");
}


/*Function to set a new value for an existing key in the custom dictionary.*/
void set_value(CustomDict *dict, char *key, Value *value, const char *dtype, int num_values) {
    int i, j;
    if (dict == NULL || key == NULL || value == NULL || dtype == NULL) {
        printf("INVALID INPUT\n");
        return;
    }

    /*Iterate through the dictionary's items to find the matching key.*/
    for (i = 0; i < dict->current_size; i++) {
        /*If the key is found, proceed to set the new value.*/
        if (strcmp(dict->itemArr[i].key, key) == 0) {
            /*Free the memory allocated for the existing value based on its data type.*/
            if (strcmp(dict->itemArr[i].dtype, "int") == 0) {
                free(dict->itemArr[i].value.int_val);
            } else if (strcmp(dict->itemArr[i].dtype, "float") == 0) {
                free(dict->itemArr[i].value.float_val);
            } else if (strcmp(dict->itemArr[i].dtype, "double") == 0) {
                free(dict->itemArr[i].value.double_val);
            } else if (strcmp(dict->itemArr[i].dtype, "char") == 0) {
                for (j = 0; j < dict->itemArr[i].num_values; j++) {
                    free(dict->itemArr[i].value.char_val[j]);
                }
                free(dict->itemArr[i].value.char_val);
            }
            free(dict->itemArr[i].dtype);

            /*Set the new value for the item.*/
            dict->itemArr[i].value = *value;
            /*Allocate memory for the new data type and copy the value.*/
            dict->itemArr[i].dtype = (char*) malloc(strlen(dtype) + 1);
            if (dict->itemArr[i].dtype == NULL) {
                printf("MEMORY ALLOCATION FAILED\n");
                return;
            }
            /*Copy the new data type string.*/
            strcpy(dict->itemArr[i].dtype, dtype); 
            /*Set the new number of values for the item.*/
            dict->itemArr[i].num_values = num_values;
            return;
        }
    }
    printf("KEY NOT FOUND\n");
}

/* Function to sort the items in the custom dictionary alphabetically based on their keys.*/
void sort_dict(CustomDict *dict) {
    int i, j;
    if (dict == NULL) {
        printf("NOTHING TO SORT\n");
        return;
    }

    /*Iterate through the items in the dictionary.*/
    for (i = 0; i < dict->current_size - 1; i++) {
        for (j = i + 1; j < dict->current_size; j++) {
            /*Compare the keys of the items and swap them if they are not in alphabetical order.*/
            if (strcmp(dict->itemArr[i].key, dict->itemArr[j].key) > 0) {
                Item temp = dict->itemArr[i];
                dict->itemArr[i] = dict->itemArr[j];
                dict->itemArr[j] = temp;
            }
        }
    }
}

void print_dict(CustomDict *dict) {
    int i, j;
    if (dict == NULL) {
        printf("NOTHING TO PRINT\n");
        return;
    }

    /* Loop through each item in the dictionary*/
    for (i = 0; i < dict->current_size; i++) {
        /*Print the key of the current item*/
        printf("%s: ", dict->itemArr[i].key);

        /*Loop through each value of the current item*/
        for (j = 0; j < dict->itemArr[i].num_values; j++) {
            /*Check the data type of the value and print accordingly*/
            if (strcmp(dict->itemArr[i].dtype, "int") == 0) {
                printf("%d", dict->itemArr[i].value.int_val[j]);
                /*Print comma if there are more values, otherwise print newline*/
                if (j == dict->itemArr[i].num_values - 1) { 
                    printf("\n");
                } else {
                    printf(", ");
                }
            } else if (strcmp(dict->itemArr[i].dtype, "float") == 0) {
                printf("%.2f", dict->itemArr[i].value.float_val[j]);
                if (j == dict->itemArr[i].num_values - 1) {
                    printf("\n");
                } else {
                    printf(", ");
                }
            } else if (strcmp(dict->itemArr[i].dtype, "double") == 0) {
                printf("%.2lf", dict->itemArr[i].value.double_val[j]);
                if (j == dict->itemArr[i].num_values - 1) {
                    printf("\n");
                } else {
                    printf(", ");
                }
            } else if (strcmp(dict->itemArr[i].dtype, "char") == 0) {
                printf("%s", dict->itemArr[i].value.char_val[j]);
                if (j == dict->itemArr[i].num_values - 1) {
                    printf("\n");
                } else {
                    printf(", ");
                }
            } else {
                printf("UNKNOWN DATA TYPE\n");
                if (j == dict->itemArr[i].num_values - 1) {
                    printf("\n");
                } else {
                    printf(", ");
                }
            }
        }
    }
}

/*Function to remove the newline character from a string.*/
char* remove_NL(char *str) {
    char *end = str + strlen(str) - 1; /*Get a pointer to the last character in the string.*/
    if (*end == '\n') { /*Check if the last character is a newline character.*/
        *end = '\0'; /*Replace the newline character with a null terminator.*/
    }
    return str; /*Return the modified string.*/
}


/*Function to read data from a CSV file and populate a custom dictionary.*/
int read_csv(CustomDict* dict, const char* filename) {
    /*Open the CSV file for reading.*/
    FILE *data_file = fopen(filename, "r");
    if (data_file == NULL) {
        printf("ERROR OPENING THE FILE %s\n", filename);
        return 0; 
    }

        char line[1024]; /*Buffer to store each line read from the file.*/
        /* Read each line from the file */
        while (fgets(line, sizeof(line), data_file)) {
        /*Divide the line based on the commas*/
        char* token = strtok(line, ","); 
        /*Extract the key from the second token*/
        char* key = strtok(NULL, ",");
        key = remove_NL(key);  /*Remove newline characters from the key */

        Value value;
        int num_values = 0; /* Initialize a variable to count the number of values */

        /* Check the data type specified by the first token */
        if (strcmp(token, "int") == 0) {
            value.int_val = (int *)malloc(MAX_VALUES * sizeof(int)); /*Allocate memory for integer values */
            /* Parse and store the integer values */
            while (1) {
                /*Divide the line based on the commas*/
                char* val = strtok(NULL, ",");
                /* Check if the token is NULL or the first character is a newline character */
                if (val == NULL || val[0] == '\n') {
                    break; /*Break the loop if end of line is reached or token is NULL*/
                }
                /*Convert the token to an integer using atoi and store it in the int array */
                value.int_val[num_values++] = atoi(val);
            }
        } else if (strcmp(token, "float") == 0) {
            value.float_val = (float *)malloc(MAX_VALUES * sizeof(float)); /* Allocate memory for float values */
            while (1) {
                char* val = strtok(NULL, ",");
                if (val == NULL || val[0] == '\n'){ 
                    break;
                }
                /*Convert the token to a float using atof and store it in the float array */
                value.float_val[num_values++] = atof(val);
            }
        } else if (strcmp(token, "double") == 0) {
            value.double_val = (double *)malloc(MAX_VALUES * sizeof(double)); /* Allocate memory for double values */
            while (1) {
                char* val = strtok(NULL, ",");
                if (val == NULL || val[0] == '\n'){
                    break;
                }
                /*Convert the token to a double using atof and store it in the double array */
                value.double_val[num_values++] = atof(val);
            }
        } else if (strcmp(token, "char") == 0) {
            value.char_val = (char **)malloc(MAX_VALUES * sizeof(char*)); /* Allocate memory for char values */
            while (1) {
                char* val = strtok(NULL, ",");
                if (val == NULL || val[0] == '\n'){
                    break;
                }
                /*Allocate memory for the string and copy the token to the char array */
                value.char_val[num_values] = (char *)malloc((strlen(val) + 1) * sizeof(char));
                strcpy(value.char_val[num_values++], remove_NL(val));
            }
        }

        add_item(dict, key, value, token, num_values); /* Add the key-value pair to the dictionary */
    }

    fclose(data_file);
    return 1; 
}

/*Function to free the memory allocated for the custom dictionary.*/
void free_dict(CustomDict* dict) {
    int i, j;
    if (dict == NULL) {
        return; 
    }
    /*Iterate through the items in the dictionary.*/
    for (i = 0; i < dict->current_size; ++i) {
        /*Free the memory allocated for the key of each item.*/
        free(dict->itemArr[i].key);
        /*ree the memory allocated for the value of each item based on its data type.*/
        if (strcmp(dict->itemArr[i].dtype, "int") == 0) {
            free(dict->itemArr[i].value.int_val);
        } else if (strcmp(dict->itemArr[i].dtype, "float") == 0) {
            free(dict->itemArr[i].value.float_val);
        } else if (strcmp(dict->itemArr[i].dtype, "double") == 0) {
            free(dict->itemArr[i].value.double_val);
        } else if (strcmp(dict->itemArr[i].dtype, "char") == 0) {
            for (j = 0; j < dict->itemArr[i].num_values; ++j) {
                free(dict->itemArr[i].value.char_val[j]);
            }
            free(dict->itemArr[i].value.char_val);
        }
        /*Free the memory allocated for the data type of each item.*/
        free(dict->itemArr[i].dtype);
    }
    /*Free the memory allocated for the item array and the dictionary itself.*/
    free(dict->itemArr);
    free(dict);
}
