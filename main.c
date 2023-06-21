#include "progress.h"
#include <sys/stat.h>

void* buf = NULL;
FILE* ifp = NULL;
FILE* ofp = NULL;

size_t fsize(const char* filename);
void cleanup(void);

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s FILE [FILE]\nBuffered block stdio with progress status bar\n\nThe FILE argument is an input/output filename\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	const char*  src = argv[1];
	const char*  dst = argc > 2 ? argv[2] : argv[1];
	const size_t len = fsize(src);
	size_t read = 0;
	size_t written = 0;
	void* buf = malloc(len);

	atexit(cleanup);

	/* read from src */
	FILE* ifp = fopen(src, "rb");
	if((read = fread_progress_bar(buf, src, len, 8192, ifp)) != len)
		exit(EXIT_FAILURE);

	FILE* ofp = fopen(dst, "wb");
	/* write to dst */
	if((written = fwrite_progress_bar(buf, dst, len, 8192, ofp)) != len)
		exit(EXIT_FAILURE);

	exit((read != len || written != len) ? EXIT_SUCCESS : EXIT_FAILURE);
}

size_t fsize(const char* filename)
{
	/* get file size */
	struct stat sb;
	if(stat(filename, &sb) == -1 || sb.st_size == 0)
	{
		perror("lstat");
		return 0;
	}
	return sb.st_size;
}

void cleanup()
{
	if(buf) free(buf);
	if(ifp) fclose(ifp);
	if(ofp) fclose(ofp);
}

