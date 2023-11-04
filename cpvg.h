#pragma once

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/param.h>
#include <sys/stat.h>

const size_t CPVG_BLOCK_SIZE = (2 << 12) * (2 << 5);

size_t fsize(const char* path)
{
	struct stat sb;
	if(stat(path,&sb) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	return sb.st_size;
}

EXTERNC size_t cpvg(const char* src, size_t blk, const char* dst);
