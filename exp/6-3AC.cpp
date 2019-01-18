#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn= 50000+10;
const int maxm=500000+10;
const int INF=1e9;
struct Edge
{
    int from,to,dist;
    Edge(){}
    Edge(int f,int t,int d):from(f),to(t),dist(d){}
}; 
int n,m;
int head[maxn],next[maxm];
Edge edges[maxm];
int d[maxn];
bool inq[maxn];

void init()
{
    m=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int from,int to,int dist)
{
    edges[m]=Edge(from,to,dist);
    next[m]=head[from];
    head[from]=m++;
}

int spfa(int index)
{
    memset(inq,0,sizeof(inq));
    for(int i=0;i<n;i++) d[i]= i==0?0:INF;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty())
    {
        int u=Q.front(); 
        Q.pop();
        inq[u]=false;
        for(int i=head[u];i!=-1;i=next[i])
        {
            Edge &e=edges[i];
            if(d[e.to]>d[u]+e.dist)
            {
                d[e.to]=d[u]+e.dist;
                if(!inq[e.to])
                {
                    inq[e.to]=true;
                    Q.push(e.to);
                }
            }
        }
    }
    return d[n-1]-d[index];
}
 
int main()
{
    int nn,max_v=-1;
    scanf("%d",&nn);
    init();
    while(nn--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        b+=10,a+=10;//����ֵ����10��,����a-1��Ϊ-1
        max_v=max(max_v,b);
        AddEdge(b,a-1,-c);
    }
    for(int i=10;i<=max_v;i++)//�Ӹ�ѭ���ɿ���,�����Լ���ĵ���Ϊ:[9,max_v](δ��������Դ0�ŵ�)
    {
        AddEdge(i,i-1,0);
        AddEdge(i-1,i,1);
        AddEdge(0,i,0);
    }
    AddEdge(0,9,0);
    n=max_v+1;
    printf("%d\n",spfa(9));//ע�����ս����d[max_v]-d[9]��ֵ,������d[max_v]�ĵ���ֵ
    return 0;
}
