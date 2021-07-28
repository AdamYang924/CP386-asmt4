# CP386-assignment 4
## Motivation
- To practice the Banker's algorithm to avoid deadlock with multiple type of resources
## Installation
- Eclipse to write code and test the program in Linux virtual machine
## Screen shots
![WechatIMG417](https://user-images.githubusercontent.com/87817568/127261475-b4b6b081-d5e0-49f9-be70-6337d0d24c0c.jpeg)


## Individual contribution
- Ning Nan is responsible for writting the module that read input from user, build the runner that runs in mutex.
- Yongtai Yang is respinsible for writting the module that read from file, implement the banker algorithm, and check if the state is safe or not.
## Features
- To determine if the given request is in the safe state
- To avoid deadlock
- To indicate the resources avaliable resources after the execution of all exist request.

## Features

## Test cases
	yangyongtai@yangyongtaideMacBook-Pro src % ./Q1 3 3 2           
	The number of customers is: 5 
	Currently Available resources:
	3 3 2 
	Maximum resources from file:
	7 5 3 
	3 2 2 
	9 0 2 
	2 2 2 
	4 3 3 
	Enter Command: RQ0010
	Request Completed!
	Enter Command: RQ1200
	Request Completed!
	Enter Command: RQ2302
	Request Completed!
	Enter Command: RQ3211
	Request Completed!
	Enter Command: RQ4002
	Request Completed!
	Enter Command: *
	Available:
	3 3 2 
	Allocated:
	0 1 0 
	2 0 0 
	3 0 2 
	2 1 1 
	0 0 2 
	Maximum:
	7 5 3 
	3 2 2 
	9 0 2 
	2 2 2 
	4 3 3 
	Need:
	7 4 3 
	1 2 2 
	6 0 0 
	0 1 1 
	4 3 1 
	Enter Command: Run

	Safe Sequence is: <1 3 4 0 2 >
	Now going to executing the threads: 
	-->  Customer 1 :
		 Allocated Resources: 2 0 0 
		 Needed Resources: 1 2 2 
		 Available Resources: 3 3 2 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 5 3 2 
	-->  Customer 3 :
		 Allocated Resources: 2 1 1 
		 Needed Resources: 0 1 1 
		 Available Resources: 5 3 2 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 7 4 3 
	-->  Customer 4 :
		 Allocated Resources: 0 0 2 
		 Needed Resources: 4 3 1 
		 Available Resources: 7 4 3 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 7 4 5 
	-->  Customer 0 :
		 Allocated Resources: 0 1 0 
		 Needed Resources: 7 4 3 
		 Available Resources: 7 4 5 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 7 5 5 
	-->  Customer 2 :
		 Allocated Resources: 3 0 2 
		 Needed Resources: 6 0 0 
		 Available Resources: 7 5 5 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 10 5 7 
## Code example

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

## About Developers
- Yongtai Yang
- Ning Nan
## Credits
- Operating System Concepts”, 10th Edition; Abraham Silberschatz, Peter B.  Galvin,Greg Gagne; 2018; John Wiley and Sons.
- Dr. Sukhjit Singh Sehra's lecture and his wonderful lecture slide
## Licence
- MIT Licence
