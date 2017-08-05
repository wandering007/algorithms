const double PI = acos(-1.0);
//复数结构体
struct complex
{
    double r, i;
    complex(double _r = 0.0, double _i = 0.0)
    {
        r = _r;
        i = _i;
    }
    complex operator + (const complex &b)
    {
        return complex(r + b.r, i + b.i);
    }
    complex operator - (const complex &b)
    {
        return complex(r - b.r, i - b.i);
    }
    complex operator * (const complex &b)
    {
        return complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
    complex& operator *= (const complex &b)
    {
        const double temp1 = r, temp2 = b.r; //防止b和左变量是同一变量
        r = r * b.r - i * b.i;
        i = temp1 * b.i + i * temp2;
        return *this;
    }
    complex& operator /= (const double val)
	{
		r /= val;
		i /= val;
		return *this;
	}
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * n必须去2的幂
 */
void BitReverse(complex y[],int n)
{
    int i, j, k;
    for(i = 1, j = n / 2; i < n - 1; ++i)
    {
        if(i < j)
            swap(y[i], y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = n / 2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
		/* compare:
			unsigned int k = n;
			//   While bit is set
			while (j & (k >>= 1))
				//   Drop bit
				j &= ~k;
			//   The current bit is 0 - set it
			j |= k;
		*/
    }
    return;
}
/*
 * 做FFT
 * n必须为2^k形式，
 * inverse == -1时是DFT，inverse == 1时是IDFT
 */
void fft(complex y[], int n, int inverse = -1)
{
    BitReverse(y, n);
    for(int m = 2; m <= n; m <<= 1)
    {
        complex w(1, 0);
        //此处已纠正，intro to algorithm 有误，DFT的旋转因子为e^(-2 * pi * i / n)
        complex wm( cos(2 * PI / m), sin(inverse * 2 * PI / m) ); 
        for(int j = 0; j < m / 2; ++j)
        {
            for(int k = 0; k < n; k += m)
            {
                {
                    complex u = y[k + j];
                    complex t = w * y[k + j + m / 2];
                    y[k + j] = u + t;
                    y[k + j + m / 2] = u - t;
                }
            }
            w = w * wm; //减少了旋转因子的计算次数
        }
    }
    if(1 == inverse)
    {
        for(int i = 0; i < n; ++i)
            y[i] /= (double)n;
    }
    return;
}