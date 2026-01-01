
The following is a simple implementation of a defer mechanism for
the C programming language, allowing for automatic code execution
at the end of a predefined scope. This helps with resources
management, and prevents memory related issues.

To use the defer module in your codebase just include the header:

```c
#include "defer.h"

...
```

Example usage:

```c
#include <stdio.h>

#include "defer.h"

int main() {
    scope({
        printf("A\n");

        defer({
            printf("B\n");
        });

        printf("C\n");
    });

    return 0;
}
```

Output:

```
A
C
B
```

Note: This implementation expects the predefined scope to finish
its execution. If at any point in time code is stopped before the
end of the scoped (i.e. return from a function), the previously
deferred block will not be invoked, which may lead to issues.
