#include <queue>
// list_star begin
#include <iostream>
#include <string>
//
const int edge_num = 1000 ;
const int vertex_num=100 ;
int edge_count=0;
int head[vertex_num];
struct edge
{
    int s,d,w,next;
    edge(){}
    edge(int _s,int _d,int _w,int _next)
    {
        s=_s;d=_d;w=_d;next=_next;
    }
}E[edge_num];
//head[i] = index of first edge from vertex i
//next[j] = index of next edge after edge j
void init()
{
    edge_count=0;
    memset(head,-1,sizeof(head));
}
void add(int i,int j,int w)
{
    E[edge_count].s=i;
    E[edge_count].d=j;
    E[edge_count].w=w;
    E[edge_count].next=head[i];
    head[i]=edge_count;
    edge_count++;
}
//list_star end
// const int vertex_num=100;

int dist[vertex_num+10];
bool inQue[vertex_num+10];
std::queue<int> que;
void spfa(int scr)
{
    memset(dist,0x3f3f3f3f,sizeof(dist));
    dist[scr]=0;
    while(!que.empty()){que.pop();}//clear queue
    que.push(scr);
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
                    inQue[E[i].d]=true;
                    que.push(E[i].d);
                }
            }
        }
        //最好把inque写在后面 表示先加完点，再去掉它
        inQue[u]=false;
    }
}