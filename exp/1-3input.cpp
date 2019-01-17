 #include <cstdio>

#include <cstdlib>
#include <ctime>
#define MAXN 2003
int n, p1, p2, m;
int f[MAXN], l[MAXN];
/*0:friend 1*/
int find(int x)
{
if (x == f[x])
return x;
int ans = find(f[x]);
l[x] ^= l[f[x]];
f[x] = ans;
return ans;
}
int main()
{
srand(time(0));
int T = 1;
while (T--)
{
m = rand() % 100 + 1;
p1 = rand() % 100, p2 = rand() % 100;
if(!p1&&!p2)p1++;
printf("%d %d %d\n", m, p1, p2);
n = p1 + p2;
for (int i = 0; i < n; ++i)
f[i] = i, l[i] = 0;
while (m--)
{
int u, v, k;
while (1)
{
u = rand() % n, v = rand() % n;
k = rand() % 2;
if (find(u) != find(v))
{
l[f[u]] = k ^ l[u] ^ l[v];
f[f[u]] = f[v];
break;
}
else if (l[u] ^ l[v] == k)
break;
}
printf("%d %d %s\n", u + 1, v + 1, !k ? "yes" : "no");
}
}
printf("0 0 0\n");
return 0;
}