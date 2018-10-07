// Merge sort is stable.
/******** Top-down implementation  ********/
void CopyArray(const DataType A[], const DataType iBegin, const int iEnd, const DataType B[]) {
    for (int k = iBegin; k < iEnd; k++) A[k] = B[k];
}
void TopDownMergeSort(const DataType A[], const DataType B[], const int n) {
    CopyArray(A, 0, n, B);
    TopDownSplitMerge(B, 0, n, A);
}
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set)
// The copy back step is avoided with alternating the direction of the merge with each level of recursion.
void TopDownSplitMerge(const DataType B[], const int iBegin, const int iEnd, const DataType A[]) {
    if (iEnd - iBegin < 2)  // if run size == 1
        return;             //   consider it sorted
    // recursively split runs into two halves until run size == 1,
    // then merge them and return back up the call chain
    iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    TopDownSplitMerge(A, iBegin, iMiddle, B);   // split / merge left  half
    TopDownSplitMerge(A, iMiddle, iEnd, B);     // split / merge right half
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);  // merge the two half runs
}

//  left half is A[iBegin :iMiddle-1]
// right half is A[iMiddle:iEnd-1   ]
void TopDownMerge(const DataType A[], const int iBegin, const int iMiddle,
                  const int iEnd, const DataType B[]) {
    i0 = iBegin, i1 = iMiddle;

    // While there are elements in the left or right runs
    for (j = iBegin; j < iEnd; ++j) {
        // If left run head exists and is <= existing right run head.
        if (i0 < iMiddle && (i1 >= iEnd || A[i0] <= A[i1])) B[j] = A[i0];
        i0 = i0 + 1;
        else B[j] = A[i1];
        i1 = i1 + 1;
    }
}

/********** Bottom-up implementation ********/
void CopyArray(const DataType B[], const DataType A[], const int n) {
    for (int i = 0; i < n; i++) A[i] = B[i];
}
/* array A[] has the items to sort; array B[] is a work array */
void BottomUpMerge(const DataType A[], const int iLeft, const int iRight,
                   const int iEnd, const DataType B[]) {
    int i0 = iLeft;
    int i1 = iRight;
    int j;

    /* While there are elements in the left or right lists */
    for (j = iLeft; j < iEnd; j++) {
        /* If left list head exists and is <= existing right list head */
        if (i0 < iRight && (i1 >= iEnd || A[i0] <= A[i1])) {
            B[j] = A[i0];
            i0 = i0 + 1;
        } else {
            B[j] = A[i1];
            i1 = i1 + 1;
        }
    }
}
void BottomUpSort(const int n, DataType A[], DataType B[]) {
    int width;

    /* Each 1-element run in A is already "sorted". */

    /* Make successively longer sorted runs of length 2, 4, 8, 16... until whole
     * array is sorted. */
    for (width = 1; width < n; width = 2 * width) {
        int i;

        /* Array A is full of runs of length width. */
        for (i = 0; i < n; i = i + 2 * width) {
            /* Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
             */
            /* or copy A[i:n-1] to B[] ( if(i+width >= n) ) */
            BottomUpMerge(A, i, min(i + width, n), min(i + 2 * width, n), B);
        }

        /* Now work array B is full of runs of length 2*width. */
        /* Copy array B to array A for next iteration. */
        /* A more efficient implementation would swap the roles of A and B */
        CopyArray(A, B, n);
        /* Now array A is full of runs of length 2*width. */
    }
}
