#include<stdio.h>

/*Define constants for maximum and minimum integer values*/
#define Int_Max 2147483647 
#define Int_Min -2147483648


int main(){
    int coord_x, coord_y, klass, menu; /* Coordinates, class, and menu choice */
    int reg1, reg2, reg3, reg4; /* Region labels */
    int min_x, max_x, min_y, max_y; /* Minimum and maximum coordinates */
    int sepX, sepY; /* Separator coordinates */
    int best_sepX, best_sepY; /* Best separator coordinates */
    int tot_error = 0, min_err = Int_Max; /* Total error and minimum error */
    int best_reg1, best_reg2, best_reg3, best_reg4; /* Best region labels */
    float success_rate = 0.0; /* Success rate */

     /* Initialize variables to store minimum and maximum values for class 0 and 1 */
    int min_x1 = Int_Max , max_x1 = Int_Min; /* Min and max X for class 1 */
    int min_y1 = Int_Max , max_y1 = Int_Min; /* Min and max Y for class 1 */
    int min_x0 = Int_Max , max_x0 = Int_Min; /* Min and max X for class 0 */
    int min_y0 = Int_Max , max_y0 = Int_Min; /* Min and max Y for class 0 */

    /* Open data.txt file for reading */
    FILE *data = fopen("data.txt", "r");

    /* Check if the file was opened successfully */
    if (data == NULL) {
        printf("Something wrong with the opening the data.txt file\n");
        return 1;
    }

    /* Read data from the file */
    while (fscanf(data, "%d %d %d", &coord_x, &coord_y, &klass) != EOF){
        /* Determine minimum and maximum values for class 0 and 1 */
        if (klass == 0){
            if (coord_x > max_x0){
                max_x0 = coord_x;
            }
            if (coord_x < min_x0){
                min_x0 = coord_x;
            }
            if (coord_y > max_y0){
                max_y0 = coord_y;
            }
            if (coord_y < min_y0){
                min_y0 = coord_y;
            } 
        }else if(klass == 1){
            if (coord_x < min_x1){
                min_x1 = coord_x;
            }
            if (coord_x > max_x1){
                max_x1 = coord_x;
            }
            if (coord_y < min_y1){
                min_y1 = coord_y;
            }
            if (coord_y > max_y1){
                max_y1 = coord_y;
            }  
        } else {
            printf("Something is wrong");
            return 0;
        }
    }

    if (max_x0 < max_x1){
        max_x = max_x0;  /* Determine overall max X */
    }else {
        max_x = max_x1; 
    }

    if (max_y0 <= max_y1){ /* Determine overall max Y */
        max_y = max_y0;
    }else {
        max_y = max_y1;
    }


    if (min_x0 <= min_x1){ /* Determine overall min X */
        min_x = min_x0;
    }else {
        min_x = min_x1;
    }

    if (min_y0 <= min_y1){ /* Determine overall min Y */
        min_y = min_y0;
    }else {
        min_y = min_y1;
    }


    printf("\nWELCOME\n\n");

    /*Menu loop*/
    while (menu != 5){
        printf("Please select from the following options:\n1. Explore Data\n2. Train Model\n3. Test Model\n4. Predict labels for test-final.txt file\n5. Exit\n");
        printf("\nChoose one of the options: ");
        scanf("%d", &menu);
        /*If the user input is bigger than 5 or smaller than 1 it will give an error*/
        if (menu < 1 || menu > 5){
            printf("Please enter one of the options provided to you!!!\n");
            
        }else{
            if (menu == 1){
                /*Display minimum and maximum values for both classes, that was found before*/
                printf("\nMinimum and Maximum X and Y values:\n");
                printf("Class 0: X in [%d, %d], Y in [%d, %d]\n", min_x0, max_x0, min_y0, max_y0);
                printf("Class 1: X in [%d, %d], Y in [%d, %d]\n\n", min_x1, max_x1, min_y1, max_y1);
            }else if(menu == 2){
                /* Iterate over possible separator coordinates to find the best separators*/
                for ( sepX = min_x ; sepX <= max_x; sepX++){
                    for ( sepY = min_y; sepY <= max_y; sepY++){    
                        /*Iterate over possible label combinations to find the best labels*/
                        for ( reg1 = 0; reg1 <= 1; reg1++){
                            for (reg2 = 0; reg2 <= 1; reg2++){
                                for (reg3 = 0; reg3 <= 1; reg3++){
                                    for (reg4 = 0; reg4 <= 1; reg4++){
                                        /*To store the error counts for each region.*/
                                        int reg1_err = 0, reg2_err = 0, reg3_err = 0, reg4_err = 0;
                                        /*Close and open the file to reset it*/
                                        fclose(data);
                                        data = fopen("data.txt", "r");

                                        while (fscanf(data, "%d %d %d", &coord_x, &coord_y, &klass) != EOF){
                                            /*Calculates errors for each region based on the separator coordinates and class labels.*/
                                            if (sepX <= coord_x && sepY > coord_y && klass != reg1 ){
                                                reg1_err++;
                                            }else if (sepX > coord_x && sepY > coord_y && klass != reg2){
                                                reg2_err++;
                                            }else if (sepX <= coord_x && sepY <= coord_y && klass != reg3){
                                                reg3_err++;
                                            }else if (sepX > coord_x && sepY <= coord_y && klass != reg4){
                                                reg4_err++;
                                            }  
                                        }
                                        /* Finds the total error by summing up the errors from all four regions.*/
                                        tot_error = reg1_err + reg2_err + reg3_err + reg4_err;
                                        /*If the current total error is less than the minimum error, 
                                        it updates the min error, separators and region labels as the best ones founds*/
                                        if (tot_error < min_err){ 
                                            min_err = tot_error;  
                                            best_sepX = sepX;
                                            best_sepY = sepY;

                                            best_reg1 = reg1;
                                            best_reg2 = reg2;
                                            best_reg3 = reg3;
                                            best_reg4 = reg4;
                                        }  
                                    }
                                }
                            }
                        }
                    }
                }
                printf("Separator coordiantes: X = %d, Y = %d\n", best_sepX, best_sepY);
                printf("Training error of the model = %d\n", min_err);
                printf("Labels of the regions R1 = %d, R2 = %d, R3 = %d, R4 = %d\n\n", best_reg1, best_reg2, best_reg3, best_reg4);
                
                fclose(data);/*Close data.txt*/

            }else if(menu == 3){
                /*Read data from the test1.txt*/
                FILE *test = fopen("test 1.txt", "r");
                /* Check if the file was opened successfully */
                if (test == NULL){
                    printf("Error opening test.txt file.\n");
                    return 1;
                }
                /*test_data_points to count the total number of points, true_klass_counter count correct predictions*/
                float test_data_points = 0, true_klass_counter = 0; 

                while (fscanf(test, "%d %d %d", &coord_x, &coord_y, &klass) != EOF){
                    /*Predicts the label for each data point in the test1.txt based on best separators and best region labels*/
                    int predict_label;
                    if (coord_x <= best_sepX && coord_y > best_sepY){
                        predict_label = best_reg1;
                    }
                    else if (coord_x > best_sepX && coord_y > best_sepY){
                        predict_label = best_reg2;
                    }
                    else if (coord_x <= best_sepX && coord_y <= best_sepY){
                        predict_label = best_reg3;
                    }
                    else{
                        predict_label = best_reg4;
                    }

                    printf("X = %d, Y = %d, Predicted label = %d, Actual label = %d\n\n", coord_x, coord_y, predict_label, klass);

                    if (predict_label == klass){
                        true_klass_counter++; /*If the predicted class is mathces the actual class it will iterate the counter*/
                    }
                    test_data_points++; /*Going to the next data point*/
                    }
                    success_rate = true_klass_counter / test_data_points * 100; /*Calculating the success rate based on the true_klass_counter and test_data_points*/
                    printf("Success rate : %.2f%%\n\n", success_rate);

                    fclose(test);/*Close the test1.txt*/

            }else if(menu == 4){
                /*Read data from the test-final.txt*/
                FILE *final = fopen("test-final.txt", "r");
                /* Check if the file was opened successfully */
                if (final == NULL){
                    printf("Error opening test-final.txt file.\n");
                    return 1;
                }
                
                while (fscanf(final, "%d %d", &coord_x, &coord_y) != EOF){
                    /*Predicts the label for each data point in the test-final.txt based on best separators and best region labels*/
                    int predict_label;
                    if (coord_x <= best_sepX && coord_y > best_sepY){
                        predict_label = best_reg1;
                    }
                    else if (coord_x > best_sepX && coord_y > best_sepY){
                        predict_label = best_reg2;
                    }
                    else if (coord_x <= best_sepX && coord_y <= best_sepY){
                        predict_label = best_reg3;
                    }
                    else{
                        predict_label = best_reg4;
                    }

                    printf("X = %d, Y = %d, Predicted label = %d\n\n", coord_x, coord_y, predict_label);
                }

                fclose(final);/*Close the test-final.txt*/

            }else if (menu == 5){
                /*Exits the program when 5 is entered*/
                printf("SEE YOU SOON!"); 
                return 0;
            }
        }
    }
return 0;
}