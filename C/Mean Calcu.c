#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// Is this real CHAT?!?!?!
int compare /*THIS SHIT ARRANGES THE ARRAY FROM LOWEST TO HIGHEST*/ (const void *x, const void *y) {
    int *value1 = (int *)x, *value2 = (int *)y;
    return *value1 - *value2;
}

float MedianFinder (int array[], int index) { //The Calculations for the Median
    float median;
    if /*EVEN*/ (index % 2 == 0) {
        median = (array[index/2] + array[index/2-1]) / 2.0;
    } else if /*ODD*/ (index % 2 == 1) {
        median = array[index/2]; 
    }
    return median; //Returns the Median and thus the output
}

int main() {
    int choose = 0;
    printf("No Longer a Mean Calculator :D\n1. Mean\n2. Median\nChoose: ");
    scanf("%d", &choose);
    if(choose == 1) { // MEAN CALCULATOR BELOW
        printf("=====Mean Calculator=====");
        int sum = 0, num = 0, count = 0, choice = 0;
        float mean;
        while(true) {
        printf("\nInput a number: ");
        scanf("%d", &num);
        sum += num;
        ++count;
        printf("Continue?\t1 - Yes\t2 - No\n?:");
        scanf("%d", &choice);
        if(choice==1) {
            continue; //just put this here so it wouldn't cuss you out lmao
        } else if(choice==2){
            break;
        } else {
            printf("What the fuck are you doing?");
        }
    }
    mean = (float) sum / count;
    printf("The mean is: %.3f", mean);
    } else if(choose == 2) { //MEDIAN CALCULATOR BELOW
        int set[10], index = 0;
        float median = 0;
        printf("=====Median Finder=====");
        while(true) {
            printf("\nInput a set of numbers\n");
            scanf("%d", &set[index]);
            index++;
            if(index > 9) {
                printf("You've already went beyond the limit lmao\n");
            }
            qsort(set, index, sizeof(int), compare); //SORTS THE ARRAY
            printf("continue?\n1 - Yes\n2 - No\n?:"); //ASKS IF YOU WANT TO GO AGAIN
            scanf("%d", &choose); //THE DECISION FOR THAT
            if(choose == 1) {
                continue; //again, it's only here so it won't cuss you out.
            } else if(choose == 2) {
                break; //ENDS THE LOOP
            } else {
                printf("Retard"); //IF YOU'RE BEING A RETARD
            }
        }
        median = MedianFinder(set, index); //Does the calculations
        printf("The Median is: %.2f", median); // The output
    } else {
        printf("Kekw");
        return 0;
    }
} //Nice try Diddy
