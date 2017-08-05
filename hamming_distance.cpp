int hamming_distance(unsigned x, unsigned y)
{
    int       dist;
    unsigned  val;

    dist = 0;
    val = x ^ y;    // XOR

    // Count the number of bits set
    while (val != 0)
    {
        // A bit is set, so increment the count and clear the bit
        dist++;
        val &= val - 1;
    }

    // Return the number of differing bits
    return dist;
}
//Wegner, Peter (1960), "A technique for counting ones in a binary computer"