#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int value;
    float mem_deg;
};

struct Pair *findUnion(struct Pair s1[], struct Pair s2[], int a) {
    int i;
    struct Pair *set = (struct Pair *)malloc(a * sizeof(struct Pair));
    for (i = 0; i < a; i++) {
        if (s1[i].mem_deg > s2[i].mem_deg) {
            set[i].value = s1[i].value;
            set[i].mem_deg = s1[i].mem_deg;
        } else {
            set[i].value = s2[i].value;
            set[i].mem_deg = s2[i].mem_deg;
        }
    }
    return set;
}

struct Pair *findIntersection(struct Pair s1[], struct Pair s2[], int a) {
    int i;
    struct Pair *set = (struct Pair *)malloc(a * sizeof(struct Pair));
    for (i = 0; i < a; i++) {
        if (s1[i].mem_deg < s2[i].mem_deg) {
            set[i].value = s1[i].value;
            set[i].mem_deg = s1[i].mem_deg;
        } else {
            set[i].value = s2[i].value;
            set[i].mem_deg = s2[i].mem_deg;
        }
    }
    return set;
}

struct Pair *findComplement(struct Pair s1[], int a) {
    int i;
    struct Pair *set = (struct Pair *)malloc(a * sizeof(struct Pair));
    for (i = 0; i < a; i++) {
        set[i].value = s1[i].value;
        set[i].mem_deg = 1 - s1[i].mem_deg;
    }
    return set;
}

int checkEqual(struct Pair s1[], struct Pair s2[], int a) {
    int i;
    for (i = 0; i < a; i++) {
        if (s1[i].value != s2[i].value || s1[i].mem_deg != s2[i].mem_deg) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int a, i;
    printf("Enter size of Fuzzy set: ");
    scanf("%d", &a);
    struct Pair s1[a], s2[a];
    printf("Enter pairs for Set1: ");
    for (i = 0; i < a; i++) {
        printf("Pair %d: ", i + 1);
        scanf("%d %f", &s1[i].value, &s1[i].mem_deg);
    }
    printf("Enter pairs for Set2: ");
    for (i = 0; i < a; i++) {
        printf("Pair %d: ", i + 1);
        scanf("%d %f", &s2[i].value, &s2[i].mem_deg);
    }
    struct Pair *set1, *set2, *set3;
    set1 = findUnion(s1, s2, a);
    set1 = findComplement(set1, a);

    set2 = findComplement(s1, a);
    set3 = findComplement(s2, a);
    set3 = findIntersection(set2, set3, a);
    
    int deM = checkEqual(set1, set3, a);
    
    printf("DeMorgan's Law Property: ");
    printf("\nComplement (set1 u set2): ");
    for (i = 0; i < a; i++) {
        printf("%d %.2f, ", set1[i].value, set1[i].mem_deg);
    }
    printf("\nComplement (set1) n Complement (set2): ");
    for (i = 0; i < a; i++) {
        printf("%d %.2f, ", set3[i].value, set3[i].mem_deg);
    }
	
	printf("DeMorgan's Law Property: ");
    if (deM == 1) {
        printf("\nTrue");
    } else {
        printf("\nFalse");
    }

    free(set1);
    free(set2);
    free(set3);

    return 0;
}
