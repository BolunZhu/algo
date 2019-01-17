//True Liars
// n p1 p2 p1=good_divine p2=bad_devilish
// n<=1000 p1 p2 <= 300
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <stdio.h>
#include <string.h>
//给定了x0 y0 x1 y1 到xn yn 且已知sumx=a sumy=b 这是01dp背包可行性问题
const int maxm=300+5;
const int maxn=2*maxm;

int f[maxn];
int r[maxn];
int n,p1,p2;
int f_p1;
int num_tree;
int dp[maxn][maxm];//n*m 600*300
int a[maxn],b[maxn];//a[i] = i true than #true
int true_root[maxn];
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
    // printf("now merge %d %d",x,y);
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
        // printf("f[fy]=fx fy=%d fx=%d f[fy]=%d\n",fy,fx,f[fy]);
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
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(int i=0;i<p1+p2;i++)
    {
        int tmp=find(i);
        // printf("i = %d tmp = %d = find(i) \n",i,tmp);
        if(r[i]==0)
        {//true
            a[tmp]++;
            // printf("r[i]==0 a[tmp]++ now a[tmp]=%d\n",a[tmp]);
        }
        else{
            // printf("before b[tmp]++ b[tmp]=%d\n",b[tmp]);
            b[tmp]++;
            // printf("r[i]==0 b[tmp]++ now b[tmp]=%d\n",b[tmp]);
        }
    }
    memset(dp,0,sizeof(dp));
    // for(int i=0;i<maxm;i++)
    // {
    //     dp[0][i]=1;
    // }
    dp[0][0]=1;
    memset(true_root,0,sizeof(true_root));
}

void print_res()
{
    //begin with dp[p1+p2][p1]
    //use int true_list[maxn] to store index of true
    int n=p1+p2,m=p1;
    // printf("now begin print_res:\n");
    while(n>0)
    {
        // printf("n=%d , m=%d",n,m);

        if(m-a[n-1]>=0 && dp[n-1][m-a[n-1]] )
        {
            true_root[n-1]=1;
            m=m-a[n-1];
            n--;
        }
        else if(m-b[n-1]>=0 && dp[n-1][m-b[n-1]])
        {
            true_root[n-1]=2;
            m=m-b[n-1];
            n--;
        }
    }
    for(int i=0;i<maxn;i++)
    {
        if(((true_root[find(i)]==1)&&r[i]==0)||((true_root[find(i)]==2)&&r[i]==1))
        {
            printf("%d\n",i+1);
        }
    }
}

void dp_find()
{
    //dp[n][m]= amount of methods that sum = m when just use n set.
    //dp[n][m]= dp[n-1][m-a[n-1]]+dp[n-1][m-b[n-1]]
    
    for(int i = 1; i <= p1+p2  ; i++)
    {
        // int flag= (a[i-1]!=b[i-1]);
        if(a[i-1]==0&&b[i-1]==0)
        {
            for(int j =0 ; j<=p1;j++)
            {
                dp[i][j]=dp[i-1][j];
            }
        }
        else
        {
            for(int j =0 ; j<=p1;j++)
            {
                // printf("now solve dp[%d][%d] ,a[n-1]=%d b[n-1]=%d\n",i,j,a[i-1],b[i-1]);
                if(j-a[i-1]>=0)
                {
                    // printf("j-a[i-1]>0  j=%d i=%d a[i-1]=%d\n",j,i,a[i-1]);
                    dp[i][j] += dp[i-1][j-a[i-1]];
                    // printf("now dp[%d][%d]=%d\n",i,j,dp[i][j]);
                }
                if(j-b[i-1]>=0)
                {
                // printf("j-b[i-1]>0  j=%d i=%d b[i-1]=%d\n",j,i,b[i-1]);
                
                dp[i][j] += dp[i-1][j-b[i-1]];
                // printf("now dp[%d][%d]=%d\n",i,j,dp[i][j]);
                }
            }
        }
        
    }
    int res = dp[p1+p2][p1];
    // printf("res=%d\n",res);
    if(res==1)
    {
        //print this way
        print_res();
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
        init();
        for(int i=0; i<n;i++)
        {
            int a,b;
            char ch[5];
            scanf("%d%d%s",&a,&b,ch);
            merge(a-1,b-1,ch[0]=='n');
        }
        dp_init();
        dp_find();
        // if ok print num & end
        // else print no
    }
    return 0;
}