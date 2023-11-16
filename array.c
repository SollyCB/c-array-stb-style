#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void* fn_new_array(int cap, int width) {
    printf("cap * width = %u\n", width * cap + 16);
    int *ret = malloc(cap * width + 16);
    ret[0] = width * cap;
    ret[1] = 0;
    ret[2] = width;
    ret += 4;
    return (void*)ret;
}
void* fn_realloc_array(int *array) {
    printf("count * width = %i\n" , array[1] * array[2]);
    if (array[0] > array[1] * array[2])
        return array + 4;
    array = realloc(array, array[0] * 2 + 16);
    assert(array);
    array[0] *= 2;
    printf("reallocd cap = %i\n", array[0]);
    array += 4;
    return array;
}

#define new_array(cap, type) fn_new_array(cap, sizeof(type))
#define free_array(array) free((int*)array - 4)

#define array_cap(array)   (((int*)array)[-4] / ((int*)array)[-2])
#define array_count(array) ((int*)array)[-3]
#define array_inc(array)   ((int*)array)[-3]++
#define array_dec(array)   ((int*)array)[-3]--

#define array_add(array, elem) array = fn_realloc_array((int*)array - 4); array[array_count(array)] = elem; array_inc(array)
#define array_pop(array) if (array_count(array) != 0) array_dec(array) else false

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
        printf("array_count = %i\n", array_count(array));
        array_add(array, thing);
    }
    printf("new cap = %i\n", array_cap(array));
    c = array_count(array);
    printf("count = %i\n", c);
    for(int i = 0; i < c; ++i)
        printf("thing[%i] = {%i, %i}\n", i, array[i].x, array[i].y);

    free_array(array);
    return 0;
}
