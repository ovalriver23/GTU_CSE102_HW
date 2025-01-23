#include<stdio.h>

/*Function prototypes*/
void draw_histogram(int a, int b, int ocr[]); /*Function to display the histogram*/
void add_new_num(int arr[], int *size, int a, int b); /*Function to insert the number to existed array*/
double calc_avg(int arr[], double size, int a, int b);/*Function to calculate the average*/
int calc_mode(int arr[], int n, int a, int b, int modes[]); /*Function to calculate the modes*/
double calc_median(int arr[], int n, int a, int b); /*Function to calculate the median*/
int size_of_array(int arr[]); /*Function to calculate the size of the array*/
void count_ocr(int arr[], int n, int a, int b, int ocr[]); /*Function to count occurrences of numbers*/

int main(){
    /*Initial number array*/
    int number_array[] = {-1}; /*You need to fill this array before using it*/

    int size, a, b, cont, modes[100], num_modes;
    double average, median;

    /*Calculating size of the array*/
    size = size_of_array(number_array); 
    
    /*Asks about the intervals and then checks them*/
    do{
        printf("Enter A and B values: ");
        scanf("%d %d", &a, &b);
        if (a < 50){
            printf("ENTER AT LEAST 50 FOR A VALUE!!!\n");
        }if (b > 200){
            printf("B VALUE MUST NOT EXCEED 200!!!\n");
        }
    } while (a < 50 || b > 200);
    
    int ocr[b - a + 1]; /*Array to store the occurrences of numbers within the range*/
    count_ocr(number_array, size, a, b, ocr); /*Count the occurrences*/
    draw_histogram(a, b, ocr); /*Draw the histogram based on the occurrences*/

    /*Asks if the user wants to enter numbers to the array*/
    do{
        printf("Would you like to add numbers? (Press 1 for yes, Press 0 for no): ");
        scanf("%d", &cont);

        if (cont != 1 && cont != 0) {
        printf("ENTER A VALID NUMBER (0 OR 1)!!!\n");
        }
        
    } while (cont != 1 && cont != 0);
    
    /*If the user chooses to add numbers to the array*/
    if (cont == 1){
        add_new_num(number_array, &size, a, b); /*Calling the function to add numbers to the array*/

        count_ocr(number_array, size, a, b, ocr); /*counts the occurrences*/
        draw_histogram(a, b, ocr); /*Redraw the histogram*/

        /*Calls the function to calculate the average and displays the result*/
        average = calc_avg(number_array, size, a, b); 
        printf("Average: %.2f\n", average);

        /*Calls the function to calculate the median and display the output*/
        median = calc_median(number_array, size, a, b);
        printf("Median: %.2f\n", median);

        /*Calls function to calculate the mode and then displays the result*/
        num_modes = calc_mode(number_array, size, a, b, modes);
        printf("Mode: ");
        int i;
        /*Loop through each mode found*/
        for (i = 0; i < num_modes; i++) {
            /*If the current mode is the same as previous one it skips it*/
            if (i > 0 && modes[i] == modes[i - 1]) {
                continue;
            }
            printf("%d ", modes[i]);
        }
        printf("\n");
    /*Calculates without adding the numbers to the array*/
    }else if(cont == 0){
        /*Call the function to calculate the average and display the result*/
        average = calc_avg(number_array, size, a, b);
        printf("Average: %.2f\n", average);

        /*Calls the function to calculate the median and display the output*/
        median = calc_median(number_array, size, a, b);
        printf("Median: %.2f\n", median);

        /*Calls function to calculate the mode and then displays the result*/
        num_modes = calc_mode(number_array, size, a, b, modes);
        printf("Mode: ");
        int i;
        /*Loop through each mode found*/
        for (i = 0; i < num_modes; i++) {
            /*If the current mode is the same as previous one it skips it*/
            if (i > 0 && modes[i] == modes[i - 1]) {
                continue;
            }
            printf("%d ", modes[i]);
        }
        printf("\n");
        
    }
    return 0;
}

void count_ocr(int arr[], int n, int a, int b, int ocr[]){
    int i, j;
    /*Loop through the each number in the interval*/
    for (i = a; i <= b; i++) {
        int ocr_counter = 0;
        /*Loop through the array*/
        for (j = 0; j < n; j++) {
            /*If the current element of the array matches the current number, it increments the counter*/
            if (arr[j] == i) {
                ocr_counter++;
            }
        }
        /*Store the count of occurrences for the current number in the output array*/
        ocr[i - a] = ocr_counter;
    }
}

