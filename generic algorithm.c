//genentic algorithm

#include <stdio.h>
#include <stdlib.h>

#define POPULATION_SIZE 4

int binaryToDecimal(int binary) {
    int decimal = 0;
    int base = 1;
    while (binary > 0) {
        int lastDigit = binary % 10;
        binary = binary / 10;
        decimal += lastDigit * base;
        base *= 2;
    }

    return decimal;
}
int* decToBinary(int n) 
{ 
    int i;
    int* binaryNum = (int*)malloc(5 * sizeof(int));
    for(i=0;i<5;i++)
    {
        binaryNum[i]=0;
    }

    i = 0; 
    while (n > 0) { 
        binaryNum[5-i-1] = n % 2; 
        n = n / 2; 
        i++; 
    } 
    return binaryNum;
} 
float fitness(int x) {
    return x * x;
}
int customRound(float number) {
    if (number - (int)number >= 0.45)
        return (int)number + 1;
    else
        return (int)number;
}
int* crossover(int parent1, int parent2, int crossoverPoint,int crossoverXval[],int i) {
    int x1 = parent1 / (1 << (5 - crossoverPoint));
    int x2 = parent1 % (1 << (5 - crossoverPoint));
    int y1 = parent2 / (1 << (5 - crossoverPoint));
    int y2 = parent2 % (1 << (5 - crossoverPoint));
    int offspring = (x1 * (1 << (5 - crossoverPoint))) + y2;
    crossoverXval[i]=offspring;
    return decToBinary(offspring); 
}
//azzam khan
void mutation(int muatationChromosomes[],int offspringAfterCrossover[][5],int offspringAfterMutation[][5])
{
    int i,j;
    for(i=0;i<POPULATION_SIZE;i++)
    {
        int x=muatationChromosomes[i];
        for(j=4;j>=0;j--)
        {
            if(x%10==0)
            offspringAfterMutation[i][j]=offspringAfterCrossover[i][j];
            else
            offspringAfterMutation[i][j]=!offspringAfterCrossover[i][j];
            x=x/10;
        }
    }
}
void mutationXval(int afterMutationXval[],int offspringAfterMutation[][5])
{ 
    int i,j;
    for(i=0;i<POPULATION_SIZE;i++)
    {
        int base=1;
        int sum=0;
        for(j=4;j>=0;j--)
        {
            sum+=offspringAfterMutation[i][j]*base;
            base*=2;
        }
        afterMutationXval[i]=sum;
    }
}
void print(int offspringAfterCrossover[][5],int i)
{
    int j;
    for(j=0;j<5;j++)
    {
        printf("%d",offspringAfterCrossover[i][j]);
    }
}
int main() {
    int i,j;
    int population[POPULATION_SIZE]={1100,11001,101,10011};
    int x_value[POPULATION_SIZE];
     for(i=0;i<POPULATION_SIZE;i++)
     {
        x_value[i]=binaryToDecimal(population[i]);
     }   
    int fitnessVal[POPULATION_SIZE];
    int sum_fitness=0;
    for(i=0;i<POPULATION_SIZE;i++)
    {
        fitnessVal[i]=fitness(x_value[i]);
        sum_fitness+=fitnessVal[i];
    }
    float probabilty[POPULATION_SIZE];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        probabilty[i]=fitnessVal[i]*1.0/sum_fitness;
    }

    float perc_probabilty[POPULATION_SIZE];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        perc_probabilty[i]=probabilty[i]*100;
    }
    float avg_fitness=sum_fitness*1.0/POPULATION_SIZE;

    float expected_count[POPULATION_SIZE];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        expected_count[i]=fitnessVal[i]*1.0/avg_fitness;
    }
  
    int actual_count[POPULATION_SIZE];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        actual_count[i]=customRound(expected_count[i]);
    }

    int mating_pool[POPULATION_SIZE];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        int x=i;
        int count=actual_count[i];
        for(j=0;j<count;j++)
        {
            mating_pool[x]=population[i];
            x++;
        }
        i=x-1;
    }

    int mating_x[POPULATION_SIZE];
     for(i=0;i<POPULATION_SIZE;i++)
     {
        mating_x[i]=binaryToDecimal(mating_pool[i]);
     }  

    int crossover_points[POPULATION_SIZE] = {4, 4, 2, 2};
    int crossOver_Xval[4];
    int offspringAfterCrossover[POPULATION_SIZE][5];

for (i = 0; i < POPULATION_SIZE; i += 2) {
        int parent1 = mating_x[i];
        int parent2 = mating_x[i + 1];
        int crossoverPoint = crossover_points[i];
        int *offspring1 = crossover(parent1, parent2, crossoverPoint,crossOver_Xval,i);
        int *offspring2 = crossover(parent2, parent1, crossoverPoint,crossOver_Xval,i+1);
        for (j = 0; j < 5; j++) {
            offspringAfterCrossover[i][j] = offspring1[j];
            offspringAfterCrossover[i + 1][j] = offspring2[j];
        }
        free(offspring1); 
        free(offspring2); 
    }

    int crossOver_fitness[5];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        crossOver_fitness[i]=fitness(crossOver_Xval[i]);
    }
    int mutationChromosomes[POPULATION_SIZE]={10000,0,0,100};
    int offspringAfterMutation[POPULATION_SIZE][5];
    mutation(mutationChromosomes,offspringAfterCrossover,offspringAfterMutation);

    int afterMutationXval[POPULATION_SIZE];
    mutationXval(afterMutationXval,offspringAfterMutation);

    int afterMutationFitness[POPULATION_SIZE];
    for(i=0;i<POPULATION_SIZE;i++)
    {
        afterMutationFitness[i]=fitness(afterMutationXval[i]);
    }

    printf("Initial_population  x_val   fitness    prob    perc_prob.  expec_count    actual_count\n");
    for(i=0;i<POPULATION_SIZE;i++)
    {
        printf("%7.5d %15d %8d %11.4f %9.2f %12.4f %10d\n",population[i],x_value[i],fitnessVal[i],probabilty[i],perc_probabilty[i],expected_count[i],actual_count[i]);
    }
    printf("\n");

    printf("Mating_Pool   Cross_point    offspringAfterCrossOver   XValAfterCross  FitnessAfterCross\n");
    for(i=0;i<POPULATION_SIZE;i++)
    {
        printf("%6.5d %13d           ",mating_pool[i],crossover_points[i]);
        print(offspringAfterCrossover,i);
        printf("%23d   %17d",crossOver_Xval[i],crossOver_fitness[i]);
        printf("\n");
    }

    printf("\n");

    printf("MutationChromosomesForFlipping      offspringAfterMutation    XValAfterMutation     FitnessAfterMutation\n");
    for(i=0;i<POPULATION_SIZE;i++)
    {
        printf("%9.5d                              ",mutationChromosomes[i]);
        print(offspringAfterMutation,i);
        printf("%24d  %19d",afterMutationXval[i],afterMutationFitness[i]);
        printf("\n");

    }

//happy ending tata!!!
}

