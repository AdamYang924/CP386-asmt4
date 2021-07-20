#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <semaphore.h>

#define p_num 20
#define r_num 20
int maximum[p_num][r_num];
int avaliable[r_num];
int allocated[p_num][r_num];
int need[p_num][r_num];

pthread_mutex_t lock;

typedef struct thread {
	int tid;
	int state;
	pthread_t handle;
	int retVal;
} Thread;

typedef struct result {
	int row;
	int col;
} fileResult;

int input();
fileResult readFile();
int Safe();
int Banker();
void* Runner(void *t);
void Print();

fileResult readFile() {
	fileResult result = { 0, 0 };
	FILE *file;
	char temp;
	file = fopen("sample4_in.txt", "r");
	if (file) {
		while ((temp = getc(file)) != EOF) {
			if (temp == ',' && result.row == 0) {
				result.col++;
			} else if (temp == '\n') {
				result.row++;
				result.col = 0;
			} else if (temp >= '0' && temp <= '9') {
				maximum[result.row][result.col] = temp - '0';
			}
		}
	}
	fclose(file);
	return result;
}

int input(){
	
}
