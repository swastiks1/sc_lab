//verify Commutative,Associative and Distributive property in Fuzzy set.
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
    struct Pair *set = (struct Pair *)(malloc(a * sizeof(struct Pair)));

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
    printf("Enter size of fuzzy set: ");
    scanf("%d", &a);

    struct Pair s1[a], s2[a],s3[a];

    printf("Enter %d pairs for set-1 (value, membership degree): \n", a);
    for (i = 0; i < a; i++) {
        printf("Pair %d: ", i + 1);
        scanf("%d,%f", &s1[i].value, &s1[i].mem_deg);
    }

    printf("Enter %d pairs for set-2 (value, membership degree): \n", a);
    for (i = 0; i < a; i++) {
        printf("Pair %d: ", i + 1);
        scanf("%d,%f", &s2[i].value, &s2[i].mem_deg);
    }
    
    printf("Enter %d pairs for set-3 (value, membership degree): \n", a);
    for (i = 0; i < a; i++) {
        printf("Pair %d: ", i + 1);
        scanf("%d,%f", &s3[i].value, &s3[i].mem_deg);
    }

    struct Pair *set1,*set2,*set3;
    //commutative property s1 U s2 == s2 U s1
    set1 = findUnion(s1, s2, a);        // Union: s1 U s2
    set2 = findUnion(s2, s1, a);        // Union: s2 U s1
    int commutative=checkEqual(set1,set2,a);

    printf("\n(set1 U set2):");
    for (i = 0; i < a; i++) {
        printf("(%d,%.2f) ", set1[i].value, set1[i].mem_deg);
    }

    printf("\n(set2 U set1):");
    for (i = 0; i < a; i++) {
        printf("(%d,%.2f) ", set2[i].value, set2[i].mem_deg);
    }
    printf("\nCommutative Property : set1 U set2 = set2 U set1 : ");
    if(commutative==1)
    {
        printf("True\n");
    }
    else
    printf("False\n");

    //associative property s1 U (s2 U s3) == (s1 U s2) U s3
    set1 = findUnion(s2, s3, a);        
    set1 = findUnion(s1, set1, a);   
    set2=findUnion(s1,s2,a);
    set2=findUnion(set2,s3,a);    
    int associative=checkEqual(set1,set2,a);

    printf("\nset1 U (set2 U set3):");
    for (i = 0; i < a; i++) {
        printf("(%d,%.2f) ", set1[i].value, set1[i].mem_deg);
    }

    printf("\n(set1 U set2) U set3:");
    for (i = 0; i < a; i++) {
        printf("(%d,%.2f) ", set2[i].value, set2[i].mem_deg);
    }
    printf("\nAssociative Property : set1 U (set2 U set3) = (set1 U set2) U set3 : ");
    if(associative==1)
    {
        printf("True\n");
    }
    else
    printf("False\n");

    //Distributive property (s1 U s2) intersection s3) == (s1 intersection s3) U (s2 intersection s3)
    set1 = findUnion(s1, s2, a);        
    set1 = findIntersection(set1, s3, a);   
    set2=findIntersection(s1,s3,a);
    set3=findIntersection(s2,s3,a);    
    set2= findUnion(set2, set3, a);        

    int distributive=checkEqual(set1,set2,a);

    printf("\n(set1 U set2) intersection set3:");
    for (i = 0; i < a; i++) {
        printf("(%d,%.2f) ", set1[i].value, set1[i].mem_deg);
    }

printf("\n(set1 intersection set2) U (set2 intersection set3):");
    for (i = 0; i < a; i++) {
        printf("(%d,%.2f) ", set2[i].value, set2[i].mem_deg);
    }
    printf("\nDistributive Property : (set1 U set2) intersection set3 = (set1 intersection set3) U (set2 intersection set3) : ");
    if(distributive==1)
    {
        printf("True\n");
    }
    else
    printf("False\n");

    free(set1);
    free(set2);
    free(set3);
    return 0;
}