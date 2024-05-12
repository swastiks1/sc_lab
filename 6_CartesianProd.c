#include <stdio.h>
#include <stdlib.h>
//1.create struct
//2.cartesian product()
// 2(i)compare the value of both fuzzys sets
typedef struct {
    char ele;
    float mem_value;
} fuzzySet;

void cartesianProduct(fuzzySet a1[], int n1, fuzzySet a2[], int n2) {
    int i, j;
    printf("Cartesian Product:\n");
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            float min_value = (a1[i].mem_value < a2[j].mem_value ? a1[i].mem_value : a2[j].mem_value);
            printf("(%c, %.2f) x (%c, %.2f) = (%c%c, %.2f)\n", a1[i].ele, a1[i].mem_value, a2[j].ele, a2[j].mem_value, a1[i].ele, a2[j].ele, min_value);
        }
    }
}

int main() {
    int i, size1, size2;
    printf("Enter size of Set A: ");
    scanf("%d", &size1);
    fuzzySet a1[size1];
    getchar(); // to consume the newline character left in the input buffer

    for (i = 0; i < size1; i++) {
        printf("Input Elements of Set A: ");
        scanf(" %c, %f", &a1[i].ele, &a1[i].mem_value);
    }

    printf("Enter size of Set B: ");
    scanf("%d", &size2);
    fuzzySet a2[size2];
    getchar(); // to consume the newline character left in the input buffer

    for (i = 0; i < size2; i++) {
        printf("Input Elements of Set B: ");
        scanf(" %c, %f", &a2[i].ele, &a2[i].mem_value);
    }

    cartesianProduct(a1, size1, a2, size2);

    return 0;
}
