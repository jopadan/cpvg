#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width);
size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width);

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width)
{
	/* read status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;
	char filled[width];
	char  empty[width];
	memset(filled, '=', width);
	filled[width] = '\0';
	memset(empty, ' ', width);
	empty[width] = '\0';


	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* read from stream in buffered block mode */
		const size_t len = MIN(size - transfered, block_size);
		if((res = fread((unsigned char*)ptr + transfered, 1, len, stream)) == 0)
			break;

		/* increment progress */
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size );
		size_t filled_start = (sizeof filled - 1) * (1 - progress / 100);
		size_t  empty_start = (sizeof filled)     * (progress / 100);

		/* read status progress bar output */
		printf("\r%40s: [%s%.03hhu%%%s] %13zu %c", filename, 
		                    filled + filled_start, progress,
		                    empty + empty_start, transfered,
		       rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width)
{
	/* write status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;
	char filled[width];
	char  empty[width];
	memset(filled, '=', width);
	filled[width] = '\0';
	memset(empty, ' ', width);
	empty[width] = '\0';

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* write to stream in buffered block mode */
		const size_t len = MIN(size - transfered, block_size);
		if(((res = fwrite((unsigned char*)ptr + transfered, 1, len, stream))) == 0)
			break;

		/* increment progress */
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size );
		size_t filled_start = (sizeof filled - 1) * (1 - progress / 100);
		size_t  empty_start = (sizeof filled)     * (progress / 100);

		/* write status progress bar output */
		printf("\r%40s: [%s%.03hhu%%%s] %13zu %c", filename, 
		                    filled + filled_start, progress,
		                    empty + empty_start, transfered,
		       rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

