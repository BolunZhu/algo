#include <iostream>
using namespace std;
int a[50000+5];
int b[50000+5];
int n,k;
int sum=0;
int not_sure=0;
// let 0=A 1=B 2=C other=no_sure
// let not_sure = next num init=0
void merge_tag(int x ,int y)
{
    
    if(a[x]<a[y])
    {
        int old=a[y];
        for(int i=1;i<=n;i++)
        {
            if(a[i]==old)
            {
                a[i]=a[x];
                b[i]=(b[i]-b[y]+b[x]+3)%3;
            }
        }
    }
    else
    {
        int old=a[x];
        for(int i=1;i<=n;i++)
        {
            if(a[i]==old)
            {
                a[i]=a[y];
                b[i]=(b[i]-b[x]+b[y]+3)%3;
            }
        }
    }
}
int uni(int x,int y)//error return 0 else return 1
{
    if(a[x]==-1)
    {
        if(a[y]==-1)
        {
            a[x]=not_sure;
            a[y]=not_sure;
            b[x]=0;
            b[y]=0;
            not_sure++;
            return 1;
        }
        else
        {
            a[x]=a[y];
            b[x]=b[y];
            return 1;
        }
    }
    else
    {
        if(a[y]==-1)
        {
            a[y]=a[x];
            b[y]=b[x];
            return 1;
        }
        else
        {
            if(a[x]==a[y]&&b[x]!=b[y])
            {//flase
                return 0;
            }
            else
            {
                merge_tag(x,y);
                return 1;
            }
        }
    }
}
void merge_eat(int x,int y)
{
    if(a[x]<a[y])
    {
        int old=a[y];
        for(int i=1;i<=n;i++)
        {
            if(a[i]==old)
            {
                a[i]=a[x];
                b[i]=(b[i]-b[y]+b[x]+4)%3;
            }
        }
    }
    else
    {
        int old=a[x];
        for(int i=1;i<=n;i++)
        {
            if(a[i]==old)
            {
                a[i]=a[y];
                b[i]=(b[i]-b[x]+b[y]+5)%3;
            }
        }
    }
}
int eat(int x,int y)
{
    if(a[x]==-1)
    {
        if(a[y]==-1)// a and b both first time
        {
            a[x]=not_sure;
            a[y]=not_sure;
            b[x]=0;
            b[y]=1;
            not_sure++;
            return 1;
        }
        else//a first time
        {
            a[x]=a[y];
            b[x]=(b[y]+2)%3;
            return 1;
        }
    }
    else
    {
        if(a[y]==-1)//b first time
        {
            a[y]=a[x];
            b[y]=(b[x]+1)%3;
            return 1;
        }
        else//a and b both have tag already
        {
            if( a[x]==a[y]&&
                ((b[x]+1)%3) != b[y])//a and b aren't in same set
            {//flase
                return 0;
            }
            else
            {
                merge_eat(x,y);
                return 1;
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    //init
    memset(a,-1,sizeof(a));
    memset(b,-1,sizeof(b));
    //input
    cin>>n>>k;
    for(int i = 0; i < k; i++)
    {
        int d,x,y;
        cin>>d>>x>>y;
    //solute
        if(x>n||y>n)
        {//false
            sum++;
            continue;
        }
        if(d==1)
        {//same set
            if(!uni(x,y))
            {
                sum++;
                continue;
            }
        }
        else if(d==2)
        {//x eat y
            if(x==y)
            {//false
                sum++;
                continue;
            }
            else
            {
                if(!eat(x,y))
                {
                    sum++;
                    continue;
                }
            }
        }
    }
    //ouput
    cout<<sum;
    return 0;
}
