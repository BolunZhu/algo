#include <stdio.h>
#include <string.h>
const int maxm = 2000+5;
const int maxn = 500+5;
int M,N;
int x[maxm],y[maxm];
char c[maxm];

int f[maxn];
int r[maxn];//r[i]=i与其父亲的关系  0: = 1: i>f[i] 2: i<f[i]
int find(int v){
    if(f[v]==v)
    {
        return v;
    }
    else{
        int tmp=f[v];
        f[v]=find(f[v]);
        r[v]=(r[v]+r[tmp]+3)%3;
        return f[v];
    }
}
bool merge(int x,int y , int v){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy)
    {
        if(r[y]==(r[x]+v)%3 )
        {
            return true;
        }
        else{
            return false;
        }
    }
    else
    {//merge them
        f[fy]=fx;
        r[fy]=(v+r[x]-r[y]+3)%3;
        return true;
    }
} 
void init(){
    for(int i=0;i<maxn;i++)
    {
        f[i]=i;
        r[i]=0;
    }
}

int main()
{
    while(scanf("%d%d",&N,&M)==2)
    {
        for(int i=0;i<M;i++)
        {
            scanf("%d%c%d",&x[i],&c[i],&y[i]);
        }
        int judge_num=0;
        int judge_line=0;
        int judge_name=0;
        for(int judge=0; judge<N;judge++)
        {
            int flag=-1;//-1: OK else: find error
            //init
            init();
            //merge
            for(int i=0;i<M;i++)
            {
                int cc=0;
                if(x[i]==judge||y[i]==judge)
                {//ignore judge's behavior
                    continue;
                }
                if(c[i]=='=')
                {
                    cc=0;
                }
                else if(c[i]=='>')
                {
                    cc=2;
                }
                else if(c[i]=='<')
                {
                    cc=1;
                }
                else
                {
                    printf("input error\n");
                    return 1;
                }
                if(merge(x[i],y[i],cc)==false)
                {
                    flag=i+1;
                    break;
                }
            }
            if(flag==-1)// it's a judge
            {
                judge_name=judge;
                judge_num++;
            }
            else// not a judge
            {
                if(flag>judge_line)
                {
                    judge_line=flag;
                }
            }
            //if error tag judge_num & judge_line
        }
        if(judge_num==0)
        {
            printf("Impossible\n");
        }
        else if(judge_num>1)
        {
            printf("Can not determine\n");
        }
        else
        {
            printf("Player %d can be determined to be the judge after %d lines\n",judge_name,judge_line);
        }
    }
    return 0;
}