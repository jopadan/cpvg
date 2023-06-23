#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif

size_t console_width();
void update_progress_bar(char* bar, size_t fill_last, size_t fill_now, unsigned char width, char filled, char empty);
size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty);
size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty);

size_t console_width()
{
#ifdef _WINDOWS
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left;
#else
        struct winsize win;
        if (ioctl(0, TIOCGWINSZ, &win) != -1)
		return win.ws_col;
	else
		return 0;
#endif
}

void update_progress_bar(char* bar, size_t fill_last, size_t fill_now, unsigned char length, char filled, char empty)
{
	if(fill_last == 0)
	{
		memset(bar, empty, length);
		bar[length] = '\0';
	}
	memset(bar + fill_last, filled, fill_now - fill_last);
	bar[length] = '\0';
}

size_t fread_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char bar_length, char filled, char empty)
{
	/* read status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;
	size_t width = console_width();
	bar_length = bar_length == 0 ? width : bar_length;
	char bar[bar_length];

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* read from stream in buffered block mode */
		const size_t len = MIN(size - transfered, block_size);
		if((res = fread((unsigned char*)ptr + transfered, 1, len, stream)) == 0)
			break;
		
		/* increment progress */
		size_t fill_last = progress * bar_length / 100;
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size);
		size_t fill_now = progress * bar_length / 100;

		update_progress_bar(bar, fill_last, fill_now, bar_length, filled, empty);

		/* read status progress bar output */
		printf("\r%40s: [%.*s%.03hhu%%%s] %13zu %c", filename, 
		                               (int)fill_now, bar, progress,
		                                 bar + fill_now, transfered,
		                 rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}

size_t fwrite_progress_bar(void* ptr, const char* filename, size_t size, const size_t block_size, FILE* stream, unsigned char width, char filled, char empty)
{
	/* read status progress bar variables */
	const char rotor_char[5] = "/-\\|";
	unsigned char rotor = 0;
	unsigned char progress = 0;
	size_t transfered = 0;
	char bar[width];

	for(size_t res = 0; transfered < size; rotor = (rotor + 1) % sizeof(rotor_char))
	{
		/* read from stream in buffered block mode */
		const size_t len = MIN(size - transfered, block_size);
		if((res = fwrite((unsigned char*)ptr + transfered, 1, len, stream)) == 0)
			break;
		
		/* increment progress */
		size_t fill_last = progress * width / 100;
		transfered += res;
		progress = (unsigned char)(transfered * 100 / size);
		size_t fill_now = progress * width / 100;

		update_progress_bar(bar, fill_last, fill_now, width, filled, empty);

		/* read status progress bar output */
		printf("\r%40s: [%.*s%.03hhu%%%s] %13zu %c", filename, 
		                               (int)fill_now, bar, progress,
		                                 bar + fill_now, transfered,
		                 rotor_char[transfered == size ? 0 : rotor]);

		if(res < len)
			break;
	}
	puts(transfered != size ? " Failed!" : " Finished!");

	return transfered;
}
