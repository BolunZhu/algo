//True Liars
// n p1 p2 p1=good_divine p2=bad_devilish
// n<=1000 p1 p2 <= 300
#include <iostream>

const int maxn=600+10;
int f[maxn];
int r[maxn];
int n,p1,p2;
int num_tree;
int find(int v){
    if(f[v]==v)
    {
        return v;
    }
    else{
        int tmp=f[v];
        f[v]=find(f[v]);
        r[v]=(r[v]+r[tmp])%2;
        return f[v];
    }
}
bool merge(int x,int y , int v){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy)
    {
        if(r[y]==(r[x]+v)%2 )
        {
            return true;
        }
        {
            return false;
        }
    }
    else
    {//merge them
    //r[i]表示 如果i的父亲是真=0 则 i是r[i]
         // r[fx]+r[x]+v= r[fy]+r[y]
        f[fy]=fx;
        r[fy]=(v+r[x]-r[y]+2)%2;
        return true;
    }
} 
void init(){
    //有一个致命的bug在于 如果你的数组为maxn 那么越界访问不一定会爆错 而是给WA！
    num_tree=maxn;
    for(int i=0;i<maxn;i++)
    {
        f[i]=i;
        r[i]=0;//0 true 1 liar
    }
}
int main(){
    while(scanf("%d%d%d",&n,&p1,&p2)==3&&n)
    {
        // if ok print num & end
        // else print no
    }
    return 0;
}