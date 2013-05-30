//============================================================================
// Name        : sharedMem.cpp
// Author      : luliang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

const int shm_size = (1 << 29);
const int shm_mode = 0600;
const char * path = "/home/luliang/result";

void err_sys(const char *str)
{
  printf("%s\n", str);
	exit(-1);
}

int main(int argc, char **argv) {

	key_t shm_key = ftok(path, 1);
	int shmid = shmget(shm_key, shm_size, IPC_CREAT | shm_mode);
	if (shmid < 0)
		err_sys("shmget error");
//	if (shmctl(shmid, SHM_LOCK, 0) == -1)
//		err_sys("shmctl error");

	while (1) {
		sleep(1);
	}
	return 0;
}
