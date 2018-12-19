#include <iostream>
using namespace std;
const int M = 50000+5;
int a[M];
int b[3*M];
int c[3*M];
int n,k;
int sum=0;
int not_sure=0;
int find(int x)
{
    return a[x]==x ?  x:a[x]=find(a[x]);
    
}
int eat(int x,int y)
{
    int resx=find(x);
    int resy=find(y);
    if(b[resx]/3==b[resy]/3)// if a & b in same big_set
    {
        if((b[resx]+1)%3!=b[resy]%3){// but not right kind
            return false;
        }
        else{
            //do nothing
            return true;
        }
    }
    else
    {//insert y into x
        
        for(int i=0;i<3;i++)
        {
            //if yi empty then do nothing
            int yi = c[ (b[resy]+i)%3+ (b[resy]- (b[resy]%3) ) ];
            if( yi==-1  )
            {
                //do nothing
            }
            else
            {//insert yi into xi
                int xi = c[ (b[resx]+i+1)%3+ ( b[resx]-(b[resx]%3) ) ];
                if(xi==-1)
                {
                    //insert yi into a empty head
                    a[yi]=yi;
                    c[ (b[resx]+i+1)%3+ ( b[resx]-(b[resx]%3) ) ]=yi;
                    b[yi]=(b[resx]+i+1)%3+ ( b[resx]-(b[resx]%3) ) ;
                }
                else
                {
                    a[yi]=xi;
                }
            }
        }
        return true;
    }
}
int uni(int x,int y)
{
    int resx=find(x);
    int resy=find(y);
    if(b[resx]/3==b[resy]/3)// if a & b in same big_set
    {
        if(b[resx]!=b[resy]){// but not same kind
            return false;
        }
        else{
            //do nothing
            return true;
        }
    }
    else
    {//insert y into x
        
        for(int i=0;i<3;i++)
        {
            //if yi empty then do nothing
            int yi = c[ (b[resy]+i)%3+ (b[resy]- (b[resy]%3) ) ];
            if( yi==-1  )
            {
                //do nothing
            }
            else
            {//insert yi into xi
                int xi = c[ (b[resx]+i)%3+ ( b[resx]-(b[resx]%3) ) ];
                if(xi==-1)
                {
                    //insert yi into a empty head
                    a[yi]=yi;
                    c[ (b[resx]+i)%3+ ( b[resx]-(b[resx]%3) ) ]=yi;
                    b[yi]=(b[resx]+i)%3+ ( b[resx]-(b[resx]%3) ) ;
                }
                else
                {
                    a[yi]=xi;
                }
            }
        }
        return true;
    }
}
int solve(int d,int x,int y)
{
    //if illegal
    if(x>n||y>n)
    {
        return false;
    }
    if(d==2&&x==y)
    {
        return false;
    }
    //legal case
    if(d==1)
    {
        // cout<<"now uni "<<x<<" and "<<y<<"\n";
        return uni(x,y);
    }
    else
    {
        // cout<<"now eat "<<x<<" and "<<y<<"\n";
        return eat(x,y);
    }
}

int main(int argc, char const *argv[])
{
    //init
    for(int i=0;i<M;i++)
    {
        a[i]=i;
    }
    memset(c,-1,sizeof(c));
    for(int i=0;i<M;i++)
    {
        b[i]=3*i;
        c[3*i]=i;
    }
    //input
    scanf("%d%d",&n,&k);
    for(int i = 0; i < k; i++)
    {
        int d,x,y;
        scanf("%d%d%d",&d,&x,&y);
    //solve
        if(!solve(d,x,y))
        {
            // cout<<"case"<<i<<": false\n";
            sum++;
        }
    }
    //ouput
    printf("%d\n",sum);
    return 0;
}
