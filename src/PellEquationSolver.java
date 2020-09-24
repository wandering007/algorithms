import java.math.*;
//Reference: https://proofwiki.org/wiki/Pell%27s_Equation#Proof
//x^2 - D * y^2 = 1, fundamental solution
public static final BigInteger zero = new BigInteger("0");
public static final BigInteger one = new BigInteger("1");
public static final double eps = 1e-6;
public class PellEquationSolver
{
	public BigInteger FundSol(int D) {
		int a0 = (int)(Math.sqrt(D) + eps);
		if(a0 * a0 == D)
			return zero;
		BigInteger p0 = one, p1 = new BigInteger(a0 + "");
		BigInteger q0 = zero, q1 = one, tmp;
		int k = a0, a = a0, t = 1, period = 0, c;
		while(true)
		{//此处仍有优化的可能
			period++;
			c = D - k * k;
			t = c / t;
			a = (int)((Math.sqrt(D) + k) / (t * 1.0) + eps);//a为整数部分
			k = a * t - k;
			if(k == a0 && 1 == t && 0 == (period & 1))
				break;
			tmp = p1;
			p1 = p0.add(p1.multiply(new BigInteger(a + "")));
			p0 = tmp;
			tmp = q1;
			q1 = q0.add(q1.multiply(new BigInteger(a + "")));
			q0 = tmp;
		}
		return p1;
	}
}
