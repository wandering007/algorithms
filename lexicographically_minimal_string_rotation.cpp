// The lexicographically minimal string rotation or lexicographically least
// circular substring is the problem of finding the rotation of a string
// possessing the lowest lexicographical order of all such rotations.

#include <string>

int minimum_representation(std::string S) {
    int i = 0, j = 1, n = S.size();
    S += S;
    while (j < n) {
        int k = 0;
        while (j + k < 2 * n && S[i + k] == S[j + k]) ++k;
        if (j + k == 2 * n)
            break;
        else if (S[i + k] > S[j + k])
            i = max(i + k + 1, j), j = i + 1;
        else
            j += k + 1;
    }
    return i;
}
