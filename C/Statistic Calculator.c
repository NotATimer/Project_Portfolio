#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
//Fucking hell man
int sort (const void *a, const void *b) { //the sorting algorithm
    int *x = (int *)a, *y = (int *)b;
    return *x - *y; //x - y = positive number means higher, x - y = negative means lower number thus staying. Not too sure to explain ngl
}
float /*Calculates the Mean*/ MeanCalculate (int set[], int index) {
    float sum = 0;
    for(int i = 0;i < index;i++) {
        sum += set[i];
    }
    return sum / index;
}

float /*Calculates the Median*/ MedianCalculate (int set[], int index) {
    float median;
    if(index % 2 == 0) { //EVEN
        median = (set[index / 2 - 1] + set[index / 2]) / 2.0;
    }
    else if(index % 2 == 1) { //ODD
        median = set[index / 2];
    }
    return median;
}

int* /*Looks for the Mode*/ FindMode (int set[], int index, int *num_modes) {
    int count = 1, max_count = 1;
    //First pass, finds the maximum count of the number that repeats the most
    for(int x = 1;x < index;x++) { //loop for finding maximum count
        if(set[x] == set[x - 1]) {
            count++;
            if(count > max_count) {
                max_count = count;
            }
        } else {
            count = 1;
        }
    }

    if(max_count == 1) { //if the counter didn't increase at all, then there is no mode
        *num_modes = 0;
        return NULL;
    }

    //Second pass, checks how many modes are there
    int mode_count = 0;
    count = 1;
    for(int y = 1;y < index;y++) { //loop for how many modes there are based on the maximum count
        if(set[y] == set[y - 1]) {
            count++;
        } else {
            if(count == max_count) {
                mode_count++;
            }
            count = 1;
        }
    }

    if(count == max_count) { //checks the last group
        mode_count++;
    }

    //Last pass, initializing the array of modes and returning
    int *modes = malloc(mode_count * sizeof(int));
    int o = 0;
    count = 1;

    for(int z = 1;z < index;z++) {
        if(set[z] == set[z - 1]) { //loop for declaring the values inside the now allocated array
            count++;
        } else {
            if(count == max_count) {
                modes[o] = set[z - 1];
                o++;
            }
            count = 1;
        }
    }

    if(count == max_count) { //checks the last group again
        modes[o] = set[index - 1];
    }

    *num_modes = mode_count;
    return modes;
}

int main () {
    int *set, index = 0, number = 0, *modes, num_modes = 0;
    float mean, median;
    printf("Statistical Calculator\nInput how many numbers you want to put in a set(Input 0 to exit)\n");

    //Memory allocation for the array
    scanf("%d", &number);
    if(number == 0) {
        printf("\nOk, closing program\n");
        return 0;
    } else if(number != 0) {
        if(number > 10 && number < 20) {
            printf("\nOk that's a lot\n");
        } else if (number > 20 && number < 30) {
            printf("\nDAMN!\n");
        } else if(number > 30) {
            printf("\nOk this is way too much\n");
        }
        set = (int *)malloc(number * sizeof(int));
        if(set == NULL) {
            printf("\nMEMORY ALLOCATION FAILED\n");
            return 1;
        }
    }

    //The Statistics itself
    printf("\nNow Input the numbers, maximum of %d (input 69420 if you want to stop)\n", number);
    for /*The loop for initializing*/ (int j = 0;j<number;j++) {
        scanf("%d", &set[index]);
        if(set[index] == 69420) {
            printf("\nOK\n");
            break;
        }
        index++;
    }

    qsort(set, index, sizeof(int), sort); //sorts the array from lowest to highest
    mean = MeanCalculate(set, index);
    median = MedianCalculate(set, index);
    modes = FindMode(set, index, &num_modes);
    printf("\nResults\nSet (organized highest to lowest): ");
    for(int i = 0;i<index;i++) { //loop that prints the arranged values of the array
        printf("%d ", set[i]);
    }
    printf("\nMean: %.2f\nMedian: %.2f\nMode(s): ", mean, median);
    if(num_modes == 0) {
        printf("No Mode\n");
    } else {
        for(int h = 0;h < num_modes;h++) {
            printf("%d ", modes[h]);
        }
    }
    printf("\nMin: %d\nMax: %d\nRange: %d", set[0], set[index - 1], (set[index - 1] - set[0]));
    free(modes);
    free(set);
}
