//Insertion sort is stable, in-place, online
//Time complexity: O(n^2)
//Space complexity: O(n) total, O(1) auxiliary
for(int i = 1; i < length(A); i++)
{
	int j = i;
	while(j > 0 && A[j - 1] > A[j])
	{
		swap(A[j], A[j - 1]);
		j--;
	}
	/*another implementation
	DataType x = A[i];
	int j = i;
	while(j > 0 && A[j - 1] > x)
	{
		A[j] = A[j - 1];
		j--;
	}
	A[j] = x;
	*/
}

//List insertion sort code in C
struct LIST * SortList1(struct LIST * pList)
{
    // zero or one element in list
    if(pList == NULL || pList->pNext == NULL)
        return pList;
    // head is the first element of resulting sorted list
    struct LIST * head = NULL;
    while(pList != NULL) {
        struct LIST * current = pList;
        pList = pList->pNext;
        if(head == NULL || current->iValue < head->iValue) 
		{
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            current->pNext = head;
            head = current;
        } else {
            // insert current element into proper position in non-empty sorted list
            struct LIST * p = head;
            while(p != NULL) {
                if(p->pNext == NULL || // last element of the sorted list
                   current->iValue < p->pNext->iValue) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    current->pNext = p->pNext;
                    p->pNext = current;
                    break; // done
                }
                p = p->pNext;
            }
        }
    }
    return head;
}
//The algorithm below uses a trailing pointer for the insertion into the sorted list.
//A simpler recursive method rebuilds the list each time (rather than splicing) and can use O(n) stack space.
struct LIST
{
  struct LIST * pNext;
  int           iValue;
};
 
struct LIST * SortList(struct LIST * pList)
{
  // zero or one element in list
  if(!pList || !pList->pNext)
      return pList;
 
  /* build up the sorted array from the empty list */
  struct LIST * pSorted = NULL;
 
  /* take items off the input list one by one until empty */
  while (pList != NULL)
  {
      /* remember the head */
      struct LIST *   pHead  = pList;
      /* trailing pointer for efficient splice */
      struct LIST ** ppTrail = &pSorted;
 
      /* pop head off list */
      pList = pList->pNext;
 
      /* splice head into sorted list at proper place */
      while (!(*ppTrail == NULL || pHead->iValue < (*ppTrail)->iValue)) /* does head belong here? */
      {
          /* no - continue down the list */
          ppTrail = &(*ppTrail)->pNext;
      }
 
      pHead->pNext = *ppTrail;
      *ppTrail = pHead;
  }
 
  return pSorted;
}