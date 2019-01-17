#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
 
int pre[1000],rk[1000],p[1000],vis[1000];
int w0[1000],w1[1000];
int dp[700][700];
int n,p1,p2;
 
int get(int x){
    if(x!=pre[x]){
        int tmp = pre[x];
        pre[x] = get(pre[x]);
        rk[x] = rk[x]^rk[tmp];
    }
    return pre[x];
}
 
void unio(int x,int y,int k){
    int xx =get(x);
    int yy = get(y);
    if(xx!=yy){
        pre[xx] = yy;
        rk[xx]=rk[x]^rk[y]^k;
    }
}
 
int main()
{
    while(scanf("%d%d%d",&n,&p1,&p2)&&(n+p1+p2)){
        for(int i=1;i<=p1+p2;i++)
            pre[i]=i,rk[i]=0,vis[i]=0,w0[i]=0,w1[i]=0;
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++){
            int a,b;char s[10];
            scanf("%d%d%s",&a,&b,s);
            if(s[0]=='y')unio(a,b,0);
            else unio(a,b,1);
        }
        int cnt = 1;
        for(int i=1;i<=p1+p2;i++){
            if(!vis[i]){
                int f = get(i);
                for(int j=i;j<=p1+p2;j++){
                    if(get(j)==f&&!vis[j]){
                        vis[j]=1;
                        if(rk[j]==0)w0[cnt]++;
                        else w1[cnt]++;
                    }
                }
                p[cnt]=f;
                cnt++;
            }
        }
        dp[0][0]=1;
        for(int i=1;i<cnt;i++){
            int Min=min(w0[i],w1[i]);
            for(int j=p1;j>=Min;j--){
                if(dp[i-1][j-w0[i]]){
                    dp[i][j]+=dp[i-1][j-w0[i]];
                }
                if(dp[i-1][j-w1[i]]){
                    dp[i][j]+=dp[i-1][j-w1[i]];
                }
            }
        }
        if(dp[cnt-1][p1]!=1){
            printf("no\n");
            continue;
        }
        int ans[1000];
        int num = 0;
        int Mp = p1;
        for(int i=cnt-1;i>=1;i--){
            if(dp[i-1][Mp-w0[i]]==1){
                for(int j=1;j<=p1+p2;j++){
                    if(get(j)==p[i]&&rk[j]==0)ans[num++]=j;
                }
                Mp-=w0[i];
            }
            else {
                 for(int j=1;j<=p1+p2;j++){
                    if(get(j)==p[i]&&rk[j]==1)ans[num++]=j;
                }
                Mp-=w1[i];
            }
        }
        sort(ans,ans+num);
        for(int i=0;i<num;i++)
            printf("%d\n",ans[i]);
        puts("end");
    }
    return 0;
}