// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "cpvg.h"

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "Usage: %s SRC DST [BLK]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	exit(fsize(argv[1]) == cpvg(argv[1], argc > 3 ? (size_t)strtouq(argv[3], NULL, 10) : CPVG_BLOCK_SIZE, argv[2])
	     ? EXIT_SUCCESS : EXIT_FAILURE);
}
