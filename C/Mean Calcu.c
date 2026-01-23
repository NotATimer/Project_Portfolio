#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// Is this real CHAT?!?!?!
int compare (const void *x, const void *y) {
    int *value1 = x, *value2 = y;
    return *value1 - *value2;
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
        /*If you're reading this you are GAY*/
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
    } else if(choose == 2) {
        int set[10], index = 0, memory;
        float median = 0;
        printf("=====Median Finder=====");
        while(true) {
            printf("Input a set of numbers\n");
            scanf("%d", &set[index]);
            index++;
            if(index > 9) {
                printf("You've already went beyond the limit lmao\n");
            }
            memory = sizeof(set) / sizeof(set[0]);
            qsort(set, memory, sizeof(set[0]), compare);
            printf("continue?\n1 - Yes\n2 - No\n?:");
            scanf("%d", &choose);
            if(choose == 1) {
                continue; //again, it's only here so it won't cuss you out.
            } else if(choose == 2) {
                break;
            } else {
                printf("Retard");
            }
        }
    } else {
        printf("Kekw"); //ain't no party like a diddy party
        return 0;
    }
} //Nice try Diddy
