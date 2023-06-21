#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "sys/param.h"

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream);
size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream);

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream)
{
	/* read status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* read from stream in bufferd block mode */
		const size_t len = MIN(size - transfered, block_size);
		if((res = fread((unsigned char*)ptr + transfered, 1, len, stream)) == 0)
			break;

		transfered += res;
		progress = (unsigned char)(transfered * 100 / size );

		/* read status progress bar output */
		printf("\r%40s: [%.*s%.03hhu%%%.*s] %13zu %c", filename, 
		            progress / 5, "====================", progress,
		       20 - progress / 5, "                    ", transfered,
		            rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream)
{
	/* write status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* write to stream in bufferd block mode */
		const size_t len = MIN(size - transfered, block_size);
		if(((res = fwrite((unsigned char*)ptr + transfered, 1, len, stream))) == 0)
			break;
			
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size );

		/* write status progress bar output */
		printf("\r%40s: [%.*s%.03hhu%%%.*s] %13zu %c", filename, 
		            progress / 5, "====================", progress,
		       20 - progress / 5, "                    ", transfered,
		            rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

