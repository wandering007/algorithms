//quick sort is unstable

typedef struct
{
    DataType key;
}node;
typedef struct
{
    node r[MAXN + 1];
    int length;
} SqList;

//return the index whose key is in the middle.
int midKey(int a, int b, int c, node *r)
{
    node temp;
    if(r[a].key > r[b].key)
    {
        temp = r[a];
        r[a] = r[b];
        r[b] = temp;
    }
    if(r[b].key > r[c].key)
    {
        if(r[a].key > r[c].key)
            return a;
        return c;
    }
    return b;
}

int Partition(SqList &L,int low,int high,bool* TagLow,bool* TagHigh)
{
    int mid = midKey(low, high, (low + high) / 2, L.r);//取三者中关键字为中值的记录为枢轴
    L.r[0] = L.r[mid];
    DataType pivotkey = L.r[mid].key;
    L.r[mid] = L.r[low];//交换记录，将r[low]的值保留下来
    node temp;
    while(low < high)
    {
        while(low < high && L.r[high].key >= pivotkey)
        {
            if(high < L.length && L.r[high].key > L.r[high + 1].key)
            {
                temp = L.r[high];
                L.r[high] = L.r[high + 1];
                L.r[high + 1] = temp;
                *TagHigh = true;
            }
            high--;
        }
        if(low < high)
            L.r[low] = L.r[high];    //将比枢轴记录小的记录移到低端
        while(low < high && L.r[low].key <= pivotkey)
        {
            if(low > 1 && L.r[low-1].key > L.r[low].key)
            {
                temp = L.r[low];
                L.r[low] = L.r[low - 1];
                L.r[low - 1] = temp;
                *TagLow = true;
            }
            low++;
        }
        if(low < high)
            L.r[high] = L.r[low];  //将比枢轴记录大的记录移到高端
    }
    L.r[low] = L.r[0];//枢轴记录到位
    return low;//返回枢轴位置
}//Partition

//divide-and-conquer
void QSort(SqList &L, int low, int high)
{
    if(low < high)//长度大于1
    {
        bool TagLow = false, TagHigh = false;
        int pivotloc = Partition(L, low, high, &TagLow, &TagHigh);//将L.r[low...high]一分为二,pivotloc是枢轴位置
        if(TagLow==true)
            QSort(L, low, pivotloc-1);//对低子表递归排序
        if(TagHigh==true)
            QSort(L, pivotloc + 1, high);//对高子表递归排序
    }
    return;
}

void QuickSort(SqList &L)
{
    QSort(L,1,L.length);
    return;
}