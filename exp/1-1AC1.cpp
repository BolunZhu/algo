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
    if((Rank[y]+v-1+3)%3==Rank[x])
    //这里最大的问题是 Rank[y]指的是什么 
    //Rank[y]=1 在这里指的是根相对于y的偏移，此时1表示根相对于y后移一位，因此是y吃根
    //在AC2代码中指的是相对于根的偏移,此时1表示相对于根后移一位，因此是根吃y。 
    //两种关系都具有传递性 : a相对于c的偏移=a相对于b的偏移+ b相对于c的偏移 (AC2)
    //                    c相对于a的便宜=c相对于b的便宜+b相对于a的偏移  (AC1)
    {
        return true;
    }
    else{
        return false;
    }
}
father[a]=b;
//此时Rank[a]表示a和根节点的关系， 1表示a吃根 2表示被吃 0表示相同
Rank[a]=(v-1+Rank[y]-Rank[x]+3)%3;
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