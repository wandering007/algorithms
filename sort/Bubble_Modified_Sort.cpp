//bubble sort is stable
void Bubble_Modified_Sort(DataType R[], int n)
{
	int i = n, LastExchangeIndex;
	while(i > 1)
	{
	 LastExchangeIndex = 1;
	 for(int j = 1; j < i; j++)
	 {
	 	if(R[j].key > R[j + 1].key)
	 	{
	 		R[0] = R[j + 1];
	 		R[j + 1] = R[j];
	 		R[j] = R[0];
	 		LastExchangeIndex = j;//记录交换的位置
	 	}
	 }
	 i = LastExchangeIndex;//本趟进行交换的最后位置
	}
}