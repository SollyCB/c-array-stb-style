#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SOL_ARRAY_IMPLEMENTATION
#include "array.h"

typedef struct Thing { int x, y; } Thing;

int main() {

    int cap = 16;
    Thing *array = new_array(cap, Thing);

    Thing thing;
    printf("cap = %i\n", array_cap(array));
    int c = array_cap(array);
    for(int i = 0; i < c + 2; ++i) {
        thing.x = i;
        thing.y = i;
        printf("array_len = %i\n", array_len(array));
        array_add(array, thing);
    }
    printf("new cap = %i\n", array_cap(array));
    c = array_len(array);
    printf("count = %i\n", c);
    for(int i = 0; i < c; ++i)
        printf("thing[%i] = {%i, %i}\n", i, array[i].x, array[i].y);

    free_array(array);
    return 0;
}
