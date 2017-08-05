/*
The extended Euclidean algorithm is an extension to the Euclidean algorithm, 
which computes, besides the greatest common divisor of integers a and b, the 
coefficients of Bézout's identity, that is integers x and y such that 
	a * x + b * y = gcd(a,b).
https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
*/

// return gcd(a ,b)
// recursive version
int extended_gcd(int a, int b, int &x, int &y)
{
	// basic case
	if(0 == b)
	{
		x = 1;
		y = 0;
		return a;
	}

	// recursive
	int r = extended_gcd(b, a % b, x, y);
	int t = y;
	y = x - (a / b) * y;
	x = t;
	return r;
}

// The standard Euclidean algorithm (non-recursive)
int extended_gcd(int a, int b, int &x, int &y)
{
	x = 1;
	y = 0;

	if(0 == b)
		return a;

	int new_x = 0;
	int new_y = 1;
	int new_r = b; 
	int r = a;
	int quotient, tmp;
	while(new_r)
	{
		quotient = r / new_r;

		tmp = r;
		r = new_r;
		new_r = tmp - quotient * new_r;

		tmp = x;
		x = new_x;
		new_x = tmp - quotient * new_x;

		tmp = y;
		y = new_y;
		new_y = tmp - quotient * new_y;
	}
	return r;
}

// Applications

/*
1. Computing modular inverse
   If a and n are relatively prime, there exist integers x and y such that 
   a * x + n * y = 1, and such integers may be found using the Euclidean algorithm.
   Considering this equation modulo n, it follows that a * x = 1; i.e., x = a^(-1)(mod n).
*/

int modular_inverse(int a, int n)
{
	int x, y;
	int r = extended_gcd(a, n, x, y);
	if(r > 1)
	{
		printf("a is not invertible\n");
		return -1;
	}
	// If a and b are both positive, we have
	// |x| < b / gcd(a, b) and |y| < a / gcd(a, b)
	return x < 0 ? x + n : x;
}

/*
2. Solving a linear Diophantine equation ax + by = c,
   for a, b and c are known, solve x and y.
*/

bool linear_Diophantine_equation(int a, int b, int &x, int &y)
{
	int d = extended_gcd(a, b, x, y);
	if(c % d)
		return false;
	int k = c / d;
	x *= k;
	y *= k;    // get one of the solutions
	return true;
}

/*
3. Solving a linear congruence equation a * x = b (mod n).
   It is solvable iff the congruence b = 0 (mod d) with
   d = gcd(a, n) is solvable. 
   In that case, if we find x0 that satisfies this congruence,
   then all the solutions can be formed from {x0 + k * n / d | k ∈ Z},
   where d = gcd(a, n). There are exactly d solutions in the complete 
   residue system modulo n, namely {0, 1, ..., n - 1}.
*/

bool linear_congruence_equation(int a, int b, int n)
{
	int x, y;
	int d = extended_gcd(a, n, x, y);
	if(b % d) // no solutions
		return false;
	int x0 = x * (b / d) % n; // particular solution
	for(int i = 1; i < d; ++i)
	{
		printf( "%d\n", ( x0 + i * (n / d) ) % n );
	}
	return true;
}