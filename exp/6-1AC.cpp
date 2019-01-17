//������������SPFA
// list_star begin
#include <iostream>
#include <string>
//
const int edge_num = 150000+10 ;
const int vertex_num=30000+10 ;
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
//��������ʵ�ּ򵥵�stack 
//��������ǿ���������� ��stack���������������
int sta[vertex_num];
int top;//top of sta
int spfa(int scr)
{
    //init
    memset(dist,0x3f3f3f3f,sizeof(dist));
    memset(inQue,false,sizeof(inQue));
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
            if(dist[u]+E[i].w<dist[E[i].d])
            {//�ɳ�
                dist[E[i].d]=dist[u]+E[i].w;
                if(!inQue[E[i].d])//������ڶ�����������
                { 
                    inQue[E[i].d]=true;
                    sta[top]=E[i].d;
                    top++;
                }
            }
        }
        //��ð�inqueд�ں��� ��ʾ�ȼ���㣬��ȥ����
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