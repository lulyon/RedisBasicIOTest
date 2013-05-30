//============================================================================
// Name        : sharedMemClient.cpp
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
#include <time.h>

const char * path = "/home/luliang/result";

void err_sys(const char *str) {
  printf("%s\n", str);
	exit(-1);
}

void read(void *data, int len) {
	key_t shm_key = ftok(path, 1);
	int shmid = shmget(shm_key, 0, 0);
	if (shmid < 0)
		err_sys("shmget error");
	void *mem = shmat(shmid, (const void*) 0, 0);
	if (mem < 0)
		err_sys("shmat error");

	memcpy(data, mem, len);
}

void write(void *data, int len) {
	key_t shm_key = ftok(path, 1);
	int shmid = shmget(shm_key, 0, 0);
	if (shmid < 0)
		err_sys("shmget error");
	void *mem = shmat(shmid, (const void*) 0, 0);
	if (mem < 0)
		err_sys("shmat error");
	memcpy(mem, data, len);
}

void readwrap(int len) {
	printf("mallocing...");
	time_t start, end;
	start = clock();

	void *data = malloc(len);
	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);

	printf("Reading...");
	start = clock();

	read(data, len);

	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);
	free(data);
}

void writewrap(int len) {
	printf("mallocing...");
	time_t start, end;
	start = clock();

	void *data = malloc(len);
	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);

	printf("Writing...");
	start = clock();

	write(data, len);

	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);
	free(data);
}

int main() {

	int shm_size;

	{
		shm_size = (1 << 20);
		printf("%d read write testing...\n", shm_size);
		writewrap(shm_size);
		readwrap(shm_size);
	}

	{
		shm_size = (1 << 20) * 10;
		printf("%d read write testing...\n", shm_size);
		writewrap(shm_size);
		readwrap(shm_size);
	}

	{
		shm_size = (1 << 20) * 100;
		printf("%d read write testing...\n", shm_size);
		writewrap(shm_size);
		readwrap(shm_size);
	}

	{
		shm_size = (1 << 20) * 300;
		printf("%d read write testing...\n", shm_size);
		writewrap(shm_size);
		readwrap(shm_size);
	}
	{
		shm_size = (1 << 20) * 500;
		printf("%d read write testing...\n", shm_size);
		writewrap(shm_size);
		readwrap(shm_size);
	}

	printf("finished!\n");
	return 0;
}
