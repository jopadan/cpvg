#pragma once
#include <stdlib.h>
#include <stdio.h>

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream);
size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream);
