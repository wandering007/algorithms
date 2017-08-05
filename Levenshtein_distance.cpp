#include <algorithm>
#include <vector>
// If the strings are the same size, the Hamming distance is an upper bound on the Levenshtein distance.
// The Levenshtein distance between two strings is no greater than the sum of their Levenshtein distances from a third string (triangle inequality).
int levDistance(const std::string &a, const std::string &b)
{
	int r = a.size();
	int c = b.size();
	if (0 == r)
		return c;
	if (0 == c)
		return r;
	// initialize 2d array to zeros
	std::vector< std::vector<int> > lev(r + 1, std::vector<int>(c + 1, 0));

	for (int i = 0; i <= r; i += 1)
	{
		for (int j = 0; j <= c; j += 1)
		{
			if (0 == std::min(i, j))
			{
				lev[i][j] = std::max(i, j);
				continue;
			}
			lev[i][j] = std::min(lev[i - 1][j] + 1,
				std::min(lev[i][j - 1] + 1, lev[i - 1][j - 1] + (a[i - 1] != b[j - 1])));
		}
	}
	return lev[r][c];
}