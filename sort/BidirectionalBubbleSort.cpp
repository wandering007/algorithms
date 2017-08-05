//bubble sort is stable
void Bidirectional_Bubble_Sort(DataType R[], int n)//cocktailSort
{
	int begin = 0, end = n;
	do
	{
		bool swapped = false;
		begin++;
		for(int i=begin;i<end;i++)
		{
			if(R[i].key>R[i+1].key)
			{
				R[0] = R[i+1];
		 		R[i+1] = R[i];
		 		R[i] = R[0];
		 		swapped = true;
			}
			if(swapped==false)break;
		}
		swapped = false;
		end--;
		for(int i=end; i>begin; i--)
		{
			if(R[i-1]>R[i])
			{
				R[0] = R[i];
		 		R[i] = R[i-1];
		 		R[i-1] = R[0];
		 		swapped = true;
			}
		}
	}
	while(swapped);
	return;
}