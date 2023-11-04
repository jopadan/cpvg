# cpvg - cp/pv with FTXUI gauge/progress terminal status output
buffered variable block size stdio file copy C/C++ function using [FTXUI](http://github.com/ArthurSonzogni/FTXUI) for gauge/progress screen output. 

# Usage
```c
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

```

# Examples
```sh
./cpvg src dst 131072
copying:█████████████████████████████████████▋                                   170393600/324785376
copying:████████████████████████████████████████████████████████████████████████ 324785376/324785376 Finished!
```
