# memPool
[![Workflos for unit test & misra](https://github.com/amorniroli/memPool/actions/workflows/workflow.yml/badge.svg)](https://github.com/amorniroli/memPool/actions/workflows/workflow.yml)
[![codecov](https://codecov.io/gh/amorniroli/memPool/branch/master/graph/badge.svg)](https://codecov.io/gh/amorniroli/memPool/tree/master)


Static memory pool util.

# Features
- static allocation (no use of malloc);
- extra configuration file to enable features such as custom assert;
- generic type supported;
- misra compliant (cppcheck);
## Usage
The module must be configured by supplying a project specific `memPool_conf.h`. `memPool_confTemplate.h` can be copied from `template` folder, renamed and modified to supply compile time options.
#### Example
```c
#include <stdint.h>

#include "memPool.h"

#define SLOTS 3U

typedef struct
{
    void* ptr;
    int   dummy;
} test_t;

int
main (void)
{
    test_t           storage[SLOTS];
    memPool_handle_t pool;
    test_t*          ptrSlot;

    memPool_init (&pool, ((uint8_t*) storage), sizeof(test_t), SLOTS);

    memPool_alloc (&pool, ((uint8_t**) &ptrSlot));

    memPool_free(&pool, ((uint8_t*) ptrSlot));

    return 0;
}