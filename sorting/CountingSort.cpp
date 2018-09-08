// Counting sort
// variables:
//    input -- the array of items to be sorted; Generally, key(x) returns the key for item x(in here just input[i])
//    n -- the length of the input
//    RANGE -- a number such that all keys are in the range 0..RANGE - 1
//    counting -- an array of numbers, with indexes 0..RANGE, initially all zero
//    output -- an array of items, with indexes 0..n-1
// The time for the algorithm: O(n + RANGE)
// The space usage of the algorithm is also O(n + RANGE)

void countingSort(DataType *input)
{
    // The output character array that will have sorted input
    DataType* output = new DataType[n];
    // Create a counting array to store count of individual characters and
    // initialize counting array as 0
    int counting[RANGE] = {};

    // Store count of each character
    for(int i = 0; i < n; i++)
        counting[input[i]]++;

    // Change counting[i] so that counting[i] now contains actual position of
    // this character in output array
    int total = 0, oldCount;
    for (int i = 0; i < RANGE; i++)
    {
        oldCount = counting[i];
        counting[i] = total;
        total += oldCount;
    }
    // Build the output character array
    for (int i = 0; i < n; i++)
		// copy to output array, preserving order of inputs with equal keys:
        output[counting[input[i]]++] = input[i];
		
	/*another version to get the result
	 for (int i = 1; i < RANGE; i++)
        counting[i] += counting[i - 1];
    // Build the output character array
    for (int i = n - 1; i >= 0; i--)
		// copy to output array, preserving order of inputs with equal keys:
        output[--counting[input[i]]] = input[i];
	*/
    for (int i = 0; i < n; i++)
        input[i] = output[i];
	return;
}