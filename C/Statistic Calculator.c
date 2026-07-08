#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct data {
    int index, num_modes;
    double *set, *modes, *population_zscore, *sample_zscore;
    double mean, median, population_variance, sample_variance;
};

void initialize /*Function for initializing values*/ (struct data *sheet) {
    char buffer[101]; //input buffer
    int multiple = 10;
    double* temp;
    sheet->set = (double *)malloc(sizeof(double) * multiple); //initial memory allocation
    while(true) {
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if(buffer[0] == '\0') { //if empty input
            continue;
        }
        if(strcmp(buffer, "h") == 0 || strcmp(buffer, "H") == 0) { //for cancelling input
            printf("s - stops input stream\nd - deletes previous input\nr - resets entire input stream\np - views initial array\n");
            continue;
        }
        else if(strcmp(buffer, "s") == 0 || strcmp(buffer, "S") == 0) { //for cancelling input
            printf("\nStopping\n");
            if(sheet->index == 0) {
                sheet->set = NULL;
            }
            else if(sheet->index < multiple) {
                temp = (double *)realloc(sheet->set, sizeof(double) * sheet->index);
                if(temp == NULL) {
                    printf("MEMORY ALLOCATION FAIL!");
                    exit(1);
                }
                else {
                    sheet->set = temp;
                }
            }
            break;
        }
        else if(strcmp(buffer, "d") == 0 || strcmp(buffer, "D") == 0) { //for removing previous instance
            if(sheet->index == 0) {
                printf("There is nothing to delete\n");
                continue;
            }
            else {
                printf("Deleted previous instance\n");
                (sheet->index)--;
                continue;
            }
        }
        else if(strcmp(buffer, "r") == 0 || strcmp(buffer, "R") == 0) { //for resetting the entire stream
            printf("Stream Reset\n");
            (sheet->index) = 0;
            multiple = 10;
            temp = (double *)realloc(sheet->set, sizeof(double) * multiple);
            if(temp == NULL) {
                printf("MEMORY ALLOCATION FAILED!\n");
                exit(1);
            }
            else {
                sheet->set = temp;
            }
            continue;
        }
        else if(strcmp(buffer, "p") == 0 || strcmp(buffer, "P") == 0) { //viewing the current array
            if(sheet->index == 0) {
                printf("The array is empty");
            }
            else {
                for(int q = 0;q < sheet->index;q++) {
                    printf("%.2lf ", sheet->set[q]);
                }
            }
            printf("\n");
            continue;
        }
        //checks if valid
        int found = 0;
        for(int i = 0;i < strlen(buffer);i++) { //loops through entire string
            if(isalpha(buffer[i])) { //increases counter if there is a letter
                found++;
            }
            else if(ispunct(buffer[i]) && buffer[i] != '.' && buffer[i] != '-') { //increases counter if there is a punctuation except for a period
                found++;
            }
        }
        if(found > 0) {
            printf("Invalid input!\n");
            continue;
        }
        char *current = buffer, *endptr;
        while(true) {
            double value = strtod(current, &endptr);
            while(isspace(*endptr)) { //checks for spaces
                endptr++; //moves to the next column
            }
            (sheet->set)[sheet->index] = value;
            (sheet->index)++;
            if(sheet->index == multiple) { //changes size of array if you went beyond
                multiple *= 2;
                temp = (double *)realloc(sheet->set, sizeof(double) * multiple);
                if(temp == NULL) {
                    printf("MEMORY ALLOCATION FAILED!");
                    exit(1);
                }
                else {
                    sheet->set = temp;
                }
            }
            if(*endptr == '\0') { //checks for the null terminator then ends loop
                break;
            }
            current = endptr;
            continue;
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
    if(index == 1 || std == 0) {
        return NULL;
    }
    double *zscores = (double *)malloc(sizeof(double) * index);
    for(int i = 0;i < index;i++) {
        zscores[i] = (set[i] - mean) / std;
    }
    return zscores;
}

void display(struct data sheet) {
    printf("\nResults\nSet (organized lowest to highest): ");
    for(int h = 0;h<sheet.index;h++) { //loop that prints the arranged values of the array
        printf("%.2lf ", sheet.set[h]);
    }
    if(sheet.index == 1 || sheet.population_zscore == NULL) {
        printf("\nPopulation Z-Scores: undefined");
    }
    else {
        printf("\nPopulation Z-Scores:");
        for(int i = 0;i < sheet.index;i++) {
            printf(" %.2lf", sheet.population_zscore[i]);
        }
    }
    if(sheet.index == 1 || sheet.sample_zscore == NULL) {
        printf("\nSample Z-Scores: undefined");
    }
    else {
        printf("\nSample Z-Scores:");
        for(int j = 0;j < sheet.index;j++) {
            printf(" %.2lf", sheet.sample_zscore[j]);
        }
    }
    printf("\nMean (μ): %.2lf\nMedian (x̃): %.2lf\nMode(s): ",sheet. mean,sheet. median);
    if(sheet.num_modes == 0) {
        printf("No Mode");
    } else {
        for(int k = 0;k < sheet.num_modes;k++) {
            printf("%.2lf ", sheet.modes[k]);
        }
    }
    printf("\nMin: %.2lf\nMax: %.2lf\nRange: %.2lf", sheet.set[0], sheet.set[sheet.index - 1], (sheet.set[sheet.index - 1] - sheet.set[0]));
    printf("\nPopulation Variance (σ²): %.2lf\nPopulation Standard Deviation (σ): %.2lf", sheet.population_variance, sqrt(sheet.population_variance));
    if(sheet.index == 1) {
        printf("\nSample Variance (s²): undefined\nSample Standard Deviation: undefined");
    }
    else {
        printf("\nSample Variance (s²): %.2lf\nSample Standard Deviation: %.2lf", sheet.sample_variance, sqrt(sheet.sample_variance));
    }
}

int main() {
    char repeat;
    struct data sheet;
    printf("Statistical calculator\n");
    do { //loops the program
        sheet.index = 0;
        sheet.num_modes = 0;
        printf("\nInput the numbers(Enter 'h' for list of commands)\n");
        initialize(&sheet); //function for initializing
        if(sheet.set == NULL) {
            printf("\nYou didn't input anything!");
        } else {
            qsort(sheet.set, sheet.index, sizeof(double), sort); //sorts the array from lowest to highest
            sheet.mean = MeanCalculate(sheet.set, sheet.index);
            sheet.median = MedianCalculate(sheet.set, sheet.index);
            sheet.modes = FindMode(sheet.set, sheet.index, &sheet.num_modes);
            sheet.population_variance = VarianceCalculate(sheet.set, sheet.index, sheet.mean, false);
            sheet.sample_variance = VarianceCalculate(sheet.set, sheet.index, sheet.mean, true);
            sheet.population_zscore = zscore(sheet.set, sheet.index, sheet.mean, sqrt(sheet.population_variance));
            sheet.sample_zscore = zscore(sheet.set, sheet.index, sheet.mean, sqrt(sheet.sample_variance));
            display(sheet);
            free(sheet.modes);
            free(sheet.population_zscore);
            free(sheet.sample_zscore);
        }
        free(sheet.set);
        printf("\n\nContinue using? (y to continue, anything else to stop): ");
        scanf(" %c", &repeat);
        while(getchar() != '\n');
    } while(repeat == 'y' || repeat == 'Y');
    printf("\nEnding Program");
    return 0;
}
