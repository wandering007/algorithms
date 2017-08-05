DataType ModularPow(DataType x, int n, DataType modulus)
{
    DataType res;
	init(res);//初始化，零次方时的值
    if (0 == n)
        return res;//对于矩阵快速幂返回单位矩阵
    while (n)
    {
        if (n & 1)
            res = Mod(multiply(res, x), modulus);
        x = Mod(multiply(x, x), modulus);
        n >>= 1;
    }
    return res;
}//时间复杂度O(log n)
//本算法用来高效计算数据的高次方的，至于数据的类型没有太多的限制，诸如：整型、浮点型、矩阵等等，都是可以解决的。