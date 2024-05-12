#include <stdio.h>
void printSet(float Set[], int n){
	int i;
	printf("{");
	for(i=0; i<n; i++){
		printf("(%d, %.2f), ", i, Set[i]);
	}
	printf("\b\b}\n");
}

void UnionFSet(float Set1[], float Set2[], int nU){
	int i;
	float newSet[nU];
	for(i=0;i<nU;i++){
		newSet[i] = ((Set1[i] > Set2[i]) ? Set1[i] : Set2[i]);
	}
	printSet(newSet, nU);
}

void IntersectionFSet(float Set1[], float Set2[], int nU){
	int i;
	float newSet[nU];
	for(i=0;i<nU;i++){
		newSet[i] = ((Set1[i] < Set2[i]) ? Set1[i] : Set2[i]);
	}
	printSet(newSet, nU);
}

void ComplementFSet(float Set1[], int nU){
	int i;
	float newSet[nU];
	for(i=0;i<nU;i++){
		newSet[i] = (1-Set1[i]);
	}
	printSet(newSet, nU);
}

void SetDifferenceFSet(float Set1[], float Set2[], int nU){
	int i;
	float newSet[nU];
	for(i=0;i<nU;i++){
		newSet[i] = ((Set1[i] > Set2[i]) ? Set1[i] - Set2[i] : 0);
	}
	printSet(newSet, nU);
}

int main(){
	int nU, i;
	printf("Enter the number of elements in the Universe of Discourse: ");
	scanf("%d", &nU);
	float Set1[nU], Set2[nU];
	printf("Enter the membership values of Set 1: ");
	for(i=0; i<nU; i++){
		scanf("%f",&Set1[i]);
	}
	printf("Enter the membership values of Set 2: ");
	for(i=0; i<nU; i++){
		scanf("%f",&Set2[i]);
	}
	
	printf("\nThe Fuzzy Set 1 is: ");
	printSet(Set1, nU);
	printf("The Fuzzy Set 2 is: ");
	printSet(Set2, nU);
	
	printf("\nUnion of Set1 and Set2 is: ");
	UnionFSet(Set1, Set2, nU);
	printf("\nIntersection of Set1 and Set2 is: ");
	IntersectionFSet(Set1, Set2, nU);
	printf("\nComplement of Set1 is: ");
	ComplementFSet(Set1, nU);
	printf("Complement of Set2 is: ");
	ComplementFSet(Set2, nU);
	printf("\nSet Difference Set1 - Set2 is: ");
	SetDifferenceFSet(Set1, Set2, nU);
	printf("Set Difference Set2 - Set1 is: ");
	SetDifferenceFSet(Set2, Set1, nU);
}