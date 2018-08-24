//A Fenwick BIT or binary indexed tree is a data structure providing efficient methods 
//for calculation and manipulation of the prefix sums of a table of values. 

//1D version
//空间复杂度O(n), 初始化时间复杂度O(n*log n), 查询区间复杂度O(log n)
//n —— maximum value which will have non-zero frequency
//idx is some index of BIT. r is a position in idx of the last digit 1 (from left to right) in binary notation. 
//BIT[idx] is sum of frequencies from index (idx - 2^r + 1) to index idx.
//We also write that idx is responsible for indexes from (idx - 2^r + 1) to idx.

//Sample C Implementation

int lowbit(int x)
{
    return x & (-x);
}

void update(int i, int delta)
{
	while(i <= MaxVal) // MaxVal —— maximum value which will have non-zero frequency
	{
		BIT[i] += delta;
		i += lowbit(i);
	}
    return;
}

int query(int k)
{
    int ans = 0;
    while (k > 0) {
        ans += BIT[k];
        k -= lowbit(k);
    }
    return ans;
}

// the actual frequency at a position idx can be calculated by calling function qeury twice
//f[idx] = query(idx) - query(idx - 1), but the function below is faster
int querySingle(int idx)
{
	int sum = BIT[idx]; // sum will be decreased
	if (idx > 0)
	{ // special case
		int z = idx - lowbit(idx); // make z first
		--idx;
		while (idx != z) {
			sum -= BIT[idx]; 
		  // substruct BIT frequency which is between y and "the same path"
			idx -= lowbit(idx);
		} // finally idx will become z
	}
	return sum;
}

//Scaling the entire BIT by a constant factor c
void scale(int c) //c is maybe not an integer
{
    for (int i = 1 ; i <= MaxVal; i++)
			BIT[i] *= c;
    // here we assume that c is used to multiply the original frenquency(maybe
    // divide)
    return;
}

//Find index with given cumulative frequency

// if in BIT exists more than one index with a same
// cumulative frequency, this procedure will return 
// some of them (we do not know which one)

// bitMask - initialy, it is the greatest bit of MaxVal
// bitMask store interval which should be searched
int find(int cumFre)
{
	int idx = 0; // this var is result of function
	
	while ((bitMask != 0) && (idx < MaxVal))
	{ // nobody likes overflow :)
		int tIdx = idx + bitMask; // we make midpoint of interval
		if (cumFre == BIT[tIdx]) // if it is equal, we just return idx
			return tIdx;
		else if (cumFre > BIT[tIdx])
		{ // if BIT frequency "can fit" into cumFre, then include it
			idx = tIdx; // update index 
			cumFre -= BIT[tIdx]; // set frequency for next loop 
		}
		bitMask >>= 1; // half current interval
	}
	if (cumFre != 0) // maybe given cumulative frequency doesn't exist
		return -1;
	else
		return idx;
}
// if in BIT exists more than one index with a same
// cumulative frequency, this procedure will return 
// the greatest one
int findG(int cumFre){
	int idx = 0;
	
	while ((bitMask != 0) && (idx < MaxVal)){
		int tIdx = idx + bitMask;
		if (cumFre >= BIT[tIdx])
		{// if current cumulative frequency is equal to cumFre, 
		 // we are still looking for higher index (if exists)
			idx = tIdx;
			cumFre -= BIT[tIdx];
		}
		bitMask >>= 1;
	}
	if (cumFre != 0)
		return -1;
	else
		return idx;
}
//Time complexity: O(log MaxVal)

//Sample C++ Implementation(a bit different idea)

class Fenwick_BIT_Sum
{
    vector< int > BIT;
    Fenwick_BIT_Sum(const vector< int >& Arg)//Arg is our array on which we are going to work
    {
        BIT.resize(Arg.size());
        for(int i = 0 ; i < BIT.size(); ++i)
            increase(i, Arg[i]);
    }
 
    // Increases value of i-th element by ''delta''.
    void increase(int i, int delta)
    {
        for (; i < (int)BIT.size(); i |= i + 1)
            BIT[i] += delta;
    }
 
    // Returns sum of elements with indexes left..right, inclusive; (zero-based);
    int getsum(int left, int right)
    {
        return sum(right) - sum(left - 1); //when left equals 0 the function hopefully returns 0
    }
 
    int sum(int ind)
    {
        int sum = 0;
        while (ind >= 0)
        {
            sum += BIT[ind];
            ind &= ind + 1;
            --ind;
        }
        return sum;
    }
};

//2D version

int lowbit(int t)
{  
    return t & (-t);
}  

void update(int i, int j, int delta)
{
    A[i][j] += delta;
    for(int x = i; x <= MaxVal_X; x += lowbit(x))
        for(int y = j; y <= MaxVal_Y; y += lowbit(y))
          BIT[x][y] += delta;
    return;
}

int query(int i, int j)
{
    int result = 0;
    for(int x = i; x > 0; x -= lowbit(x)) 
        for(int y = j; y > 0; y -= lowbit(y)) 
           result += BIT[x][y];
    return result;
}

//多维树状数组与一维二维树状数组实现很相似，只是在查询区间时注意容斥原理的使用
