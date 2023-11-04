// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "cpvg.h"

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

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s FILE [FILE]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char* src = argv[1];
	char* dst = argv[argc > 2 ? 2 : 1];
	size_t BLOCK_SIZE = argc > 3 ? (size_t)strtoq(argv[3], NULL, 10) : 16384;
	size_t size = fsize(src); 

	size_t copied = cpvg(src, BLOCK_SIZE, dst);
	exit( copied == size ? EXIT_SUCCESS : EXIT_FAILURE);
}
