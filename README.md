# cpvg - cp/pv with FTXUI gauge/progress terminal status output
buffered variable block size stdio file copy C/C++ function using [FTXUI](http://github.com/ArthurSonzogni/FTXUI) for gauge/progress screen output. 

# Usage
```c
#include "cpvg.h"

size_t written = cpvg("src", 131072, "dst");

```

# Examples
```sh
./cpvg src dst 131072
copying:█████████████████████████████████████▋                                   170393600/324785376
copying:████████████████████████████████████████████████████████████████████████ 324785376/324785376 Finished!
```
