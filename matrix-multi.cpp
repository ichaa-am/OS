// CPP Program to multiply two matrix using pthreads 
#include <bits/stdc++.h> 
#include <chrono>
using namespace std; 
using namespace chrono;
// maximum size of matrix 
#define MAX 1000

// maximum number of threads 
#define MAX_THREAD 4096 

int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matC[MAX][MAX]; 
int step_i = 0; 
int mymax;

void* multi(void* arg) 
{ 
	int core = step_i++; 

	// Each thread computes 1/MAX_THREAD th of matrix multiplication 
	for (int i = core * MAX / mymax; i < (core + 1) * MAX / mymax; i++) 
		for (int j = 0; j < MAX; j++) 
			for (int k = 0; k < MAX; k++) 
				matC[i][j] += matA[i][k] * matB[k][j]; 
} 

// Driver Code 
int main() 
{ 
	
	// Generating random values in matA and matB 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) { 
			matA[i][j] = rand() % 10; 
			matB[i][j] = rand() % 10; 
		} 
	}  

	printf("how many threads: ");
	scanf("%d", &mymax);
	fflush(stdin);
	auto a = high_resolution_clock::now();	
	// declaring four threads 
	pthread_t threads[MAX_THREAD]; 

	// Creating four threads, each evaluating its own part 
	for (int i = 0; i < mymax; i++) { 
		int* p; 
		pthread_create(&threads[i], NULL, multi, (void*)(p)); 
	} 

	// joining and waiting for all threads to complete 
	for (int i = 0; i < mymax; i++) 
		pthread_join(threads[i], NULL);	 

	auto b = high_resolution_clock::now();
	cout << "Using " << mymax << " threads" << endl;
	cout << "Took " << duration_cast<milliseconds>(b - a).count() << " milliseconds" <<  endl;
	return 0; 
}
