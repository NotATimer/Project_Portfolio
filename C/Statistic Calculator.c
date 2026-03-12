#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void initialize /*Function for initializing values*/ (double **set, int *index) {
    char buffer[101], *endptr; //input buffer
    int multiple = 10;
    *set = (double *)malloc(sizeof(double) * multiple); //initial memory allocation
    while(true) {
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if(buffer[0] == '\0') { //no input
            printf("You didn't input anything!\n");
            continue;
        }
        if(strcmp(buffer, "s") == 0 || strcmp(buffer, "S") == 0) { //for cancelling input
            printf("\nStopping\n");
            if(*index < multiple) {
                *set = (double *)realloc(*set, sizeof(double) * *index);
            }
            break;
        }
        //converts the string into a double
        double value = strtod(buffer, &endptr);
        if(*index == multiple) {
            multiple += 10;
            *set = (double *)realloc(*set, sizeof(double) * multiple);
        }
        if(endptr == buffer) {
            printf("Invalid input, please try again\n");
            continue;
        }
        else if(*endptr != '\0') {
            printf("Invalid input, please try again\n");
            continue;
        }
        else {
            (*set)[*index] = value;
            (*index)++;
        }
    }
}

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

double* zscore(double set[], int index, double mean, double std) {
    double *zscores = (double *)malloc(sizeof(double) * index);
    for(int i = 0;i < index;i++) {
        zscores[i] = (set[i] - mean) / std;
    }
    return zscores;
}

void display(double set[], int index, double mean, double median, double modes[], int num_modes, double population_variance, double population_zscore[], double sample_variance, double sample_zscore[]) {
    printf("\nResults\nSet (organized lowest to highest): ");
    for(int h = 0;h<index;h++) { //loop that prints the arranged values of the array
        printf("%.2lf ", set[h]);
    }
    printf("\nPopulation Z-Scores:");
    for(int i = 0;i < index;i++) {
        printf(" %.2lf", population_zscore[i]);
    }
    printf("\nSample Z-Scores:");
    for(int j = 0;j < index;j++) {
        printf(" %.2lf", sample_zscore[j]);
    }
    printf("\nMean (μ): %.2lf\nMedian (x̃): %.2lf\nMode(s): ", mean, median);
    if(num_modes == 0) {
        printf("No Mode");
    } else {
        for(int k = 0;k < num_modes;k++) {
            printf("%.2lf ", modes[k]);
        }
    }
    printf("\nMin: %.2lf\nMax: %.2lf\nRange: %.2lf", set[0], set[index - 1], (set[index - 1] - set[0]));
    printf("\nPopulation Variance (σ²): %.2lf\nPopulation Standard Deviation (σ): %.2lf", population_variance, sqrt(population_variance));
    printf("\nSample Variance (s²): %.2lf\nSample Standard Deviation: %.2lf", sample_variance, sqrt(sample_variance));
}

int main() {
    char repeat;
    double *set, *modes, *population_zscore, *sample_zscore; //the set and others
    double mean, median, population_variance, sample_variance; //the outputs
    printf("Statistical calculator\n");
    do { //loops the program
        int index = 0, num_modes = 0;
        printf("\nInput the numbers(Put s if you want to stop)\n");
        initialize(&set, &index); //function for initializing
        if(set == NULL) {
            printf("\nYou didn't input anything!");
        } else {
            qsort(set, index, sizeof(double), sort); //sorts the array from lowest to highest
            mean = MeanCalculate(set, index);
            median = MedianCalculate(set, index);
            modes = FindMode(set, index, &num_modes);
            population_variance = VarianceCalculate(set, index, mean, false);
            sample_variance = VarianceCalculate(set, index, mean, true);
            population_zscore = zscore(set, index, mean, sqrt(population_variance));
            sample_zscore = zscore(set, index, mean, sqrt(sample_variance));
            display(set, index, mean, median, modes, num_modes, population_variance, population_zscore, sample_variance, sample_zscore);
            free(modes);
            free(population_zscore);
            free(sample_zscore);
        }
        free(set);
        printf("\n\nContinue using? (y to continue, anything else to stop): ");
        scanf(" %c", &repeat);
        while(getchar() != '\n');
    } while(repeat == 'y' || repeat == 'Y');
    printf("\nEnding Program");
    return 0;
}
