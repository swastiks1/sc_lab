#include <stdio.h>
//#include <stdbool.h>

// Function to print a set
void printSet(int set[], int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", set[i]);
    }
    printf("}");
}

// Function to check if two sets are equal
bool isEqual(int set1[], int size1, int set2[], int size2) {
    if (size1 != size2) return false;

    for (int i = 0; i < size1; i++) {
        if (set1[i] != set2[i]) return false;
    }

    return true;
}

// Function to sort a set
void sortSet(int set[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (set[i] > set[j]) {
                int temp = set[i];
                set[i] = set[j];
                set[j] = temp;
            }
        }
    }
}

// Function to perform set union
void setUnion(int set1[], int size1, int set2[], int size2, int result[], int *resultSize) {
    int i = 0, j = 0, k = 0;

    for (; i < size1 && j < size2; ) {
        if (set1[i] < set2[j]) {
            result[k++] = set1[i++];
        } else if (set1[i] > set2[j]) {
            result[k++] = set2[j++];
        } else {
            result[k++] = set1[i++];
            j++;
        }
    }

    for (; i < size1; ) {
        result[k++] = set1[i++];
    }
    for (; j < size2; ) {
        result[k++] = set2[j++];
    }

    *resultSize = k;
}


// Function to perform set intersection
void setIntersection(int set1[], int size1, int set2[], int size2, int result[], int *resultSize) {
    int k = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (set1[i] == set2[j]) {
                result[k++] = set1[i];
                break;
            }
        }
    }
    *resultSize = k;
}

// Function to verify commutative, associative, and distributive properties
void verifyProperties(int set1[], int size1, int set2[], int size2, int set3[], int size3) {
    int result1[size1 + size2 + size3], result2[size1 + size2 + size3], result3[size1 + size2 + size3], result4[size1 + size2 + size3];
    int resultSize1, resultSize2, resultSize3, resultSize4;

    // Sort sets
    sortSet(set1, size1);
    sortSet(set2, size2);
    sortSet(set3, size3);

    printf("Sets:\n");
    printf("A = "); printSet(set1, size1);
    printf("\nB = "); printSet(set2, size2);
    printf("\nC = "); printSet(set3, size3);
    printf("\n\n");

    // Commutative Property Verification
    printf("Commutative Property Verification:\n");
    printf("A u B = "); setUnion(set1, size1, set2, size2, result1, &resultSize1); sortSet(result1, resultSize1);
    printSet(result1, resultSize1); 
    printf("\nB u A = "); setUnion(set2, size2, set1, size1, result2, &resultSize2); sortSet(result2, resultSize2);
    printSet(result2, resultSize2); 
    printf("\n(A u B) == (B u A) : %s\n", isEqual(result1, resultSize1, result2, resultSize2) ? "True" : "False");

    printf("A n B = "); setIntersection(set1, size1, set2, size2, result1, &resultSize1); sortSet(result1, resultSize1);
    printSet(result1, resultSize1); 
    printf("\nB n A = "); setIntersection(set2, size2, set1, size1, result2, &resultSize2); sortSet(result2, resultSize2);
    printSet(result2, resultSize2); 
    printf("\n(A n B) == (B n A) : %s\n", isEqual(result1, resultSize1, result2, resultSize2) ? "True" : "False");

    // Associative Property Verification
    printf("\nAssociative Property Verification:\n");
    printf("(A u B) u C = "); setUnion(set1, size1, set2, size2, result3, &resultSize3); setUnion(result3, resultSize3, set3, size3, result1, &resultSize1); 
	sortSet(result1, resultSize1); printSet(result1, resultSize1); 
    printf("\nA u (B u C) = "); setUnion(set2, size2, set3, size3, result3, &resultSize3); setUnion(result3, resultSize3, set1, size1, result2, &resultSize2);
	sortSet(result2, resultSize2); printSet(result2, resultSize2); 
    printf("\n((A u B) u C) == (A u (B u C)) : %s\n", isEqual(result1, resultSize1, result2, resultSize2) ? "True" : "False");

    printf("(A n B) n C = "); setIntersection(set1, size1, set2, size2, result3, &resultSize3); setIntersection(result3, resultSize3, set3, size3, result1, &resultSize1); 
	sortSet(result1, resultSize1); printSet(result1, resultSize1);
    printf("\nA n (B n C) = "); setIntersection(set2, size2, set3, size3, result3, &resultSize3); setIntersection(result3, resultSize3, set1, size1, result2, &resultSize2);
	sortSet(result2, resultSize2); printSet(result2, resultSize2);
    printf("\n((A n B) n C) == (A n (B n C)) : %s\n", isEqual(result1, resultSize1, result2, resultSize2) ? "True" : "False");

    // Distributive Property Verification
    printf("\nDistributive Property Verification:\n");
    printf("A u (B n C) = "); setIntersection(set2, size2, set3, size3, result3, &resultSize3); setUnion(set1, size1, result3, resultSize3, result1, &resultSize1);
    sortSet(result1, resultSize1); printSet(result1, resultSize1);
    printf("\n(A u B) n (A u C) = "); setUnion(set1, size1, set2, size2, result3, &resultSize3); setUnion(set1, size1, set3, size3, result4, &resultSize4);
    setIntersection(result3, resultSize3, result4, resultSize4, result2, &resultSize2);
    sortSet(result2, resultSize2); printSet(result2, resultSize2);
    printf("\n(A u (B n C)) == ((A u B) n (A u C)) : %s\n", isEqual(result1, resultSize1, result2, resultSize2) ? "True" : "False");
    
    printf("A n (B u C) = "); setUnion(set2, size2, set3, size3, result3, &resultSize3); setIntersection(set1, size1, result3, resultSize3, result1, &resultSize1);
    sortSet(result1, resultSize1); printSet(result1, resultSize1);
    printf("\n(A n B) u (A n C) = "); setIntersection(set1, size1, set2, size2, result3, &resultSize3); setIntersection(set1, size1, set3, size3, result4, &resultSize4);
    setUnion(result3, resultSize3, result4, resultSize4, result2, &resultSize2);
    sortSet(result2, resultSize2); printSet(result2, resultSize2);
    printf("\n(A n (B u C)) == ((A n B) u (A n C)) : %s\n", isEqual(result1, resultSize1, result2, resultSize2) ? "True" : "False");
}

int main() {
//    int set1[] = {3, 1, 2};
//    int set2[] = {4, 3, 5};
//    int set3[] = {7, 5, 6};
    
    //General
	int i, a, b, c;
	printf("Enter Size of set A, B & C : ");
	scanf("%d %d %d", &a, &b, &c);
	int set1[a];
	int set2[b];
	int set3[c];
	int size = a+b+c;
	
	printf("Enter A elements : ");
	for(i=0; i<a; i++){
	scanf("%d", &set1[i]);
	}
	printf("Enter B elements : ");
	for(i=0; i<b; i++){
	scanf("%d", &set2[i]);
	}
	printf("Enter C elements : ");
	for(i=0; i<c; i++){
	scanf("%d", &set3[i]);
	}
    
    verifyProperties(set1, sizeof(set1) / sizeof(set1[0]), set2, sizeof(set2) / sizeof(set2[0]), set3, sizeof(set3) / sizeof(set3[0]));

    return 0;
}

