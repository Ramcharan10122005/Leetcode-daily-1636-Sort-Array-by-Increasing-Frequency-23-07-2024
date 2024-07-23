#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int frequency;
} Element;

int compare(const void* a, const void* b) {
    Element* elem1 = (Element*)a;
    Element* elem2 = (Element*)b;

    if (elem1->frequency == elem2->frequency) {
        return elem2->value - elem1->value;
    }
    return elem1->frequency - elem2->frequency;
}

int* frequencySort(int* nums, int numsSize, int* returnSize) {
    int minElem = INT_MAX, maxElem = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxElem) maxElem = nums[i];
        if (nums[i] < minElem) minElem = nums[i];
    }

    int range = maxElem - minElem + 1;
    Element* frequency = (Element*)calloc(range, sizeof(Element));
    if (frequency == NULL) {
        return NULL;
    }

    for (int i = 0; i < range; i++) {
        frequency[i].value = i + minElem;
        frequency[i].frequency = 0;
    }

    for (int i = 0; i < numsSize; i++) {
        frequency[nums[i] - minElem].frequency++;
    }

    qsort(frequency, range, sizeof(Element), compare);

    int* result = (int*)malloc(numsSize * sizeof(int));
    if (result == NULL) {
        free(frequency);
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < frequency[i].frequency; j++) {
            result[index++] = frequency[i].value;
        }
    }

    free(frequency);
    *returnSize = numsSize;

    return result;
}
