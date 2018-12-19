//食物链AC代码2
#include <iostream>
#include <vector>
using namespace std;
const int maxn= 50010;
int father[maxn];
int Rank[maxn];
int n,m,sum=0;
int x,y,d;
int find(int v){
if(father[v]==v){
    return v;
}
else
{
    int tmp=father[v];
    father[v]=find(father[v]);
    Rank[v]=(Rank[tmp]+Rank[v])%3;
    return father[v];
}
}
bool merge(int x,int y , int v)
{
int a=find(x),b=find(y);
if(a==b){
    if( (Rank[x]+v-1+3)%3==Rank[y])
    {
        return true;
    }
    else{
        return false;
    }
}
father[b]=a;
//此时Rank[b]相当于b相对于a的偏移 偏移为1则b被a吃 偏移为2则b吃a
Rank[b]=(v-1+Rank[x]-Rank[y]+3)%3;// b=a+1 so a eat b
return true;
}
void init(int n){
        for(int i=1;i<=n;i++){
            father[i]=i;
            Rank[i]=0;
        }
    }
int main()
{
    
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d", &d, &x, &y);
        if(x>n||y>n||(d==2&&x==y)){
            sum++;
        }
        else{
            if(!merge(x,y,d))
            {
                sum++;
            }
        }
    }
    printf("%d\n",sum);
    return 0;
}