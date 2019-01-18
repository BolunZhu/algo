#include<cstdio>
#include<cstring>
#define N 110000
char str1[1100];
int a[N],id[N];
int k,n,l,r,m,k1,count[N],rank[N<<1],rank1[N],tmp[N],sa[N],height[N],ans;
inline int max(int x,int y){
    return x>y?x:y;
}
int q[N],n2,q1[N],n3;
inline bool check(int x){
    bool visit[110],flag=false,flag1=false;int cnt=0;
    n2=0;
    for (int i=1;i<=n;++i){
        if (height[i]>=x){
            if (!visit[id[sa[i]]]) visit[id[sa[i]]]=true,cnt++;
        }else{
            memset(visit,false,sizeof(visit));
            visit[id[sa[i]]]=true;cnt=1;flag=false;
        }
        if ((cnt>(k1>>1))&&(!flag)) q[++n2]=sa[i],flag=true,flag1=true;
    }
    if (flag1) {
        for (int i=1;i<=n2;++i) q1[i]=q[i];n3=n2;
    }
    return flag1;
}
int main(){
    while(~scanf("%d",&k1),k1){
        n=0;m=30+k1;r=0;l=1;n2=0;
        for (int i=1;i<=k1;++i){
            scanf("%s",str1);
            int n1=strlen(str1);r=max(r,n1);
            for (int j=n+n1;j>n;--j) a[j]=str1[j-n-1]-'a'+1,id[j]=i;
            n=n+n1;
            a[++n]=30+i;id[n]=i;
        }
        for (int i=1;i<=m;++i) count[i]=0;
        memset(rank,0,sizeof(rank));
        for (int i=1;i<=n;++i) count[a[i]]=1;
        for (int i=1;i<=m;++i) count[i]+=count[i-1];
        for (int i=1;i<=n;++i) rank[i]=count[a[i]];
        k=0;
        for (int p=1;k!=n;p<<=1,m=k){
            for (int i=1;i<=m;++i) count[i]=0;
            for (int i=1;i<=n;++i) count[rank[i+p]]++;
            for (int i=1;i<=m;++i) count[i]+=count[i-1];
            for (int i=n;i>=1;--i) tmp[count[rank[i+p]]--]=i;
            for (int i=1;i<=m;++i) count[i]=0;
            for (int i=1;i<=n;++i) count[rank[i]]++;
            for (int i=1;i<=m;++i) count[i]+=count[i-1];
            for (int i=n;i>=1;--i) sa[count[rank[tmp[i]]]--]=tmp[i];
            memcpy(rank1,rank,sizeof(rank)>>1);
            rank[sa[1]]=k=1;
            for (int i=2;i<=n;++i){
                if (rank1[sa[i-1]]!=rank1[sa[i]]||rank1[sa[i-1]+p]!=rank1[sa[i]+p])++k;
                rank[sa[i]]=k;
            }
        }
        k=0;
        for (int i=1;i<=n;++i){
            if (rank[i]==0){
                height[1]=0;continue;
            }
            k=k==0?0:k-1;
            while (a[i+k]==a[sa[rank[i]-1]+k])++k; 
            height[rank[i]]=k;
        }
        while (l<=r){
            int mid=(l+r)>>1;
            if (check(mid)) ans=mid,l=mid+1;else r=mid-1;
        }

        if (l==1)printf("?\n");else{
            for (int j=1;j<=n3;++j){
                int tmp1=q1[j];
                for (int i=tmp1;i<ans+tmp1;++i) putchar(a[i]+'a'-1);
                puts("");
            }
        }
        printf("\n");
    }
    return 0;
}