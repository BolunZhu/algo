//带负环检测的SPFA
#include <queue>
// list_star begin
#include <iostream>
#include <string>
//
const int edge_num = 150000+10 ;
const int vertex_num=30000+10 ;
int edge_count=0;
// int vertex_count=0;
int head[vertex_num];
struct edge
{
    int s,d,w,next;
    // edge(){}
    // edge(int _s,int _d,int _w,int _next)
    // {
    //     s=_s;d=_d;w=_d;next=_next;
    // }
}E[edge_num];
//head[i] = index of first edge from vertex i
//next[j] = index of next edge after edge j
void init()
{
    edge_count=0;
    // vertex_count=0;
    memset(head,-1,sizeof(head));
}
void add(int i,int j,int w)
{
    E[edge_count].s=i;
    E[edge_count].d=j;
    E[edge_count].w=w;
    E[edge_count].next=head[i];
    // if(head[i]==-1){vertex_count++;}
    // if(head[j]==-1){vertex_count++;}
    head[i]=edge_count;
    edge_count++;
}
//list_star end
// const int vertex_num=100;

int dist[vertex_num+10];
bool inQue[vertex_num+10];
// int cnt[vertex_num+10];
std::queue<int> que;
int spfa(int scr)
{
    memset(dist,0x3f3f3f3f,sizeof(dist));
    memset(inQue,false,sizeof(inQue));
    // memset(cnt,0,sizeof(cnt));
    dist[scr]=0;
    while(!que.empty()){que.pop();}//clear queue
    que.push(scr);
    // cnt[scr]++;
    inQue[scr]=true;
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        for(int i=head[u];i!=-1;i=E[i].next)
        {
            if(dist[u]+E[i].w<dist[E[i].d])
            {//松弛
                dist[E[i].d]=dist[u]+E[i].w;
                if(!inQue[E[i].d])//如果不在队列则加入队列
                { 
                    // if(cnt[E[i].d]>=vertex_count-1)//每个点最多放入队列V-1次
                    // {
                    //     // printf("now cnt[E[i].d]=%d  vertex_count-1=%d\n",cnt[E[i].d],vertex_count-1);
                    //     return false;
                    // }
                    inQue[E[i].d]=true;
                    // cnt[E[i].d]++;
                    que.push(E[i].d);
                }
            }
        }
        //最好把inque写在后面 表示先加完点，再去掉它
        inQue[u]=false;
    }
    return true;
}

int main()
{
    int N,M;
    init();
    scanf("%d%d",&N,&M);
    for(int i=0;i<M;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a-1,b-1,c);
    }
    spfa(0);
    printf("%d\n",dist[N-1]);
    return 0;
}