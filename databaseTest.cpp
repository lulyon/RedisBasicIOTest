//============================================================================
// Name        : databaseTest.cpp
// Author      : luliang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <hiredis.h>

void read_redis(const char *key, char *&value, int &len) {
  const char * ip = "127.0.0.1";
	int port = 6379;
	int dbno = 1;
	redisContext *con = redisConnect(ip, port);
	if (con->err) {
		redisFree(con);
		printf("Connection error: %s", con->errstr);
		exit(-1);
	}

	printf("Reading...");
	time_t start, end;
	start = clock();
	void *reply0 = redisCommand(con, "select %d", dbno);
	void *reply1 = redisCommand(con, "GET key:%s", key);
	assert(reply0 != NULL && reply1 != NULL);

	redisReply * reply = (redisReply *) reply1;
	assert(reply->type == REDIS_REPLY_STRING);

	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);

	if (value != NULL) {
		free(value);
	}
	len = reply->len;
	int size = len * sizeof(char);
	value = (char *) malloc(size);
	memcpy(value, reply->str, size);

	freeReplyObject(reply0);
	freeReplyObject(reply1);
	redisFree(con);

	return;
}

void write_redis(const char * key, char *value, int len) {
	const char * ip = "127.0.0.1";
	int port = 6379;
	int dbno = 1;
	redisContext *con = redisConnect(ip, port);
	if (con->err) {
		redisFree(con);
		printf("Connection error: %s", con->errstr);
		exit(-1);
	}

	printf("Writing...");
	time_t start, end;
	start = clock();

	void *reply0 = redisCommand(con, "select %d", dbno);
	void *reply1 = redisCommand(con, "SET key:%s %b", key, value,
			len * sizeof(char));

	end = clock();
	printf("%f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);

	freeReplyObject(reply0);
	freeReplyObject(reply1);
	redisFree(con);
}

void read_redis_wrap(const char *key) {
	char * value = NULL;
	int len = 0;

	read_redis(key, value, len);
	if (value != NULL) {
		free(value);
		value = NULL;
	}
}

void write_redis_wrap(const char * key, char *value, int len) {
	if (value != NULL) {
		free(value);
		value = NULL;
	}
	value = (char *) malloc(len * sizeof(char));
	write_redis(key, value, len);
}

int main() {
	const int one_kilo_byte = 1 << 10;
	const int ten_kilo_byte = 10 * one_kilo_byte;
	const int hrd_kilo_byte = 10 * ten_kilo_byte;

	const int one_mega_byte = 1 << 20;
	const int ten_mega_byte = 10 * one_mega_byte;
	const int hrd_mega_byte = 10 * ten_mega_byte;

	{
		char * key = "one_kilo_byte";
		char * value = NULL;
		int len = one_kilo_byte;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
	}

	{
		char * key = "ten_kilo_byte";
		char * value = NULL;
		int len = ten_kilo_byte;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
	}

	{
		char * key = "hrd_kilo_byte";
		char * value = NULL;
		int len = hrd_kilo_byte;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
	}

	{
		char * key = "one_mega_byte";
		char * value = NULL;
		int len = one_mega_byte;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
	}

	{
		char * key = "ten_mega_byte";
		char * value = NULL;
		int len = ten_mega_byte;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
	}

	{
		char * key = "hrd_mega_byte";
		char * value = NULL;
		int len = hrd_mega_byte;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
	}

	{
		char * key = "thd_mega_byte";
		char * value = NULL;
		int len = hrd_mega_byte * 3;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
		system("/home/luliang/redis-2.6.10/src/redis-cli flushall");
	}

	{
		char * key = "fhd_mega_byte";
		char * value = NULL;
		int len = hrd_mega_byte * 5;
		printf("%s read write testing...\n", key);
		write_redis_wrap(key, value, len);
		read_redis_wrap(key);
		//		system("/home/luliang/redis-2.6.10/src/redis-cli flushall");
	}

	return 0;
}

