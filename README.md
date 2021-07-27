# CP386-assignment 4
## Motivation
- To practice the Banker's algorithm to avoid deadlock with multiple type of resources
## Installation
- Eclipse to write code and test the program in Linux virtual machine
## Screen shots

## Individual contribution
- Ning Nan is responsible for writting the module that read input from user, build the runner that runs in mutex.
- Yongtai Yang is respinsible for writting the module that read from file, implement the banker algorithm, and check if the state is safe or not.
## Features
- To determine if the given request is in the safe state
- To avoid deadlock
- To indicate the resources avaliable resources after the execution of all exist request.
## Test
## Code example
('''

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

''')
## Authors
- Yongtai Yang
- Ning Nan
## Credits
## Licence
