#include <stdio.h>
void printSet(int Set[], int n){
	int i;
	printf("{");
	for(i=0; i<n; i++){
		printf("%d, ",Set[i]);
	}
	printf("\b\b}\n");
}

void UnionSet(int Set1[], int n1, int Set2[],int n2){
	int i,j, USet[100], k=0;
	for(i=0;i<n1;i++){
		USet[k]=Set1[i];
		k++;
	}
	for(i=0;i<n2;i++){
		int isDuplicate=0;
		for(j=0;j<n1;j++){
			if(Set2[i]==Set1[j]){
				isDuplicate=1;
				break;
			}
		}
		if(!isDuplicate){
			USet[k]=Set2[i];
			k++;
		}
	}
	printSet(USet, k);
}

void IntersectionSet(int Set1[], int n1, int Set2[],int n2){
	int i,j, ISet[100], k=0;
	for(i=0;i<n1;i++){
		for(j=0;j<n2;j++){
			if(Set1[i]==Set2[j]){
				ISet[k]=Set1[i];
				k++;
				break;
			}
		}
	}
	printSet(ISet, k);
}

void ComplementSet(int UnivSet[], int Set[], int nU, int nSet) {
    int i,j, CSet[100], k=0;
    for (i = 0; i < nU; i++) {
        int isMember = 0;
        for (j = 0; j < nSet; j++) {
            if (UnivSet[i] == Set[j]) {
                isMember = 1;
                break;
            }
        }
        if (!isMember){
            CSet[k]=UnivSet[i];
            k++;
    	}
    }
    printSet(CSet, k);
}

void SetDifference(int Set1[], int Set2[], int n1, int n2) {
    int i,j, DSet[100], k=0;
    for (i = 0; i < n1; i++) {
        int isPresentInSet2 = 0;
        for (j = 0; j < n2; j++) {
            if (Set1[i] == Set2[j]) {
                isPresentInSet2 = 1;
                break;
            }
        }
        if (!isPresentInSet2){
            DSet[k]=Set1[i];
            k++;
    	}
    }
    printSet(DSet, k);
}

int main(){
	int n1, n2, nU;
	int i; 
	printf("Enter the length of Set1, Set2 and Universal Set: ");
	scanf("%d %d %d", &n1, &n2, &nU);
	int Set1[n1], Set2[n2], UnivSet[nU];
	printf("\nEnter 1st Set: ");
	for(i=0; i<n1; i++){
		scanf("%d",&Set1[i]);
	}
	printf("\nEnter 2nd Set: ");
	for(i=0; i<n2; i++){
		scanf("%d",&Set2[i]);
	}
	printf("\nEnter Universal Set: ");
	for(i=0; i<nU; i++){
		scanf("%d",&UnivSet[i]);
	}
	printf("\nSet1: ");
	printSet(Set1, n1);
	printf("Set2: ");
	printSet(Set2, n2);
	printf("Universal Set: ");
	printSet(UnivSet, nU);

	printf("Union of Set1 & Set2: ");
	UnionSet(Set1, n1, Set2, n2);
	printf("Intersection of Set1 & Set2: ");
	IntersectionSet(Set1, n1, Set2, n2);
	printf("Complement of Set1: ");
	ComplementSet(UnivSet, Set1, nU, n1);
	printf("Complement of Set2: ");
	ComplementSet(UnivSet, Set2, nU, n2);
	printf("Set Difference Set1-Set2: ");
	SetDifference(Set1, Set2, n1, n2);
	printf("Set Difference Set2-Set1: ");
	SetDifference(Set2, Set1, n2, n1);
}