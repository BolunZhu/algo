// x0+x1+x2+x3+..x7>=w7
// y8-y0>=w7
// sp case: x19+x20+x21+x22+x23+x0+x1+x2>=w2
// y24-y19+y3-y0>=w2
// y3-y19>=w2-y24
// let y0 = 0
// y24 = ans
// for 7<=i<24
// yi+1-yi-7>=wi
// for 0<=i<7
// yi+1-y(24+i-7)>=wi-ans
// for i=0 to i<24
// yi+1-yi>=0
// y24-y0>=ans
// yo-y24<=ans

//如果希望求差值最大 则起点应该是yo 使得yo-y1<=w
//如果希望求差值最小 则起点应该是y1 使得y1-yo>=w    => yo-y1<=w
//不带负环检测的SPFA
// list_star begin
//带负环检测的SPFA
#include <queue>
// list_star begin
#include <iostream>
#include <string>
//
const int edge_num = 1000 ;
const int vertex_num=100 ;
int edge_count=0;
int vertex_count=0;
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
    if(head[i]==-1){vertex_count++;}
    if(head[j]==-1){vertex_count++;}
    head[i]=edge_count;
    edge_count++;
}
//list_star end
// const int vertex_num=100;

int dist[vertex_num+10];
bool inQue[vertex_num+10];
int cnt[vertex_num+10];
std::queue<int> que;
int spfa(int scr)
{
    memset(dist,0x3f3f3f3f,sizeof(dist));
    memset(cnt,0,sizeof(cnt));
    dist[scr]=0;
    while(!que.empty()){que.pop();}//clear queue
    que.push(scr);
    cnt[scr]++;
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
                    if(cnt[E[i].d]>=vertex_count-1)//每个点最多放入队列V-1次
                    {
                        return false;
                    }
                    inQue[E[i].d]=true;
                    cnt[E[i].d]++;
                    que.push(E[i].d);
                }
            }
        }
        //最好把inque写在后面 表示先加完点，再去掉它
        inQue[u]=false;
    }
    return true;
}
int app[24];// app[i] = the number of apps at time i
int x[25];// x[i] = the number of apps before time x (x not include)
int w[24];//input weight
int main()
{
    bool flag=false; // true: find solution false:no solution
    int N,M;
    scanf("%d",&M);
    for(int i=0;i<M;i++)
    {
        //input
        memset(app,0,sizeof(app));
        memset(x,0,sizeof(x));
        memset(w,0,sizeof(w));
        for(int j=0;j<24;j++)
        {
            scanf("%d",&w[i]);
        }
        scanf("%d",&N);
        for(int j=0;j<N;j++)
        {
            int tmp;
            scanf("%d",&tmp);
            app[tmp]++;
        }
        for(int ans=0;ans<=N;ans++)
        {
            //init
            init();
            //build graph
            for(int j=1;j<=N;j++)
            {//x[i]-x[i-1]>=0   == x[i-1]-x[i]<=0
                add(j,j-1,0);
            }
            for(int j=1;j<=N;j++)
            {//x[i]-x[i-1]<=app[i] 
                add(j-1,j,app[j]);
            }
            for(int j=7;j<N;j++)
            {//x[j+1]-x[j-7]>=w[j]  == x[j-7]-x[j+1]<=w[j]
                add(j+1,j-7,w[j]);
            }
            for(int j=0;j<7;j++)
            {// x[j+1]-x[0] + x[25]-x[j+17] >= w[j] ==  x[j+17] - x[j+1] -x[25] <= -w[j]
                add(j+17,j+1,ans-w[j]);
            }
            add(24,0,-ans);
            if(spfa(0))
            {
                flag=true;
                for(int aa=0;aa<=24;aa++)
                {
                    printf("%d\n",dist[aa]);
                }
                printf("%d\n",dist[24]);
                break;
            }
        }
        if(!flag){
            printf("No Solution\n");
        }
    }
    
    return 0;
}