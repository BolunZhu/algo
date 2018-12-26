// list_star
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
