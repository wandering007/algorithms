//Bucket/Bin sort	

// Function to sort arr[] of size n using bucket sort, index from 0 to n - 1
// a number such that all keys are in the range 0..Range - 1
void bucketSort(DataType arr[], int Range)
{
    // 1) Create Range empty buckets
	vector< vector< DataType > > b;
    b.resize(Range);
    //vector<DataType> b[Range];
   
    // 2) Put array elements in different buckets
    for (int i=0; i < n; i++)
    {
	   // Index in bucket
       int bi = bucketIndex(arr[i], Range); 
	   // if DataType is Integer, a common one is: value * NUMBER_OF_ELEMENTS / (MAXIMUM_ARRAY_VALUE + 1)
	   // if DataType is float and MAXIMUM_ARRAY_VALUE < 1, a common one is: Range * value
       b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < Range; i++)
       sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < Range; i++)
        for (unsigned int j = 0; j < b[i].size(); j++)
          arr[index++] = b[i][j];
}
 
//A more concrete version
struct node
{
	float data;
	struct node *next;
};
 
//sorting Linked List by changing links
void insertionSortInLinkedList(struct node **q,float num){
	struct node *insertNode = (struct node*)malloc(sizeof(struct node));
	insertNode->data = num;
	struct node *temp = *q;        
	//if its the first node
	if (NULL == *q)
	{
		*q = insertNode;
		(*q)->next = NULL;
	//if the new node is to be inserted before the first node
	}
	else if (num < temp->data)
	{
		*q = insertNode;
		(*q)->next = temp;
	//traverse the entire linked list to find the correct point of insertion
	}
	else
	{
		while(temp != NULL)
		{
			if(temp->data <= num && (temp->next == NULL || num <= temp->next->data))
			{
				insertNode->next = temp->next;
				temp->next = insertNode;
				return;
			}
			temp = temp->next;
		}
	}
}

void bucketSort(float arr[],int Range)
{
	struct node *p[Range];
	//initialise by empty buckets
	for(int i = 0;i < Range; i++)
		p[i] = NULL;
	//put array elements in Range different buckets
	for(int i = 0;i < n; i++)
	{
		//calculating the index of insertion into the bucket array
		int bucketIndex = Range * arr[i];
		insertionSortInLinkedList(&p[bucketIndex], arr[i]);
	}
 
	//since all individual buckets are sorted,just concatenate
	int index = 0;
	for(int i = 0;i < Range;i++)
		for (node *q = p[i]; q != NULL; q = q->next)
			arr[index++] = p[i]->data;
}
