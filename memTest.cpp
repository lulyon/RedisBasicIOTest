//============================================================================
// Name        : memTest.cpp
// Author      : luliang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

void test(int len) {

  printf("mallocing...");
	time_t start, end;
	start = clock();

	void * src = malloc(len);
	void * dst = malloc(len);

	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);

	printf("memcpying...");
	start = clock();

	memcpy(dst, src, len);
	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);

	free(src);
	free(dst);
}

int main() {
	int size;
	{
		size = (1 << 20);
		printf("%d data memcpy testing...\n", size);
		test(size);
	}
	{
		size = (1 << 20) * 10;
		printf("%d data memcpy testing...\n", size);
		test(size);
	}
	{
		size = (1 << 20) * 100;
		printf("%d data memcpy testing...\n", size);
		test(size);
	}
	{
		size = (1 << 20) * 300;
		printf("%d data memcpy testing...\n", size);
		test(size);
	}
	{
		size = (1 << 20) * 500;
		printf("%d data memcpy testing...\n", size);
		test(size);
	}
	return 0;
}
