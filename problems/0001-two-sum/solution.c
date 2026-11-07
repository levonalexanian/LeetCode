// 1. Two Sum (Easy) — https://leetcode.com/problems/two-sum/
//
// Hash map from value to index, filled as we go: for each number, check
// whether its complement was already seen. O(n) time, O(n) space.

#include <stdlib.h>

typedef struct {
    int key;
    int index;
    int used;
} Slot;

static unsigned hash(int key, unsigned mask) {
    return ((unsigned)key * 2654435761u) & mask;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    unsigned cap = 1;
    while (cap < 2u * (unsigned)numsSize) cap <<= 1;
    unsigned mask = cap - 1;
    Slot* table = calloc(cap, sizeof(Slot));
    int* result = malloc(2 * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {
        // Wraps instead of overflowing; a wrapped value can't match anyway.
        int want = (int)((unsigned)target - (unsigned)nums[i]);
        for (unsigned h = hash(want, mask); table[h].used; h = (h + 1) & mask) {
            if (table[h].key == want) {
                result[0] = table[h].index;
                result[1] = i;
                *returnSize = 2;
                free(table);
                return result;
            }
        }
        unsigned h = hash(nums[i], mask);
        while (table[h].used) h = (h + 1) & mask;
        table[h] = (Slot){nums[i], i, 1};
    }
    free(table);
    return result;
}
