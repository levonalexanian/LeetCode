#include <assert.h>
#include <stdlib.h>

#include "solution.c"

static void check(int* nums, int n, int target, int a, int b) {
    int size;
    int* got = twoSum(nums, n, target, &size);
    assert(size == 2);
    assert(got[0] == a && got[1] == b);
    free(got);
}

int main(void) {
    check((int[]){2, 7, 11, 15}, 4, 9, 0, 1);
    check((int[]){3, 2, 4}, 3, 6, 1, 2);
    check((int[]){3, 3}, 2, 6, 0, 1);
    check((int[]){-3, 4, 3, 90}, 4, 0, 0, 2);
    check((int[]){1000000000, 7, -1000000000}, 3, 0, 0, 2);
    return 0;
}
