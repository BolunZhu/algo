    // poj3415 zbl
    // vis 记录当前高度能持续到哪里
    // hh 记录当前高度和次高的相差多少。
    // a 记录一段区间有多少个子串是属于a串
    // b 记录一段区间有多少个子串是属于b串
    // st 单调栈。
    // L、R 单调栈的左右区间。
    #include<cstdio>
    #include<cstring>
    #include<algorithm>
    using namespace std;
    typedef long long ll;
    const int N=200000+100;
    char s[N],s2[N];
    int sa[N],t[N],t2[N],c[N];
    int height[N],rk[N];
    int a[N],b[N],st[N],L[N],R[N];
    int vis[N],hh[N];

    void SuffixSort(int n,int m)
    {
        int i,*x=t,*y=t2;
        for(i=0;i<m;++i) c[i]=0;
        for(i=0;i<n;++i) x[i]=s[i];
        for(i=0;i<n;++i) c[x[i]]++;
        for(i=1;i<m;++i) c[i]+=c[i-1];
        for(i=n-1;i>=0;--i) sa[--c[x[i]]]=i;
        for(int k=1;k<=n;k<<=1)
        {
            int p=0;
            for(i=n-k;i<n;++i) y[p++]=i;
            for(i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
            for(i=0;i<m;++i) c[i]=0;
            for(i=0;i<n;++i) c[x[i]]++;
            for(i=1;i<m;++i) c[i]+=c[i-1];
            for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
            swap(x,y);
            p=1;x[sa[0]]=0;
            for(i=1;i<n;++i)
                x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
            if(p>=n) break;
            m=p;
        }
    }
    void getHeight(int n)
    {
        int i,j,k=0;
        for(i=1;i<=n;++i) rk[sa[i]]=i;
        for(i=0;i<n;++i)
        {
            if(k) k--;
            j=sa[rk[i]-1];
            while(s[i+k]==s[j+k]) k++;
            height[rk[i]]=k;
        }
    }
    void slove(int n, int n1,int k){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        int t;
        for(int i = 1; i <= n; i++){
            if (sa[i] < n1) a[i] = a[i-1]+1; else a[i] = a[i-1];
            if (sa[i] > n1) b[i] = b[i-1]+1; else b[i] = b[i-1];
        }
        t = 1;
        for(int i = 1; i <= n; i++){
            while(t > 1 && height[st[t-1]] >= height[i])t--;
            L[i] = (t == 1) ? 1 : (st[t-1]);
            st[t++] = i;
            hh[i] = min(height[i] - height[L[i]],height[i]-k+1);
        }
        t = 1;
        for (int i = n; i >= 1; i--){
            while(t > 1 && height[st[t-1]] >= height[i])t--;
            R[i] = (t == 1)?n:st[t-1]-1;
            st[t++] = i;
            if (R[i] != n) hh[i] = min(hh[i],height[i] - height[R[i]+1]);
        }
    }
    long long  the_end(int n, int k){
        memset(vis,0,sizeof(vis));
        long long ans = 0;
        for (int i = 1; i <= n; i++){
            if (height[i] >= k && L[i] > vis[height[i]]){
                vis[height[i]] = R[i];
                ans += (long long)(a[R[i]] - a[L[i]-1])*(b[R[i]] - b[L[i]-1])*hh[i];
            }
        }
        return ans;
    }
    int main()
    {
        int k;
        while(~scanf("%d",&k) && k){
        int n1,n;
        scanf("%s",s);
        n1=strlen(s);
        s[n1]='$';
        scanf("%s",s+n1+1);
        n=strlen(s);
        SuffixSort(n+1,150); //字符后面补一个0，所以n+1.
        getHeight(n); //算这个的时候不用加0.
        slove(n,n1,k);
        long long ans = the_end(n,k);
        printf("%I64d\n",ans);
        }
        return 0;
    }
    
