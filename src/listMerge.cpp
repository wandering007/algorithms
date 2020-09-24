//Something definitely wrong!!!!!!!!!!自己写一个
int rmergeSort(element a[], int link[], int right)
{/*a[left:right] is to be sorted, link[i] is initially 0
	for all i, returns the index of the first element in
	the sorted chain*/
 if(left>=right) return left;
 int mid = (left+right)/2;
 return listMerge(a, link, 
 				  //sort left half
 				  rmergeSort(a,link,left,mid),
 				  //sort right half
 				  rmergeSort(a, link, mid+1, right));
}//递归归并排序

int listMerge(element a[], int link[], int start1, int start2)
{/*sorted chains beginning at start1 and start2,respectively,
 are merged; link[0] is used as a temporary header;returns start
 of merge chain*/
 int last1, last2, lastResult = 0;
 if(a[last1]<=a[last2])
 {
 	link[lastResult] = last1;
 	lastResult = last1;
 	last1 = link[last1];
 }
 else 
 {
 	link[lastResult] = last2;
 	lastResult = last2;
 	last2= link[lastResult];
 }
 //attach remaining records to result chain
 else link[lastResult] = last1;
 return link[0];
}//归并有序链表
