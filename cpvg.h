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

EXTERNC size_t cpvg(const char* src, size_t block_size, const char* dst);

