# rw_progress_bar
C/C++ [fread:fwrite]_progress_bar buffered block stdio functions supporting status progress bar

# Usage
```c
#include "progress.h"

size_t read    =  fread_progress_bar(ptr, filename, size, block_size, ifp);
size_t written = fwrite_progress_bar(ptr, filename, size, block_size, ofp);
```
# Examples
```sh
./progress /var/cache/distfiles/test.in /var/cache/distfiles/test.out
 /var/cache/distfiles/test.in: [====================100%]      34821768 / Finished!
/var/cache/distfiles/test.out: [====================100%]      34821768 / Finished!
```
