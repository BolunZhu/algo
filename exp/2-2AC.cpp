#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
#define l64 long long
 
struct node
{
    l64 f,x;
} s[20010];
 
bool cmp(node a,node b)
{
    return a.f<b.f;
} 
 
int n;
l64 c1[20010],c2[20010];
 
l64 lowbit(l64 k)
{
    return k&(-k);//������ĩβ�� 1 ��ʮ������
}
 
void add1(l64 k,l64 num)
{
    while (k<20010)
    {
        c1[k]+=num;
        k+=lowbit(k);
    }
}
 
void add2(l64 k,l64 num)
{
    while (k<20010)
    {
        c2[k]+=num;
        k+=lowbit(k);
    }
}
 
l64 sum1(l64 k)
{
    l64 sm=0;
    while (k)
    {
        sm+=c1[k];
        k-=lowbit(k);
    }
    return sm;
}
 
l64 sum2(l64 k)
{
    l64 sm=0;
    while (k)
    {
        sm+=c2[k];
        k-=lowbit(k);
    }
    return sm;
}
 
int main()
{
    while (~scanf("%d",&n))
    {
        for (int i=1; i<=n; i++)
        {
            scanf("%lld%lld",&s[i].f,&s[i].x);
        }
        memset(c1,0,sizeof(c1));
        memset(c2,0,sizeof(c2));
        sort(s+1,s+n+1,cmp);
        l64 ans=0;
        for (int i=1; i<=n; i++)
        {
            add1(s[i].x,1);
            add2(s[i].x,s[i].x);//ά��������������
            l64 nn=sum1(s[i].x);//����
            l64 sss=sum2(s[i].x);//����
            ans+=(nn*s[i].x-sss)*s[i].f;//�õ������ڵ�ǰxǰ����������С������ţ
            l64 nnn=i-nn;
            l64 ss=sum2(20000)-sss;//�ܹ��ļ�ȥ�ȽϽ��ĵ��ڱȽ�Զ��
            ans+=(ss-s[i].x*nnn)*s[i].f;//����ǰ��ı�������ֵ���x
 
        }
        printf ("%lld\n",ans);
    }
    return 0;
}
