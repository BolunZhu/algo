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
#include <cstdio>
#include <iostream>
#include <cstring>
//
const int edge_num = 1000 ;
const int vertex_num=25 ;
int edge_count=0;
int head[vertex_num];
struct edge
{
    int s,d,w,next;
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

int dist[vertex_num];
bool inQue[vertex_num];
//适用数组实现简单的stack 
//如果队列是宽度优先搜索 那stack就是深度优先搜索
int sta[vertex_num];
int cnt[vertex_num];
int top;//top of sta
int spfa(int scr)
{
    //init
    memset(dist,0x3f3f3f3f,sizeof(dist));
    memset(inQue,false,sizeof(inQue));
    memset(cnt,0,sizeof(cnt));
    top=0;
    //insert scr
    dist[scr]=0;
    sta[top]=scr;
    top++;
    inQue[scr]=true;
    //begin while
    while(top!=0)
    {
        int u=sta[top-1];
        top--;
        for(int i=head[u];i!=-1;i=E[i].next)
        {
            if(dist[u]+E[i].w>dist[E[i].d])
            {//松弛
                dist[E[i].d]=dist[u]+E[i].w;
                if(!inQue[E[i].d])//如果不在队列则加入队列
                { 
                    inQue[E[i].d]=true;
                    sta[top]=E[i].d;
                    top++;
                }
                if(++cnt[E[i].d]>24)
                {
                    return false;
                }
            }
        }
        //最好把inque写在后面 表示先加完点，再去掉它
        inQue[u]=false;
    }
    return true;
}
int app[25];// app[i] = the number of apps at time i
int x[25];// x[i] = the number of apps before time x (x not include)
int w[25];//input weight
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
        for(int j=1;j<=24;j++)
        {
            scanf("%d",&w[j]);
        }
        scanf("%d",&N);
        for(int j=0;j<N;j++)
        {
            int tmp;
            scanf("%d",&tmp);
            app[tmp+1]++;
        }
        for(int ans=0;ans<=N;ans++)
        {
            //init
            init();
            //build graph
            add(0,24,ans);
            for(int j=1;j<=24;j++)
            {//x[i]-x[i-1]>=0   == x[i-1]-x[i]<=0
                add(j,j-1,-app[j]);
            }
            for(int j=1;j<=24;j++)
            {//x[i]-x[i-1]<=app[i] 
                add(j-1,j,0);
            }
            for(int j=9;j<=24;j++)
            {//x[j+1]-x[j-7]>=w[j]  == x[j-7]-x[j+1]<=w[j]
                add(j-8,j,w[j]);
            }
            for(int j=1;j<=8;j++)
            {// x[j+1]-x[0] + x[25]-x[j+17] >= w[j] ==  x[j+17] - x[j+1] -x[25] <= -w[j]
                add(j+16,j,w[j]-ans);
            }
            
            if(spfa(0)&&dist[24]==ans)
            {
                flag=true;
                // for(int aa=0;aa<=24;aa++)
                // {
                //     printf("%d\n",dist[aa]);
                // }
                // printf("%d\n",dist[24]);
                printf("%d\n",ans);
                break;
            }
        }
        if(!flag){
            printf("No Solution\n");
        }
    }
    
    return 0;
}