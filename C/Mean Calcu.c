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
int main () {
    int set[10], index = 0;
    float mean, median;
    printf("Statistical Calculator\nInput a set of Numbers(Put 69420 if you'd want to stop)\n");
    while /*The loop for initializing the values of the array*/ (true) {
        scanf("%d", &set[index]);
        if(set[index] == 69420) {
            printf("\nOk\n");
            break;
        }
        index++;
    }
    qsort(set, index, sizeof(int), sort);
    mean = MeanCalculate(set, index);
    median = MedianCalculate(set, index);
    printf("\nResults\nSet (organized highest to lowest): ");
    for(int i = 0;i<index;i++) {
        printf("%d ", set[i]);
    }
    printf("\nMean: %.2f\nMedian: %.2f", mean, median);
}
