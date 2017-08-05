int prime[MAXN + 1];
bool comp[MAXN + 1];
void getprime()
{
    for(int p = 2; p <= MAXN; p++)
    {
        if(!comp[p])
        {
            for(int i = p + p; i <= MAXN; i += p)
                comp[i] = 1;
            prime[++prime[0]] = p;
        }
    }
    return;
}