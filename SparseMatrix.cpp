//表示稀疏矩阵
typedef struct
{
    int col;
    int row;
    int value;
} term;
term a[30],b[30],d[30];
//稀疏矩阵的快速转置
void fastTranspose(term a[], term b[])
{
    //the transpose of a is placed in b
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;
    if(numTerms > 0) //nonzero matrix
    {
        for(i = 0; i<numTerms; i++)
            rowTerms[i] = 0;
        for(i = 1; i<=numTerms; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;
        for(i = 1; i<=numCols; i++)
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];
        for(i = 1; i<=numTerms; i++)
        {
            j = startingPos[a[i].col]++;//startingPos[a[i].col]++为了下次查询a的该列时j增加了1
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

//稀疏矩阵相乘
//storeSum function
void storeSum(term d[], int *totalD, int row, int col, int *sum)
{
    //if *sum != 0, then it along with its row and col. postion is stored as the *totalD+1 entry in d
    if(*sum)
    {
        if(*totalD<MAX_TERMS)
        {
            (*totalD)++;
            d[*totalD].row = row;
            d[*totalD].col = col;
            d[*totalD].value = *sum;
            *sum = 0;
        }
        else
        {
            fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
            exit(EXIT_FAILURE);
        }
    }
    return;
}
//mmult function
void mmult(term a[], term b[], term d[])
{
    //multiply two sparse matrics
    int i, j, col, totalB = b[0].value, totalD = 0;
    int rowsA = a[0].row, colsA = a[0].col;
    int colsB = b[0].col, totalA = a[0].value;
    int row = a[1].row, sum = 0, rowBegin = 1;
    if(colsA != b[0].row)
    {
        fprintf(stderr, "Incompatible matrices\n");
        exit(EXIT_FAILURE);
    }
    term newB[MAX_TERMS];
    fastTranspose(b, newB);
    //set boundary condition
    a[totalA + 1].row = 0;
    newB[totalB + 1].row = 0;
    newB[totalB + 1].col = 0;
    for(i = 1; i <= totalA; )
    {
        col = newB[1].row;
        for(j = 1; j <= totalB+1; )
        {
            //multiply row of a by col of b
            if(a[i].row != row)
            {
                storeSum(d, &totalD, row, col, &sum);
                i = rowBegin;
                for(; newB[j].row == col; j++)
                  {;}
                if(j>totalB)
                    break;
                col = newB[j].row;
            }
            else if(newB[j].row != col)
            {
                storeSum(d, &totalD, row, col, &sum);
                if(j>totalB)
                    break;
                i = rowBegin;
                col = newB[j].row;
            }
            else
                switch(COMPARE(a[i].col, newB[j].col))
                {
                case -1: //go to next term in a
                    i++;
                    break;
                case 0: //add terms, go to next term in a and b
                    sum += (a[i++].value*newB[j++].value);
                    break;
                case 1: //advance to next term in b
                    j++;
                }
        }//end of for j<=totalB
        for(; a[i].row == row; i++)
          {;}
        rowBegin = i;
        row = a[i].row;
    }//end of for i<=totalA
    d[0].row = rowsA;
    d[0].col = colsB;
    d[0].value = totalD;
}