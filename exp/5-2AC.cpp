#include<stdio.h>
#include<stdlib.h>
const int N = 40000+10;
int length=0,n;
struct node{
   int l;
   int r;
   int h;
}bul[N];
int cmp(const void * a,const void *b)
{
    if((*(node *)a).h>(*(node *)b).h)
    {
        return 1;
    }
    return -1;
}

void solve(int l,int r,int i)
{
    while(i<n&&(r<=bul[i].l||l>=bul[i].r))
        i++;
    if(i>=n){
        length+=(r-l);
        return ;
    }
    //开始二分
    if(r>bul[i].r)
        solve(bul[i].r,r,i+1);
    if(l<bul[i].l)
        solve(l,bul[i].l,i+1);
}
int main()
{
    int i,j;
    long long ans=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d%d%d",&bul[i].l,&bul[i].r,&bul[i].h);
    qsort(bul,n,sizeof(bul[0]),cmp);
    for(i=0;i<n;i++)
    {
         length=0;
         solve(bul[i].l,bul[i].r,i+1);
         ans+=(long long )bul[i].h*(long long)length;
    }
    printf("%lld\n",ans);
    return 0;
}
