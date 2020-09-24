#include <math.h>
#include <stdlib.h>
#include <algorithm>
/* The selection algorithms to find the kth smallest element in an unordered
 * list */

// Quickselect (aka Hoare's selection algorithm)
// Average complexity: O(n), with a worst case of O(n^2)
int partition(int list[], int left, int right, int pivotIndex) {
    int pivotValue = list[pivotIndex];
    std::swap(list[pivotIndex], list[right]);
    int storeIndex = left;
    for (int i = left; i < right; i += 1) {
        if (list[i] < pivotValue) {
            std::swap(list[storeIndex], list[i]);
            storeIndex += 1;
        }
    }
    std::swap(list[right], list[storeIndex]);
    return storeIndex;
}

int select(int list[], int left, int right, int k) {  // k >= left && k <= right
    if (left == right) {
        return list[left];
    }
    // select a pivotIndex between left and right
    int pivotIndex = left + rand() % (right - left + 1);
    pivotIndex = partition(list, left, right, pivotIndex);
    if (k == pivotIndex) return list[k];
    if (k < pivotIndex) return select(list, left, pivotIndex - 1, k);
    return select(list, pivotIndex + 1, right, k);
}

// Median-of-medians (BFPRT)
// The median-of-medians algorithm solves the problem deterministically in O(n)
// time. The constant value for the median-of-medians algorithm is pretty high,
// however.
int select(int list[], int left, int right, int n);

int partition5(int list[], int left, int right) {
    std::sort(list + left, list + right + 1);
    return (left + right) / 2;
}

int pivot(int list[], int left, int right) {
    // for 5 or less elements just get median
    if (right - left < 5) {
        return partition5(list, left, right);
    }
    // otherwise move the medians of five-element subgroups to the first n/5
    // positions
    for (int i = left; i <= right; i += 5) {
        int subRight = i + 4;
        if (subRight > right) {
            subRight = right;
        }
        // get the median of the i'th five-element subgroup
        int median5 = partition5(list, i, subRight);
        std::swap(list[median5], list[left + (i - left) / 5]);
        // compute the median of the n/5 medians-of-five
        return select(list, left, left + (right - left + 4) / 5 - 1,
                      left + (right - left) / 10);
    }
}

int select(
    int list[], int left, int right,
    int k) {  // 注意:该函数和Quickselect中的select不一样,返回的是index,而不是list[index]
    while (true) {
        if (left == right) {
            return left;
        }
        int pivotIndex = pivot(list, left, right);
        pivotIndex =
            partition(list, left, right, pivotIndex);  // same as Quickselect
        if (k == pivotIndex) return k;
        if (k < pivotIndex)
            right = pivotIndex - 1;
        else
            left = pivotIndex + 1;
    }
}

/*
Other algorithms:
1. introselect (short for "introspective selection") is a selection algorithm
that is a hybrid of quickselect and median of medians which has fast average
performance and optimal worst-case performance.
2. Soft heap select. This selection algorithm involves inserting and deleting
elements from a soft heap and runs deterministically in Θ(n) time.
3. Min/Max heap.
http://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/*/
