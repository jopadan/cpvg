# cpvg - cp/pv with FTXUI gauge/progress terminal status output
buffered variable block_size stdio copyfile C/C++ function using [FTXUI](http://github.com/ArthurSonzogni/FTXUI) for gauge/progress screen output. 

# Usage
```c
#include "cpvg.h"

size_t written = cpvg(src, block_size, dst);

```

# Examples
```sh
./cpvg src.in src.out 131072
copying:████████████████████████████████████████████████████████████████████████ 324785376/324785376 Finished!
```
