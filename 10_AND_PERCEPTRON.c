#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_SIZE 2
#define LEARNING_RATE 0.1
#define MAX_EPOCHS 1000
#define THRESHOLD 0.0

float bipolar_sigmoid(float x) {
    return (2 / (1 + exp(-x))) - 1;
}

int perceptron(float input[INPUT_SIZE], float weights[INPUT_SIZE], float bias) {
    float sum = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        sum += input[i] * weights[i];
    }
    sum += bias;
    return (sum >= THRESHOLD ? 1 : -1);
}

int train(float input[][INPUT_SIZE], int targets[], float weights[], float *bias) {
    int error;
    int epoch = 0;
    do {
        error = 0;
        for (int i = 0; i < 4; i++) {
            int output = perceptron(input[i], weights, *bias);
            int e = targets[i] - output;
            if (e != 0) {
                error++;
                for (int j = 0; j < INPUT_SIZE; j++) {
                    weights[j] += LEARNING_RATE * e * input[i][j];
                }
                *bias += LEARNING_RATE * e;
            }
        }
        epoch++;
    } while (error != 0 && epoch < MAX_EPOCHS);
    return epoch;
}

int main() {
    float input[][INPUT_SIZE] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    int targets[] = {-1, -1, -1, 1};
    float weights[INPUT_SIZE];
    float bias = ((float)rand() / RAND_MAX) - 0.5;
    for (int i = 0; i < INPUT_SIZE; i++) {
        weights[i] = ((float)rand() / RAND_MAX) - 0.5;
    }
    int epochs = train(input, targets, weights, &bias);
    printf("Trained Weights: ");
    for (int i = 0; i < INPUT_SIZE; i++) {
        printf("%.2f ", weights[i]);
    }
    printf("\nTrained bias: %.2f\n", bias);
    printf("\nTesting the perceptron\n");
    for (int i = 0; i < 4; i++) {
        int output = perceptron(input[i], weights, bias);
        printf("Input: (%d, %d), Output: %d\n", (int)input[i][0], (int)input[i][1], output);
    }
    printf("Converged after %d epochs.\n", epochs);
    return 0;
}
