#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#define A 9;
#define e 2.718281
// LI TAO
//print
void printArray(double M1[], double M2[], int N) {
    printf(" M1 :");
    for (int i = 0; i < N; i++) {
        printf("%lf ", M1[i]);
    }
    printf(" M2 :");
    for (int i = 0; i < N; i++) {
        printf("%lf ", M2[i]);
    }
    printf("\n");
}
//Map M1


//MAP M2  
double factorial(double x) { //zkw验证
    double result = 1;
    while (x != 1) {
        result *= x;
        x--;
    }
    return result;
}

double calculateSinSum(double arr[], int size) {
    double sinSum = 0.0;
    for (int i = 0; i < size; i++) {
        if ((int)(arr[i] / arr[0]) % 2 == 0) {
            sinSum += sin(arr[i]);
        }
    }
    return sinSum;
}

//heapSort
void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(double arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(double arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

//A = 9
int main(int argc, char* argv[])
{
    int i, N;
    unsigned int seed;
    struct timeval T1, T2;
    long delta_ms;
    N = atoi(argv[1]); /* N equals the first command-line parameter */
    gettimeofday(&T1, NULL); /* remember the current time T1 tv is time,tz is shiqu*/
    for (i = 0; i < 50; i++) /* 50 experiments */
    {
        srand(i); /* initialize the initial value of the RNG */
        double* M1 = (double*)malloc(N * sizeof(double));
        double* M2 = (double*)malloc((N / 2) * sizeof(double));
        // double M1[] = {8.2,4.233,5.21,1.22,2356,7.22,1.212};
        // double M2[] = {2.11,2.45,5.22};

        // 1.Generate Stage

        // init M1
        for (int i = 0; i < N; i++) {
            double rd = (double)(rand_r(&seed) % 101) / 101;
            M1[i] = (rand_r(&seed) % 10) + 1 + rd;
            printf("%lf ", M1[i]);
        }
        printf("\n");
        // init M2
        // [min , max -1]
        for (int i = 0; i < N / 2; i++) {
            int max = 10 * A;
            int min = A;
            double rd = (double)(rand_r(&seed) % 101) / 101;
            M2[i] = (double)((rand() % ((max + 1) - min + 1)) + min) + rd;
            printf("%lf ", M2[i]);
        }
        printf("\n");

        // 2.MAP STAGE
        //	tanh
        for (int i = 0; i < N; i++) {
            M1[i] = tanh(M1[i]) - 1;
        }

        //	copy M2 and add
        double* M2_copy = (double*)malloc((N / 2) * sizeof(double));
        for (int i = 0; i < N / 2; i++) {
            M2_copy[i] = M2[i];
        }

        for (int i = 1; i < N / 2; i++) {
            M2[i] = M2_copy[i - 1] + M2_copy[i];
        }

        //	cosine M2
        for (int i = 0; i < N / 2; i++) {
            M2[i] = cos(M2[i]);
        }

        // 3.Merge Stage
        for (int i = 0; i < N / 2; i++) {
            M2[i] = fmax(M1[i], M2[i]);
        }

        // 4.Sort Stage
        heapSort(M2, N / 2);

        // 5.Reduce Stage
        //	sin and get sum
        int res_sum = 0;
        for (int i = 1; i < N / 2; i++) {
            M2[i] /= M2[0];
            if ((int)M2[i] % 2) {
                res_sum += sin(M2[i]);
            }
        }
        M2[0] = 1;
    }
    gettimeofday(&T2, NULL); /* remember the current time T2 */
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms); /* T2 -T1 */
    return 0;
}
/* /home/user/gcc -o3 -Wall -Werror -o lab1-seq lab1.c   non-parallelized command*/
/* /home/user/gcc -o3 -Wall -Werror -floop-parallelize-all-ftree-parallelize-loops=K lab1.c -o lab1-par-K    parallelized command*/
/*ulimit -c unlimited  only useful in current shell*/
/* ID SUM = 726960101 */
/* A = 726960101%47 = 9 */
// variant 1 = 3
// variant 2 = 2
// variant 3 = 4
// variant 4 = 3