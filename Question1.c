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
int allocation[p_num][r_num];
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
void readFile();
int Safe();
void Banker();
void* Runner(void *t);
void Print();
void logStart(int tID);
void logFinish(int tID);
fileResult result = { 0, 0 };
int bk_res[p_num];

int main(int argc, char *argv[]) {
	int counter;
	if (argc < 3) {

		printf("ERROR: wrong input format\n");
		return -1;
	} else {

		for (counter = 0; counter < argc - 1; counter++)
			avaliable[counter] = atoi(argv[counter + 1]);
	}

	if (pthread_mutex_init(&lock, NULL) != 0) {

		printf("\n ERROR: Mutex Init\n");
		return 1;
	}

	readFile();
	printf("The number of customers is: %d \n", result.row);

	printf("Currently Available resources:\n");
	for (int j = 0; j < result.col; j++) {
		printf("%d ", avaliable[j]);
	}
	printf("\n");
	printf("Maximum resources from file:\n");
	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			printf("%d ", maximum[i][j]);
		}
		printf("\n");
	}

	input();

	return 0;
}

void readFile() {

	FILE *file;
	char temp;

	int counter = 0;

	file = fopen("sample4_in.txt", "r");
	if (file) {
		while ((temp = getc(file)) != EOF) {
			if (temp == ',') {
				if (result.row == 0) {
					result.col++;
				}
				counter++;
			} else if (temp == '\n') {
				result.row++;
				counter = 0;
			} else if (temp >= '0' && temp <= '9') {
				maximum[result.row][counter] = temp - '0';
			}
		}
		result.col++;
		result.row++;
	}

	fclose(file);
	return;
}

int input() {
	for (int i = 0; i < p_num; i++) {
		for (int j = 0; j < r_num; j++) {
			allocation[i][j] = 0;
		}
	}
	int flag = 1;
	int safe;
	while (flag) {
		char string[r_num + 3];
		char *temp = string;
		printf("Enter Command: ");
		scanf("%s", temp);
		if (*temp == 'S') {
			Print();
		} else if (*(temp + 1) == 'u') {
			Banker();
			printf("\nSafe Sequence is: <");

			for (int i = 0; i < result.row; i++) {
				printf("%d ", bk_res[i]);
			}
			printf(">\nNow going to executing the threads: \n");
			for (int i = 0; i < result.row; i++) {
				Thread *t = NULL;
				t = (Thread*) malloc(sizeof(Thread));
				t->tid = bk_res[i];
				t->state = 1;
				t->retVal = pthread_create(&(t->handle), NULL, Runner, t);
				sleep(1);
			}
			flag = 0;
		} else if ((*(temp + 2) - 48) >= result.row) {
			printf("ERROR: Overflow\n");
			return 1;

		} else if (*(temp + 1) == 'Q') {
			int row = *(temp + 2) - 48;
			int pre_allocation[p_num][r_num];
			int pre_need[p_num][r_num];

			for (int i = 0; i < result.col; i++) {
				pre_allocation[row][i] = allocation[row][i];
				pre_need[row][i] = need[row][i];
				allocation[row][i] += *(temp + i + 3) - 48;
				need[row][i] = maximum[row][i] - allocation[row][i];
			}
			safe = Safe();
			if (safe == 1) {
				printf("Request denied\n");
				for (int i = 0; i < result.col; i++) {
					allocation[row][i] = pre_allocation[row][i];
					need[row][i] = pre_need[row][i];
				}
			} else {
				for (int i = 0; i < result.col; i++) {
					avaliable[i] -= allocation[row][i];
				}
				printf("Request Completed!\n");
			}

		} else if (*(temp + 1) == 'L') {
			int row = *(temp + 2) - 48;
			for (int i = 3; i < result.col + 3; i++) {
				allocation[row][i - 3] -= *(temp + i) - 48;
				need[row][i] = maximum[row][i] - allocation[row][i];
			}
			printf("Request Completed!\n");
		}

	}
	return 0;
}

int Safe(fileResult *fr) {
	for (int i = 0; i < fr->row; i++) {
		for (int j = 0; j < fr->col; j++) {
			if (need[i][j] < 0) {
				printf("Not Safe!");
				return 1;
			}
		}
	}
	return 0;
}

void Banker() {
	int p[result.row];

	int idx = 0;
	int temp_avail[result.col];
	for (int i = 0; i < result.row; i++) {
		p[i] = 0;
	}
	for (int j = 0; j < result.col; j++) {
		temp_avail[j] = avaliable[j];
	}

	for (int k = 0; k < result.row; k++) {
		for (int i = 0; i < result.row; i++) {
			if (p[i] == 0) {
				int flag = 0;
				for (int j = 0; j < result.col; j++) {
					if (temp_avail[j] < need[i][j]) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					bk_res[idx++] = i;
					for (int l = 0; l < result.col; l++) {
						temp_avail[l] += allocation[i][l];
					}
					p[i] = 1;
				}

			}
		}
	}
	return;
}
void logStart(int tID) {
	printf("\t Thread has started\n");
}

void logFinish(int tID) {
	printf("\t Thread has finished\n");
}
void* Runner(void *t) {
	pthread_mutex_lock(&lock);

	int id = ((Thread*) t)->tid;
	printf("-->  Customer %d :\n", id);
	printf("\t Allocated Resources: ");
	for (int i = 0; i < result.col; i++) {
		printf("%d ", allocation[id][i]);
	}
	printf("\n");

	printf("\t Needed Resources: ");
	for (int i = 0; i < result.col; i++) {
		printf("%d ", need[id][i]);
	}
	printf("\n");

	printf("\t Available Resources: ");
	for (int i = 0; i < result.col; i++) {
		printf("%d ", avaliable[i]);
	}
	printf("\n");
	logStart(((Thread*) t)->tid);
	logFinish(((Thread*) t)->tid);

	printf("\t Thread is releasing resources...\n");

	for (int i = 0; i < result.col; i++) {
		avaliable[i] += allocation[id][i];
	}
	printf("\t New Available: ");
	for (int i = 0; i < result.col; i++) {
		printf("%d ", avaliable[i]);
	}
	printf("\n");

	pthread_mutex_unlock(&lock);
	pthread_exit(0);
}

void Print() {
	printf("Available:\n");
	for (int j = 0; j < result.col; j++) {
		printf("%d ", avaliable[j]);
	}
	printf("\n");

	printf("Allocated:\n");
	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			printf("%d ", allocation[i][j]);
		}
		printf("\n");
	}
	printf("Maximum:\n");
	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			printf("%d ", maximum[i][j]);
		}
		printf("\n");
	}
	printf("Need:\n");
	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
}

