#include <stdio.h>
#include <stdlib.h>

int *findUnion(int s1[], int s2[], int a, int b, int *size) {
    int i, j;
    int x = a + b;
    int *uni = (int *)malloc(x * sizeof(int));
    *size = 0;
    for (i = 0; i < a; i++) {
        uni[(*size)++] = s1[i];
    }
    for (i = 0; i < b; i++) {
        int flag = 1;
        for (j = 0; j < *size; j++) {
            if (s2[i] == uni[j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            uni[(*size)++] = s2[i];
    }
    return uni;
}

int *findIntersection(int s1[], int s2[], int a, int b, int *size) {
    int i, j;
    int *intersection = (int *)malloc(a * sizeof(int));
    int size1 = 0;
    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
            if (s1[i] == s2[j]) {
                intersection[size1++] = s1[i];
                break;
            }
        }
    }
    *size = size1;
    return intersection;
}

int checkEquality(int set1[], int set2[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (set1[i] != set2[i])
            return 0;
    }
    return 1;
}

int *findComplement(int s1[], int universalSet[], int *size) {
    int i, j;
    int *complementS1 = (int *)malloc(20 * sizeof(int));
    int sizeC = 0;
    for (i = 0; i < 20; i++) {
        int flag = 1;
        for (j = 0; j < *size; j++) {
            if (universalSet[i] == s1[j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            complementS1[sizeC++] = universalSet[i];
        }
    }
    *size = sizeC;
    return complementS1;
}

int main() {
    int universalSet[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int a, b, i;
    printf("Enter size of Set1, Set2: ");
    scanf("%d %d", &a, &b);
    int *s1 = (int *)malloc(a * sizeof(int));
    int *s2 = (int *)malloc(b * sizeof(int));
    printf("Enter values of Set A: ");
    for (i = 0; i < a; i++) {
        scanf("%d", &s1[i]);
    }
    printf("Enter values of Set B: ");
    for (i = 0; i < b; i++) {
        scanf("%d", &s2[i]);
    }
    int *set1;
    int *set2;
    int *set3;
    int size1, size2;

    set1 = findUnion(s1, s2, a, b, &size1);
    set1 = findComplement(set1, universalSet, &size1);
    set2 = findComplement(s1, universalSet, &a);
    set3 = findComplement(s2, universalSet, &b);
    set3 = findIntersection(set2, set3, a, b, &size2);

    printf("DeMorgan Law's Property: ");
    printf("Complement(<Set1 u Set2>): ");
	for (i = 0; i < size1; i++) {
        printf("%d ", set1[i]);
    }
    printf("\nComplement(<Set1>) n Complement(<Set2>): ");
    for (i = 0; i < size2; i++) {
        printf("%d ", set3[i]);
    }
    printf("\n");
    printf("DeMorgan Law:\n Complement(<Set1 u Set2>) == Complement(<Set1>) n Complement(<Set2>):");
    int DeMorgan = checkEquality(set1, set3, size1);
    if (DeMorgan == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    free(s1);
    free(s2);
    free(set1);
    free(set2);
    free(set3);

    return 0;
}
