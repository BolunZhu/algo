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
    //�������������� Rank[y]ָ����ʲô 
    //Rank[y]=1 ������ָ���Ǹ������y��ƫ�ƣ���ʱ1��ʾ�������y����һλ�������y�Ը�
    //��AC2������ָ��������ڸ���ƫ��,��ʱ1��ʾ����ڸ�����һλ������Ǹ���y�� 
    //���ֹ�ϵ�����д����� : a�����c��ƫ��=a�����b��ƫ��+ b�����c��ƫ�� (AC2)
    //                    c�����a�ı���=c�����b�ı���+b�����a��ƫ��  (AC1)
    {
        return true;
    }
    else{
        return false;
    }
}
father[a]=b;
//��ʱRank[a]��ʾa�͸��ڵ�Ĺ�ϵ�� 1��ʾa�Ը� 2��ʾ���� 0��ʾ��ͬ
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