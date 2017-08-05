# Longest increasing subsequence
# Time complexity: O(n log n), where n denotes the length of the input sequence
# Ref: https://rosettacode.org/wiki/Longest_increasing_subsequence#Python:_O.28nlogn.29_Method_from_Wikipedia.27s_LIS_Article.5B1.5D
# Related to Patience sort
def longest_increasing_subsequence(X):
    N = len(X)
    P = [0] * N
    M = [0] * (N + 1)
    L = 0
    for i in range(N):
    # Binary search for the largest positive j <= L
        lo = 1
        hi = L
        while lo <= hi:
            mid = (lo + hi) // 2
            if X[ M[mid] ] < X[i]:
                lo = mid + 1
            else:
                hi = mid - 1
        # After searching, lo is 1 greater than the length of the longest prefix of X[i]
        newL = lo

        # The predecessor of X[i] is the last index of the subsequence of length newL - 1
        P[i] = M[newL - 1]
        M[newL] = i

        if(newL > L):
            # If we found a subsequence longer than any we've found yet, update L
            L = newL
    # Reconstruct the longest increasing subsequence
    S = []
    k = M[L]
    for i in range(L - 1, -1, -1):
        S.append(X[k])
        k = P[k]
    return S[::-1]