#include <algorithm>
#include <iostream>

//	heap sort is unstable
//	adjust the binary tree to establish the heap
void adjust(element a[], int root, int n) {
    int child, rootkey;
    a[0] = a[root];
    rootkey = a[root].key;
    child = 2 * root;
    while (child <= n) {
        if (child < n && a[child].key < a[child + 1].key) ++child;
        if (rootkey > a[child].key)  // compare root and max child
            break;                   //	筛选完成
        a[child / 2] = a[child];
        child *= 2;
    }
    a[child / 2] = a[0];
}
void HeapSort(element a[], int n) {  //	perform a  heap sort on a[1 : n]
    for (int i = n / 2; i > 0; --i) adjust(a, i, n);  //	n * log n
#if 1
    for (int i = n; i > 1; --i) {
        std::cout << a[1].key
                  << "\t";  //	print sorted sequence from max to min
        std::swap(a[1], a[i]);
        adjust(a, 1, i - 1);  // log n
    }
    std::cout << a[1].key << "\n";
#endif
}
