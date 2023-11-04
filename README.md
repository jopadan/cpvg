# cpvg - cp/pv with FTXUI gauge/progress terminal status output
buffered variable block_size stdio copyfile C/C++ function using @ArthurSonzogni's [FTXUI](http://github.com/ArthurSonzogni/FTXUI) for gauge/progress screen output. 

# Usage
```c
#include "cpvg.h"

const char* src  = "src.in";
const char* dst  = "src.out";
const block_size = 131072;
size_t written = cpvg(src, block_size, dst);

```

# Examples
```sh
./cpvg src.in src.out 131072
copying:████████████████████████████████████████████████████████████████████████ 324785376/324785376 Finished!
```
