#include <stdio.h>
//create composition
//create symmetric reflexive and transitive
//create pritn relation fucntion

void composition(int n, float A[][n], float B[][n], float result[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float max_value = 0;
            for (int k = 0; k < n; k++) {
                float min_value = (A[i][k] < B[k][j] ? A[i][k] : B[k][j]);
                if (min_value > max_value)
                    max_value = min_value;
            }
            result[i][j] = max_value;
        }
    }
}

int is_reflexive(int n, float matrix[][n]) {
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] != 1.0)
            return 0;
    }
    return 1;
}

int is_symmetric(int n, float matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != matrix[j][i])
                return 0;
        }
    }
    return 1;
}

int is_transitive(int n, float matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                float min_value = matrix[i][k] < matrix[k][j] ? matrix[i][k] : matrix[k][j];
                if (matrix[i][j] < min_value)
                    return 0;
            }
        }
    }
    return 1;
}

void printRelation(int n, float matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3;
    float A[3][3] = {{1.0, 0.4, 0.5},
                     {0.4, 1.0, 0.6},
					 {0.5, 0.6, 1.0}};
    float result[3][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j];
        }
    }
    if(!is_reflexive(n, result) || !is_symmetric(n, result)){
    	printf("Not reflexive or not symmetric");
	}
	else{
    	while ( !is_transitive(n, result)) {
        	composition(n, result, A, result);
    	}
    	printf("Equivalence Relation: \n");
    	printRelation(n, result);
	}
    return 0;
}
