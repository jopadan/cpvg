# rw_progress_bar
Single-file header C/C++ [fread:fwrite]_progress_bar buffered block stdio functions supporting status progress bar

# Usage
```c
#include "progress.h"

FILE* ifp      = fopen(filename, "rb");
size_t read    = fread_progress_bar(ptr, filename, size, block_size, ifp, width, '=', ' ');
fclose(ifp);
FILE* ofp      = fopen(filename, "rw");
size_t written = fwrite_progress_bar(ptr, filename, size, block_size, ofp, width, '=', ' ');
fclose(ofp);
```
# Examples
```sh
./cpbar /var/cache/distfiles/test.in /var/cache/distfiles/test.out
 /var/cache/distfiles/test.in: [====================100%]      34821768 / Finished!
/var/cache/distfiles/test.out: [====================100%]      34821768 / Finished!
```
