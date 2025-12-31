#include <stdio.h>
#include <stdlib.h>

#include "defer.h"

void display() {
    scope({
        printf("A\n");

        defer({
            printf("B\n");
        });

        printf("C\n");
    });
}

int main() {
    display();

    int buffer_size = 10;

    scope({
        char *buffer = malloc(buffer_size * sizeof(char));
        defer(free(buffer));

        for (int i = 0; i < buffer_size - 1; i++) {
            *(buffer + i) = 'A' + i;
        }

        *(buffer + buffer_size - 1) = '\0';

        printf("%s\n", buffer);
    });

    printf("Printing outside deferred scope\n");

    return 0;
}
