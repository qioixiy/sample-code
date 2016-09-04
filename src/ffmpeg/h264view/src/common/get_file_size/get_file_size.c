#include<stdio.h>
#include <sys/stat.h>
#include "get_file_size.h"

#define get_file_size_1 get_file_size

unsigned long get_file_size_1(const char *path)
{
	unsigned long filesize = -1;
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL)
		return filesize;
	fseek(fp, 0L, SEEK_END);
	filesize = ftell(fp);
	fclose(fp);
	return filesize;
}

unsigned long get_file_size_2(const char *path)
{
	unsigned long filesize = -1;	
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}