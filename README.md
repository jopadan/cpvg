# rw_progress_bar
[fread:fwrite]_progress_bar buffered block stdio functions supporting status progress bar

# Usage
```c
#include "progress.h"

size_t read    =  fread_progress_bar(ptr, filename, size, block_size, ifp);
size_t written = fwrite_progress_bar(ptr, filename, size, block_size, ofp);
```
