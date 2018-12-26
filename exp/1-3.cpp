//True Liars
// n p1 p2 p1=good_divine p2=bad_devilish
// n<=1000 p1 p2 <= 300
#include <iostream>
//给定了x0 y0 x1 y1 到xn yn 且已知sumx=a sumy=b 这是01dp背包可行性问题
const int maxm=300+5;
const int maxn=2*maxm;

int f[maxn];
int r[maxn];
int n,p1,p2;
int f_p1;
int num_tree;
int dp[maxn][maxm];//n*m 600*300
int a[maxm],b[maxm];

int find(int v){
    if(f[v]==v)
    {
        return v;
    }
    else{
        int tmp=f[v];
        f[v]=find(f[v]);
        r[v]=(r[v]+r[tmp])%2;
        return f[v];
    }
}
bool merge(int x,int y , int v){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy)
    {
        if(r[y]==(r[x]+v)%2 )
        {
            return true;
        }
        {
            return false;
        }
    }
    else
    {//merge them
    //r[i]表示 如果i的父亲是真=0 则 i是r[i]
         // r[fx]+r[x]+v= r[fy]+r[y]
        f[fy]=fx;
        r[fy]=(v+r[x]-r[y]+2)%2;
        return true;
    }
} 
void init(){
    //有一个致命的bug在于 如果你的数组为maxn 那么越界访问不一定会爆错 而是给WA！
    num_tree=maxn;
    for(int i=0;i<maxn;i++)
    {
        f[i]=i;
        r[i]=0;//0 true 1 liar
    }
}
void dp_init(){
    for(int i=0;i<maxn;i++)
    {
        dp[0][i]=-1;
    }
    dp[0][0]=0;
    memset(a,0,sizeof(a));
    memset(a,0,sizeof(b));
    for(int i=1;i<=p1+p1;i++)
    {
        int tmp=find(i);
        if(r[tmp]==0)
        {//true
            a[tmp]++;
        }
        else{
            b[tmp]++;
        }
    }
    for(int i=1;i<=p1+p1;i++)
    {
        if(f[i]==i)
        {
            a[i]=a[i]-b[i];
            f_p1=p1-b[i];
        }
    }
}
int dp_find()
{// dp[i][j]=?
// dp[i-1][j]>=0 : dp[i-1][j]
    for(int i=1;i<=p1+p1;i++)
    {
        for(int j=0;j<=f_p1;j++)
        {
            if(dp[i-1][j]>=0)
            {
                if(j>=a[i]&&dp[i][j-a[i]]>0)// i-1 & i all ok
                {
                    return false;
                }
                else
                {
                    dp[i][j]=1;
                }   
            }
            else
            {
                if(j<a[i]||dp[i][j-a[i]]<=0)
                {
                    dp[i][j]=-1;
                }
                else{
                    dp[i][j]=dp[i][j-a[i]]-1;
                }
            }
        }
    }
    if(dp[p1+p2][f_p1]>=0)
    {
        //print this way

        printf("end\n");
    }
    else
    {
        printf("no\n");
    }
}
int main(){
    while(scanf("%d%d%d",&n,&p1,&p2)==3&&n)
    {
        // if ok print num & end
        // else print no
    }
    return 0;
}