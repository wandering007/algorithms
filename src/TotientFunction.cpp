/*
In number theory, Euler's totient or phi function, φ(n), is an arithmetic function that counts the 
totatives of n, that is, the positive integers less than or equal to n that are relatively prime to 
n. Thus, if n is a positive integer, then φ(n) is the number of integers k in the range 1 ≤ k ≤ n 
for which gcd(n, k) = 1. 
1) The totient function is a multiplicative function, meaning that if 
two numbers m and n are relatively prime (to each other), then φ(mn) = φ(m)φ(n).
(Sketch of proof: let A, B, C be the sets of residue classes modulo-and-coprime to m, n, mn respectively; 
then there is a bijection between A × B and C, by the Chinese remainder theorem.)
2) If p is prime and k ≥ 1 then
φ(p^k) = p^k -p^{k - 1} =p^{k - 1} * (p - 1) = p^k * ( 1 - 1 / p).
*/
int Phi[MAXN + 1];

void Totient()
{
	for(int i = 1; i <= MAXN; i++)
		Phi[i] = i;
	for(int i = 2; i <= MAXN; i++)
	{
		if(Phi[i] == i)
		{
			for(int j = i; j <= MAXN; j += i)
				Phi[j] = Phi[j] / i * (i - 1); //Euler's product formula
		}
	}//与扫描法求质数方法相同
	return;
}