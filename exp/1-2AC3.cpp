//Parity game AC1
//odd �� even ż
#include <iostream>
#include <map>
using namespace std;
const int maxn=10000+5;
int len;
int n;
int x,y;
char str[6];
int f[maxn];
int r[maxn];
int nextnum=0;
map <int,int> m;
int res=0;
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
        //�����и��� Ҫ����fx ��fy�Ĵ�С
        //��ʵû�п� fx��fy�Ĵ�С������Ҳû�й�ϵ ���˱���һ������ Ҳ�ж�Ӧ�����塣
         // r[fx]+r[x]+v= r[fy]+r[y]
            f[fx]=fy;
            r[fx]=(r[y]-r[x]-v+4)%2;
        return true;
    }
} 
void init(){
    //��һ��������bug���� ����������Ϊmaxn ��ôԽ����ʲ�һ���ᱬ�� ���Ǹ�WA��
    for(int i=0;i<maxn;i++)
    {
        f[i]=i;
        r[i]=0;
    }
}
int main(){
    scanf("%d%d",&len,&n);
    m.clear();
    init();
    pair<map<int, int>::iterator, bool> Insert_Pair;
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%s",&x,&y,str);
        Insert_Pair = m.insert(pair<int,int>(x,nextnum));
        nextnum++;
        Insert_Pair = m.insert(pair<int,int>(y+1,nextnum));
        nextnum++;
        int v = (str[0]=='o');
        if(merge(m[x],m[y+1],v))
        {
            res++;
        }
        else
        {
            break;
        }
    }
    printf("%d\n",res);
    return 0;
}