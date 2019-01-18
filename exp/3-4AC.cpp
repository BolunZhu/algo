#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <iostream>


using namespace std;
const int maxs=2000010;
int dp[maxs][33];
int wa[maxs],wb[maxs],wv[maxs],sa[maxs],wd[maxs];
int ranks[maxs],height[maxs],s[maxs];
char str[maxs];

bool cmp(int *r,int a,int b,int k)
{
    return r[a]==r[b]&&r[a+k]==r[b+k];
}
void rmq_init(int *a,int n){

    for(int i=1;i<=n;i++) dp[i][0]=a[i];
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
//ST 预处理
int rmq_ask(int ll,int rr)
{
    int k;
    ll=ranks[ll];
    rr=ranks[rr]; //注意这里我们要找到这两的排名，之后在这段排名中找到最小的height值
    if(ll>rr) swap(ll,rr);
    ll++; 
    k=(int)(log(rr-ll+1.0)/log(2.0));
    return min(dp[ll][k],dp[rr-(1<<k)+1][k]);
}
void getsa(int *r,int n,int m)
{
    int i,j,p,*x=wa,*y=wb;
    for(i=0;i<m;i++) wd[i]=0;
    for(i=0;i<n;i++) wd[x[i]=r[i]]++;
    for(i=1;i<m;i++) wd[i]+=wd[i-1];
    for(i=n-1;i>=0;i--) sa[--wd[x[i]]]=i;

    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) wd[i]=0;
        for(i=0;i<n;i++) wd[wv[i]]++;
        for(i=1;i<m;i++) wd[i]+=wd[i-1];
        for(i=n-1;i>=0;i--) sa[--wd[wv[i]]]=y[i];
        for(swap(x,y),x[sa[0]]=0,p=1,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}

void getheight(int *r,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) ranks[sa[i]]=i;
    for(i=0;i<n;i++){
        if(k)
            k--;
        else k=0;
        j=sa[ranks[i]-1];
        while(r[i+k]==r[j+k])
            k++;
        height[ranks[i]]=k;
    }
}
//sa ,height

//查询
int main()
{
    static int times=1;
    while(~scanf("%s",str)&&str[0]!='#')
    {
        int len=strlen(str);
        for(int i=0;i<len;i++)
            s[i]=str[i]-'a'+1;
        s[len]=0;
        getsa(s,len+1,30);
        getheight(s,len);
        rmq_init(height,len);
        int ans=-1,anspos,anslen;
        for(int L=1;L<=len/2;L++)  // 枚举长度
        {
            for(int j=0;j<len-L;j+=L)
            {
                if(str[j]!=str[j+L])
                    continue;

                int k=rmq_ask(j,j+L);//区间最小值
                int tol=k/L+1;//假定出现次数
                int temppos=j;//假设的初始位置
                int cnt=0,yu=L-k%L;//这里看有多少个能再补一个l的长度
                for(int m=j-1;m>j-L&&str[m]==str[m+L]&&m>=0;m--)//从这段区间开始往前找
                {
                    cnt++;
                    if(cnt==yu)
                    {
                        tol++;
                        temppos=m;
                    }
                    else if(ranks[m]<ranks[temppos])//保证了字典序
                        temppos=m;
                }
                if(ans<tol)
                {
                    ans=tol;
                    anspos=temppos;
                    anslen=tol*L;
                }
                else if(ans==tol&&ranks[temppos]<ranks[anspos])
                {
                    anspos=temppos;
                    anslen=tol*L;
                }
            }
        }
        printf("Case %d: ",times++);
        if(ans==1)
        {
            char c='z';
            for(int i=0;i<len;i++)
                if(str[i]<c)
                    c=str[i];

            printf("%c\n",c);
        }
        else
        {
            for(int i=anspos;i<anspos+anslen;i++)
            {
                printf("%c",str[i]);
            }
            puts("");
        }
    }
    return 0;
}