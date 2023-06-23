#include "progress.h"
#include <sys/stat.h>
#include <errno.h>

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
	/* get size of filename */
	const size_t len = fsize(src);
	if(len == 0)
	{
		fprintf(stderr, "%40s: File is empty!\n", src);
		exit(EXIT_FAILURE);
	}

	/* initialize buffer and r/w status */
	size_t read = 0;
	size_t written = 0;
	void* buf = malloc(len);

	/* set exit cleanup func */
	atexit(cleanup);

	/* read from src */
	FILE* ifp = fopen(src, "rb");
	if((read = fread_progress_bar(buf, src, len, 8192, ifp, 40, '|', '-')) != len)
		exit(EXIT_FAILURE);

	FILE* ofp = fopen(dst, "wb");
	/* write to dst */
	if((written = fwrite_progress_bar(buf, dst, len, 8192, ofp, 40, '|', '-')) != len)
		exit(EXIT_FAILURE);

	exit((read != len || written != len) ? EXIT_SUCCESS : EXIT_FAILURE);
}

size_t fsize(const char* filename)
{
	/* get file size */
	struct stat sb;
	if(stat(filename, &sb) == -1)
	{
		fprintf(stderr, "%40s: %s\n", filename, strerror(errno));
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

