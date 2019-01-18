#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
struct ac
{
	int s,e,num;
}r[100010];
int x[100010];
int num[100010];
int cmp(ac q, ac w)
{
	if(q.e!=w.e)
	return q.e>w.e;
	return q.s<w.s;
}
int lowbit(int w)
{
	return w&-w;
}
int add(int w)
{
	while(w<=100010)
	{
		x[w]++;
		w+=lowbit(w);
	}
}
int sum(int w)
{
	int ans=0;
	while(w>0)
	{
		ans+=x[w];
		w-=lowbit(w);
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);//否则超时
	int t;
	while(cin>>t)
	{
		if(t==0)
		break;
		memset(x,0,sizeof(x));
		memset(num,0,sizeof(num));
		for(int i=0;i<t;i++)
		{
			cin>>r[i].s>>r[i].e;
			r[i].num=i;
		}
		sort(r,r+t,cmp);
		for(int i=0;i<t;i++)
		{
			if(r[i].s==r[i-1].s&&r[i].e==r[i-1].e)
			{
				num[r[i].num]=num[r[i-1].num];//因为最多只能覆盖一个点
				// 所以当两端相同的时候 直接让其值与上一个相等 
			}
			else
			{
				num[r[i].num]=sum(r[i].s+1);
			
			}
			add(r[i].s+1);// 要再这里进行 add 
		}
		cout<<num[0];
		for(int i=1;i<t;i++)
		{
			cout<<" "<<num[i];
		}
		cout<<endl;
	}
	return 0;
}
