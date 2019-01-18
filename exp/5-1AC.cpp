    #include<iostream>
    #include<cstdio>
    #include<algorithm>
    #include<cstring>
    #define lson l,m,rt<<1
    #define rson m+1,r,rt<<1|1
    const int maxn=100004;
    using namespace std;

    int col[maxn<<2];
    int sum[maxn<<2];
    
    void pushDown(int rt)
    {
        if(sum[rt]){
        col[rt<<1]=col[rt<<1|1]=1<<(sum[rt]-1);
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        sum[rt]=0;
        }
    }
    void update(int c,int L,int R,int l,int r,int rt)
    {
        if(l>=L&&R>=r)
        {
            sum[rt]=c;
            col[rt]=1<<(sum[rt]-1);
            return;
        }
        if(L>r||R<l)
            return ;
        if(sum[rt])
        pushDown(rt);
        int m=(l+r)>>1;
        if(m>=L) update(c,L,R,lson);
        if(m<R) update(c,L,R,rson);
        col[rt]=col[rt<<1]|col[rt<<1|1];
    }
    int query(int L,int R,int l,int r,int rt)
    {
        if(L<=l&&r<=R)
        {
            return col[rt];
        }
        if(L>r||R<l)
            return 0;
        pushDown(rt);
        int m=(l+r)>>1;
        return query(L,R,lson)|query(L,R,rson);
    }
    int main()
    {
        int l,t,o;
        while(scanf("%d%d%d",&l,&t,&o)!=EOF)
        {
            getchar();
            char p;
            int a,b,c;
            sum[1]=1;col[1]=1;
            for(int i=0; i<o; i++)
            {
                scanf("%c",&p);
                getchar();
                if(p=='P')
                {
                    scanf("%d%d",&a,&b);
                    if(a>b)
                    {
                        int x=a;a=b;b=x;
                    }
                    getchar();
                    int tem=query(a,b,1,l,1);
                    int ans=0;
                    while(tem)
                    {
                        ans+=tem&1;
                        tem>>=1;
                    }
                    printf("%d\n",ans);
                }
                else
                {
                    scanf("%d%d%d",&a,&b,&c);
                    if(a>b)
                    {
                        int x=a;a=b;b=x;
                    }
                    getchar();
                    update(c,a,b,1,l,1);
                }
            }
        }
        return 0;
    }
