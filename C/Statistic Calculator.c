#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
//Fucking hell man
int sort (const void *a, const void *b) { //the sorting algorithm
    double *x = (double *)a, *y = (double *)b;
    if(*x > *y) {
        return 1;
    } else if(*x < *y) {
        return -1;
    } else {
        return 0;
    } // Positive: x goes right, Negative: x goes left, Zero: equal
}
double /*Calculates the Mean*/ MeanCalculate (double set[], int index) {
    double sum = 0;
    for(int i = 0;i < index;i++) {
        sum += set[i];
    }
    return sum / index;
}

double /*Calculates the Median*/ MedianCalculate (double set[], int index) {
    double median;
    if(index % 2 == 0) { //EVEN
        median = (set[index / 2 - 1] + set[index / 2]) / 2.0;
    }
    else if(index % 2 == 1) { //ODD
        median = set[index / 2];
    }
    return median;
}

double* /*Looks for the Mode*/ FindMode (double set[], int index, int *num_modes) {
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
    double *modes = malloc(mode_count * sizeof(double));
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

double /*Calculates the Variance*/ VarianceCalculate(double set[], int index, double mean, bool is_sample) {
    double sum = 0, difference = 0, variance = 0;
    for(int i = 0;i < index;i++) {
        difference = set[i] - mean;
        difference *= difference;
        sum += difference;
    }
    if(index == 1) { //for weirdos who think putting only one number is funny
        variance = sum;
    } else {
        variance = sum / (is_sample ? (index - 1) : index);
    }
    return variance;
}

int main () {
    int index = 0, number = 0, num_modes = 0;
    double *set, *modes; //the set and others
    double mean, median, population_variance, sample_variance; //the outputs
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
        set = (double *)malloc(number * sizeof(double));
        if(set == NULL) {
            printf("\nMEMORY ALLOCATION FAILED\n");
            return 1;
        }
    }

    //The Statistics itself
    printf("\nNow Input the numbers, maximum of %d (input 69420 if you want to stop)\n", number);
    for /*The loop for initializing*/ (int j = 0;j<number;j++) {
        if(scanf("%lf", &set[index]) != 1) { //input statement and condition for checking if input was valid
            printf("That's not a number...\n");
            while(getchar() != '\n'); //
            j--;
            continue;
        }
        if(set[index] == 69420) {
            printf("\nOK\n");
            break;
        }
        index++;
    }
    if(index == 0) { //if you for some reason input 69420 at the start
        printf("\nNo numbers input\nEnding the program");
        free(set);
        return 0;
    }
    qsort(set, index, sizeof(double), sort); //sorts the array from lowest to highest
    mean = MeanCalculate(set, index);
    median = MedianCalculate(set, index);
    modes = FindMode(set, index, &num_modes);
    sample_variance = VarianceCalculate(set, index, mean, true);
    population_variance = VarianceCalculate(set, index, mean, false);
    printf("\nResults\nSet (organized lowest to highest): ");
    for(int i = 0;i<index;i++) { //loop that prints the arranged values of the array
        printf("%.2lf ", set[i]);
    }
    printf("\nMean: %.2lf\nMedian: %.2lf\nMode(s): ", mean, median);
    if(num_modes == 0) {
        printf("No Mode");
    } else {
        for(int h = 0;h < num_modes;h++) {
            printf("%.2lf ", modes[h]);
        }
    }
    printf("\nMin: %.2lf\nMax: %.2lf\nRange: %.2lf", set[0], set[index - 1], (set[index - 1] - set[0]));
    printf("\nSample Variance: %.2lf\nPopulation Variance: %.2lf\nSample Standard Deviation: %.2lf\nPopulation Standard Deviation: %.2lf", sample_variance, population_variance, sqrt(sample_variance), sqrt(population_variance));
    free(modes);
    free(set);
}

