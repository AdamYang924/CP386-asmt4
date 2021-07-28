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

## Test cases
	yangyongtai@yangyongtaideMacBook-Pro src % ./Question1 10 5 7 8        
	The number of customers is: 5 
	Currently Available resources:
	10 5 7 8 
	Maximum resources from file:
	6 4 7 3 
	4 2 3 2 
	2 5 3 3 
	6 3 3 2 
	5 5 7 5 
	Enter Command: RQ01001
	Request Completed!
	Enter Command: RQ11111
	Request Completed!
	Enter Command: RQ22222
	Request Completed!
	Enter Command: RQ31111
	Request Completed!
	Enter Command: RQ41000
	Request Completed!
	Enter Command: Status
	Available:
	4 1 3 3 
	Allocated:
	1 0 0 1 
	1 1 1 1 
	2 2 2 2 
	1 1 1 1 
	1 0 0 0 
	Maximum:
	6 4 7 3 
	4 2 3 2 
	2 5 3 3 
	6 3 3 2 
	5 5 7 5 
	Need:
	5 4 7 2 
	3 1 2 1 
	0 3 1 1 
	5 2 2 1 
	4 5 7 5 
	Enter Command: Run

	Safe Sequence is: <1 3 2 4 0 >
	Now going to executing the threads: 
	-->  Customer 1 :
		 Allocated Resources: 1 1 1 1 
		 Needed Resources: 3 1 2 1 
		 Available Resources: 4 1 3 3 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 5 2 4 4 
	-->  Customer 3 :
		 Allocated Resources: 1 1 1 1 
		 Needed Resources: 5 2 2 1 
		 Available Resources: 5 2 4 4 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 6 3 5 5 
	-->  Customer 2 :
		 Allocated Resources: 2 2 2 2 
		 Needed Resources: 0 3 1 1 
		 Available Resources: 6 3 5 5 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 8 5 7 7 
	-->  Customer 4 :
		 Allocated Resources: 1 0 0 0 
		 Needed Resources: 4 5 7 5 
		 Available Resources: 8 5 7 7 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 9 5 7 7 
	-->  Customer 0 :
		 Allocated Resources: 1 0 0 1 
		 Needed Resources: 5 4 7 2 
		 Available Resources: 9 5 7 7 
		 Thread has started
		 Thread has finished
		 Thread is releasing resources...
		 New Available: 10 5 7 8 
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
