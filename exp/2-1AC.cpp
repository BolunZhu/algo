#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 100010;
int num;
//for dfs
int s[maxn],e[maxn];
bool vis[maxn];
//for tree
int c[maxn];
bool apple[maxn];
//
vector<vector<int > > v(maxn);
int n;
void dfs(int cur){
    s[cur]=++num; vis[cur]=true;
    for(int i=0;i<v[cur].size();i++){
        int u =v[cur][i];
        if(!vis[u])
            dfs(u);
    }
    e[cur]=num;
    return ;
}
int sum(int x){
    int res=0;
    while(x>0)
    {
      res+=c[x];  
      x-=(x&-x);
    }
    return res;
}
void update(int x){
    int d;
    if(apple[x]==true){//if exist then delete
      apple[x]=false;
      d=-1;
    }
    else{
       apple[x]=true;;
       d=1;
    }
    while(x<=n){
        c[x]+=d;  x+=(x&-x);
    }
}
 
int main(){
        int m,a,b;  
        char ch[10];
        //init
        memset(vis,false,sizeof(vis));
        memset(c,0,sizeof(c));
        //input tree
        scanf("%d",&n);
        for(int i=0;i<n-1;i++){
           scanf("%d %d",&a,&b);
           v[b].push_back(a);
           v[a].push_back(b);
        }
        scanf("%d",&m);

       num=0; 
       dfs(1);
       for(int i=1;i<=n;i++){
           update(i);
           apple[i]=true;
       }
       for(int kk=0;kk<m;kk++){
           scanf("%s",ch);
           scanf("%d",&a);
           if(ch[0]=='Q'){
               printf("%d\n",sum(e[a])-sum(s[a]-1));
           }
           else{
               update(s[a]);
           }
       }
    return 0;
 
}