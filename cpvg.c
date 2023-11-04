// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "cpvg.h"

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "Usage: %s SRC DST [BLOCK_SIZE]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char*  src = argv[1];
	char*  dst = argv[2];
	size_t blk = argc > 3 ? (size_t)strtoq(argv[3], NULL, 10) : CPVG_BLOCK_SIZE;
	size_t sze = fsize(src); 

	size_t copied = cpvg(src, blk, dst);
	exit( copied == sze ? EXIT_SUCCESS : EXIT_FAILURE);
}
