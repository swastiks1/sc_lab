//Back propagation 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_SIZE 2
#define HIDDEN_SIZE 2
#define OUTPUT_SIZE 1
#define LEARNING_RATE 0.25
#define EPOCHS 1
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x);
}

void feedforward(int inputs[INPUT_SIZE], double Z[HIDDEN_SIZE], double Y[OUTPUT_SIZE], double V[INPUT_SIZE][HIDDEN_SIZE], double W[HIDDEN_SIZE][OUTPUT_SIZE], double bias_hidden[HIDDEN_SIZE], double bias_output) {
    // Calculate hidden layer outputs
    int i,j;
    for (i = 0; i < HIDDEN_SIZE; i++) {
        double sum = 0;
        for (j = 0; j < INPUT_SIZE; j++) {
            sum += inputs[j] * V[j][i];
        }
        Z[i] = sigmoid(sum + bias_hidden[i]);
        printf("Z%d=%.4f\n",i,Z[i]);
    }
    // Calculate output layer output
    for (i = 0; i < OUTPUT_SIZE; i++) {
        double sum = 0;
        for (j = 0; j < HIDDEN_SIZE; j++) {
            sum += Z[j] * W[j][i];
        }
        Y[i] = sigmoid(sum + bias_output);
        printf("Y%d=%.4f\n",i,Y[i]);
    }
}

void backpropagation(int inputs[INPUT_SIZE], int expected_output[OUTPUT_SIZE], double Y[OUTPUT_SIZE], double Z[HIDDEN_SIZE], double V[INPUT_SIZE][HIDDEN_SIZE], double W[HIDDEN_SIZE][OUTPUT_SIZE], double bias_hidden[HIDDEN_SIZE], double bias_output) {
    // Calculate output layer errors
    int i,j;
    double output_errors[OUTPUT_SIZE];
    for (i = 0; i < OUTPUT_SIZE; i++) {
        output_errors[i] = expected_output[i] - Y[i];
    }

    // Calculate output layer deltas
    double delta_k[OUTPUT_SIZE];
    for (i = 0; i < OUTPUT_SIZE; i++) {
        delta_k[i] = output_errors[i] * sigmoid_derivative(Y[i]);
        printf("Delta_k%d=%.4f\n",i+1,delta_k[i]);
    }

    // Calculate hidden layer errors
    double delta_in[HIDDEN_SIZE];
    for (i = 0; i < HIDDEN_SIZE; i++) {
        double error = 0;
        for (j = 0; j < OUTPUT_SIZE; j++) {
            error += delta_k[j] * W[i][j];
        }
        delta_in[i] = error;
    }

    // Calculate hidden layer deltas
    double hidden_errors[HIDDEN_SIZE];
    for (i = 0; i < HIDDEN_SIZE; i++) {
        hidden_errors[i] = delta_in[i] * sigmoid_derivative(Z[i]);
        printf("delta%d=%.4f\n",i+1,hidden_errors[i]);
    }

    // Update input to hidden weights
    for (i = 0; i < INPUT_SIZE; i++) {
        for (j = 0; j < HIDDEN_SIZE; j++) {
            V[i][j] += LEARNING_RATE * hidden_errors[j] * inputs[i];
            printf("V%d%d=%.4f\n",i+1,j+1,V[i][j]);
        }
    }

    // Update bias for hidden layer
    for (i = 0; i < HIDDEN_SIZE; i++) {
        bias_hidden[i] += LEARNING_RATE * hidden_errors[i];
            printf("V0%d=%.4f\n",i+1,bias_hidden[i]);
    }

    // Update hidden to output weights
    for (i = 0; i < HIDDEN_SIZE; i++) {
        for (j = 0; j < OUTPUT_SIZE; j++) {
            W[i][j] += LEARNING_RATE * delta_k[j] * Z[i];
            printf("W%d%d=%.4f\n",i+1,j+1,W[i][j]);
        }
    }

    // Update bias for output layer
    for (i = 0; i < OUTPUT_SIZE; i++) {
        bias_output += LEARNING_RATE * delta_k[i];
        printf("W0%d=%.4f\n",i+1,bias_output);
    }
}
	
int main() {
    // Initialize random weights and biases
    double V[INPUT_SIZE][HIDDEN_SIZE]={{0.6,-.3},{-0.1,0.4}};
    double W[HIDDEN_SIZE][OUTPUT_SIZE]={{0.4},{0.1}};
    double bias_hidden[HIDDEN_SIZE]={0.3,0.5};
    double bias_output=-0.2;
    int i,epoch;

    // Input data
    int inputs[4][INPUT_SIZE] = {{-1, 1}, {-1, -1}, {1, -1}, {1, 1}};
    int expected_outputs[4][OUTPUT_SIZE] = {{1}, {0}, {1}, {0}};

// Training loop
    for (epoch = 0; epoch < EPOCHS; epoch++) {
        printf("EPOCH:%d\n",epoch+1);
        for (i = 0; i < 4; i++) {
            double Z[HIDDEN_SIZE];
            double Y[OUTPUT_SIZE];
            printf("Iteration-%d:\n",i+1);
            printf("X1=%d\n",inputs[i][0]);
            printf("X2=%d\n",inputs[i][1]);
            printf("target(t)=%d\n",expected_outputs[0][i]);
            feedforward(inputs[i], Z, Y, V, W, bias_hidden, bias_output);
            backpropagation(inputs[i], expected_outputs[i], Y, Z, V, W, bias_hidden, bias_output);
            printf("\n\n");
        }
    }
    return 0;

}

