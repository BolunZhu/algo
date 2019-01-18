#include<stdio.h>
#include<string.h>

const int maxn=1e6+9;

int first1[maxn],first2[maxn],vis[maxn],fath[maxn],dis[maxn],ans[maxn],h[maxn];
int N;
struct node
{
    int v,w,nex;
}edge[maxn];
void build_edge(int u,int v,int w,int firs[])
{
    edge[N]=(node){v,w,firs[u]};
    firs[u]=N++;
}
void init()
{
    memset(first1,-1,sizeof(first1));
    memset(first2,-1,sizeof(first2));
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));
    memset(h,0,sizeof(h));
    memset(ans,0,sizeof(ans));
    N=0;
}
int find(int x)
{
    if(x!=fath[x]) fath[x]=find(fath[x]);
    return fath[x];
}
void Trajan(int u)//模板
{
    fath[u]=u;
    vis[u]=1;
    for(int i=first2[u];~i;i=edge[i].nex)
    {
        int v=edge[i].v,w=edge[i].w;
        if(vis[v])
        {
            int f=find(v);
            ans[w]=dis[v]+dis[u]-2*dis[f];
        }
    }
    for(int i=first1[u];~i;i=edge[i].nex)
    {
        int v=edge[i].v,w=edge[i].w;
        if(!vis[v])
        {
            dis[v]=dis[u]+w;
            Trajan(v);
            fath[v]=u;
        }
    }
}
int main()
{
    int n,m,p;
    while(~scanf("%d%d",&n,&m))
    {
        init();
        int u,v,w;
        char a;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d%c%*c",&u,&v,&w,&a);
            build_edge(u,v,w,first1);//建双向图
            build_edge(v,u,w,first1);
            h[v]++;
        }
        int root;
        for(int i=1;i<=n;i++)//查找根节点
        {
            if(!h[i])
            {
                root=i;
                break;
            }
        }
        scanf("%d",&p);
        for(int i=1;i<=p;i++)//记录询问
        {
            scanf("%d%d",&u,&v);
            build_edge(u,v,i,first2);
            build_edge(v,u,i,first2);
        }
        Trajan(root);
        for(int i=1;i<=p;i++)
        {
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}