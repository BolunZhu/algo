#include <iostream>
using namespace std;
const int M = 50000+5;
int a[M];
int b[M][2];
int c[M][3];
int n,k;
int sum=0;
int not_sure=0;
int find(int x)
{
    return a[x]==x ?  x:a[x]=find(a[x]);
    
}
int eat(int x,int y)
{
    // if(a[x]==-1&&a[y]==-1)
    // {
    //     a[x]=x;
    //     a[y]=y;
    //     b[x][0]=not_sure;
    //     b[x][1]=0;
    //     b[y][0]=not_sure;
    //     b[y][1]=1;
    //     c[not_sure][0]=x;
    //     c[not_sure][1]=y;
    //     not_sure++;
    //     return true;
    // }
    // if(a[x]==-1&&a[y]!=-1)
    // {
    //     int yroot=find(y);//yroot = y's root
    //     int y_bigset = b[yroot][0]; // y_bigset = name of bigset contain y 
    //     int x_kind = (b[yroot][1]+2)%3;// x_kind =  num of kind x should be when x belong to y's bigset
    //     if(c[y_bigset][x_kind]==-1)
    //     {
    //         c[y_bigset][x_kind]=x;
    //         b[x][0]=y_bigset;
    //         b[x][1]=x_kind;
    //         a[x]=x;
    //     }
    //     else
    //     {
    //         a[x]=c[y_bigset][x_kind];
    //     }
    //     return true;
    // }
    // if(a[x]!=-1&&a[y]==-1)
    // {
    //     int xroot=find(x);
    //     int x_bigset = b[xroot][0];
    //     int y_kind = (b[xroot][1]+1)%3;
    //     if(c[x_bigset][y_kind]==-1)
    //     {
    //         c[x_bigset][y_kind]=y;
    //         b[y][0]=x_bigset;
    //         b[y][1]=y_kind;
    //         a[y]=y;
    //     }
    //     else
    //     {
    //         a[y]=c[x_bigset][y_kind];
    //     }
    //     return true;
    // }
    //if a[x]!=-1 && a[y]!=-1
    int resx=find(x);
    int resy=find(y);
    if( b[resx][0]==b[resy][0])//in a same bigset
    {
        if( (b[resx][1]+1)%3==b[resy][1])//OK
        {//do nothing
            return true;
        }
        else
        {
            return false;
        }
    }
    for(int i=0;i<3;i++)
        {
            int yi=c[b[resy][0]][i];
            if(yi==-1)
            {
                //do nothing
            }
            else
            {
                int tmp=c[b[resx][0]][(i-b[resy][1]+b[resx][1]+7)%3];
                if(tmp==-1)
                {
                    // a[yi]=yi;
                    c[b[resx][0]][(i-b[resy][1]+b[resx][1]+7)%3]=yi;
                    b[yi][0]=b[resx][0];
                    b[yi][1]=(i-b[resy][1]+b[resx][1]+7)%3;
                }
                else
                {
                    a[yi]= a[tmp];
                }
                
            }
            
            
        }
        return true;
}
int uni(int x,int y)
{
    // if(a[x]==-1&&a[y]==-1)
    // {
    //     a[x]=x;
    //     a[y]=x;
    //     b[x][0]=not_sure;
    //     b[x][1]=0;
    //     c[not_sure][0]=x;
    //     not_sure++;
    //     return true;
    // }
    // if(a[x]==-1&&a[y]!=-1)
    // {
    //     a[x]=find(y);
    //     return true;
    // }
    // if(a[x]!=-1&&a[y]==-1)
    // {
    //     a[y]=find(x);
    //     return true;
    // }
    // a[x]!=-1 && a[y]!=-1
    int resx=find(x);
    int resy=find(y);
    if(b[resx][0]==b[resy][0])// if a & b in same big_set
    {
        if(b[resx][1]!=b[resy][1]){// but not same kind
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
            int yi=c[b[resy][0]][i];
            if(yi==-1)
            {
                //do nothing
            }
            else
            {
                int tmp=c[b[resx][0]][(i-b[resy][1]+b[resx][1]+6)%3];
                if(tmp==-1)
                {
                    // a[yi]=yi;
                    c[b[resx][0]][(i-b[resy][1]+b[resx][1]+6)%3]=yi;
                    b[yi][0]=b[resx][0];
                    b[yi][1]=(i-b[resy][1]+b[resx][1]+6)%3;
                }
                else
                {
                    a[yi]= a[tmp];
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
    for(int i=0;i<M;i++)
    {
        b[i][0]=i;
        b[i][1]=0;
    }
    for(int i=0;i<M;i++)
    {
        c[i][0]=i;
        c[i][1]=-1;
        c[i][2]=-1;
    }
    //input
    cin>>n>>k;
    for(int i = 0; i < k; i++)
    {
        int d,x,y;
        cin>>d>>x>>y;
    //solve
        if(!solve(d,x,y))
        {
            // cout<<"case"<<i<<": false\n";
            sum++;
        }
    }
    //ouput
    cout<<sum;
    return 0;
}
