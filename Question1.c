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
int Safe() {
	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			if (need[i][j] < 0) {
				printf("Not Safe!");
				return 1;
			}
		}
	}
	return 0;
}

int Banker() {
	int p[p_num];
	int result[p_num];
	int idx = 0;
	int temp_avail[p_num][r_num];
	for (int i = 0; i < p_num; i++) {
		p[i] = 0;
		for (int j = 0; j < r_num; j++) {
			temp_avail[i][j] = avaliable[i][j];
		}
	}

	for (int k = 0; k < p_num; k++) {
		for (int i = 0; i < p_num; i++) {
			if (p[i] == 0) {
				int flag = 0;
				for (int j = 0; j < r_num; j++) {
					if (temp_avail[j] < need[i][j]) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					result[idx++] = i;
					for (int l = 0; l < r_num; l++) {
						temp_avail[l] += allocation[i][l];
					}
					p[i] = 1;
				}

			}
		}
	}
	return result;
}
