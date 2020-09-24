/*Euclidean algorithm by subtraction, 更相减损术, O(x + y)*/
int gcd(int x, int y) {
    if (x == y) return x;

    if (x > y) return gcd(x - y, y);

    return gcd(x, y - x);
}

/*Euclidean algorithm by division, 辗转相除法, O( log(x + y) )*/
// assumed that a > b,  or a comparison would be needed.
int gcd(int a, int b) {
    // a = a % b, b = b ^ a, a = a ^ b, b = b ^ a;(swap a and b)
    while (b ^= a ^= b ^= a %= b)
        ;
    return a;
}

int gcd(int a, int b) { return (b > 0) ? gcd(b, a % b) : a; }

int gcd(int a, int b) {  //比较容易理解的一种写法
    int r;
    while (b > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/*
Binary Euclidean algorithm, divide and conquer, O( log(x + y) )
For very large integers, O( ( log(x + y) ) ^ 2 )
*/
int gcd(int x, int y) {
    if (x == y) return x;
    // both are even
    if (0 == x & 1 && 0 == y & 1) return gcd(x >> 1, y >> 1) << 1;
    // x is even, y is odd
    if (0 == x & 1) return gcd(x >> 1, y);
    // y is even, x is odd
    if (0 == y & 1) return gcd(x, y >> 1);

    // both are odd
    if (x > y) return gcd(x - y, y);

    return gcd(x, y - x);
}

/*
Extension:
least common multiple (lcm)
lcm(x, y) = x * y / gcd(x, y)
*/