void draw_histogram(int a, int b, int ocr[]) {
    int max_ocr = 0, i, j;
    /*Determine the maximum number of occurrences within the interval*/
    for (i = a; i <= b; i++) {
        /*Chech if the current number is grater than maximum number of occurrences*/
        if (ocr[i - a] > max_ocr) {
            max_ocr = ocr[i - a];
        }
    }
    /*Loop from maximum occurrences to 1 to draw the histogram vertically*/
    for (i = max_ocr; i > 0; i--) {
        /*Loop through each number within the interval to draw each row*/
        for (j = a; j <= b; j++) {
            /*Check if the current muber has occurrences grater or equal to the current row*/
            if (ocr[j - a] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/*Function to calculate the size of the array*/
int size_of_array(int arr[]){
    int size = 0, i = 0;

    while (arr[i] != -1){
        size++;
        i++;
    }
    return size;
}

double calc_avg(int arr[], double size, int a, int b){
    int i, counter = 0; 
    double average, sum = 0;
    
    for ( i = 0; i < size; i++){
        /*Check if the current element is in the interval and not equal to the -1*/
        if (arr[i] != -1 && arr[i] >= a && arr[i] <= b){
            sum += arr[i]; /*Add the current element to the sum*/
            counter++; /*Increment the counter to track the number of elements in the interval*/
        }
    }

    /*Calculates the average*/
    if (counter > 0){
        average = sum / counter;
    }else{
        /*if there s no elements in the range, it prints the error message*/
        printf("There is no number on that interval!!");
        average = 0;
    }
    return average;
}

int calc_mode(int arr[], int n, int a, int b, int modes[]){
    int max_val = 0, ocr_counter = 0, max_ocr = 0, i, j, k, num_modes = 0;

    for (i = 0; i < n; i++){ /*Loop through the array*/
        if(arr[i] >= a && arr[i] <= b){ /*Checks if current number is in the interval*/
            ocr_counter = 0;
            /*Loop through the array to count the occurrences of the current number*/
            for (j = 0; j < n; j++){
                if (arr[j] == arr[i] && arr[j] >= a && arr[j] <= b){
                    ocr_counter++; /*increment the counter if the element matches the current number and inside the interval*/
                }
            }
            /*Check if the number of occurrences is greater than the current maximum occurrences*/
            if (ocr_counter > max_ocr){
                /*Update the maximum occurrneces and the mode value*/
                max_ocr = ocr_counter;
                max_val = arr[i];
                /*Reset the number of modes and store the current mode in the mode array*/
                num_modes = 1;
                modes[0] = max_val;
            }else if(ocr_counter == max_ocr && max_ocr > 1){
                int new_mode = 1; /*Flag to indicate is it a new mode or not*/
                for (k = 0; k < num_modes; k++){ /*A loop through the current modes*/
                    if (modes[k] == arr[i]){ /*Chech if the mode is already in the modes array*/
                       new_mode = 0; /*If the mode is found, set the flag to zero meaning it is not new*/
                       break;
                    }
                }
                if (new_mode == 1){ /*If the mode is new*/
                    modes[num_modes] = arr[i]; /*Add the mode to the array*/
                    num_modes++; /*Increment the count of modes*/
                }
            }
        }
    }
    return num_modes;    
}

double calc_median(int arr[], int n, int a, int b){
    int conter = 0, i, j, index = 0, temp;
    double median;

    /*Counts the number of elements inside the interval*/
    for (i = 0; i < n; i++){
        if (arr[i] >= a && arr[i] <= b){
            conter++;
        }
    }

    int interval_nums[conter];/*Create an array to store numbers inside the interval*/

    /*Store numbers inside the interval to the interval_nums array*/
    for (i = 0; i < n; i++){
        if (arr[i] >= a && arr[i] <= b){
            interval_nums[index++] = arr[i];
        }
    }

    /*Sorts the array in ascending order*/
    for (i = 0; i < conter - 1; i++){ /*This loop goes iterates from beginning of the array to the second to last element*/
        for (j = 0; j < conter - i - 1; j++){ /*This loop goes from the beginning of the array to the element before the last unsorted element*/
            /*Compares elements and swaps if necessary to move larger elements towards the end*/
            if (interval_nums[j] > interval_nums[j+1]){ 
                temp = interval_nums[j]; /*Swap the elements using a temp variable*/
                interval_nums[j] = interval_nums[j + 1];
                interval_nums[j + 1] = temp;
            }
        }
    }

    /*Calculate the median based*/
    if (conter == 0){
        printf("There are no elements in the interval!!");
        return 0;
    } else if(conter % 2 == 1){ /*If the number of elements is odd*/
        median = interval_nums[conter / 2];
    }else{ /*If the number of the elements is even*/
        median = (interval_nums[conter / 2] + interval_nums[conter / 2 - 1]) / 2.0;
    }
    
    return median;
}

void add_new_num(int arr[], int *size, int a, int b){
    int count = 0, num;

    printf("Enter the numbers: \n");

    while (count < 5){ /*Continue until 5 numbers are entered*/
        scanf("%d", &num);

        if (num == -1){ /*If the user enter -1, exit the loop*/
            break;
        }

        if (num < a || num > b){ /*Check if the entered number is within an interval*/
            /*If the number is out of the interval it prints the error message*/
            printf("PLEASE ENTER THE NUMBER INSIDE THE INTERVAL!!!\n");
        }else{
        arr[*size] = num; /*Add the number to the array an the current index*/
        (*size)++; /*Increment the size of the array*/
        count++; /*Increment the count of numbers added*/
        }
    }
}