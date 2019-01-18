#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,o,a,x;
struct node
{
  int l,r;
  int lsum,rsum,sum,p;
}seg[200010];
 
void buildtree(int no,int l,int r) //建立线段树
{
  int mid=(l+r)/2;
  seg[no].l=l;seg[no].r=r;
  seg[no].sum=seg[no].lsum=seg[no].rsum=r-l+1;
  seg[no].p=-1;
  if (l!=r)
  {
	buildtree(2*no,l,mid);
	buildtree(2*no+1,mid+1,r);
  }
}
 
void pushdown(int no) //将节点no的标记下放
{
  if (seg[no].p!=-1)
  {
    seg[2*no].p=seg[2*no+1].p=seg[no].p;
    if (!seg[2*no].p)
	{
	  seg[2*no].lsum=seg[2*no].rsum=seg[2*no].sum=0;
	  seg[2*no+1].lsum=seg[2*no+1].rsum=seg[2*no+1].sum=0;
	}
	else
	{
	  seg[2*no].lsum=seg[2*no].rsum=seg[2*no].sum=seg[2*no].r-seg[2*no].l+1;
	  seg[2*no+1].lsum=seg[2*no+1].rsum=seg[2*no+1].sum=seg[2*no+1].r-seg[2*no+1].l+1;
	}
	seg[no].p=-1;
  }
}
 
void pushup(int no) //用更新后的no的儿子的数值来更新节点no
{
  seg[no].lsum=seg[2*no].lsum;
  seg[no].rsum=seg[2*no+1].rsum;
  if (seg[2*no].lsum==seg[2*no].r-seg[2*no].l+1) seg[no].lsum+=seg[2*no+1].lsum;
  if (seg[2*no+1].rsum==seg[2*no+1].r-seg[2*no+1].l+1) seg[no].rsum+=seg[2*no].rsum;
  seg[no].sum=max(max(seg[2*no].sum,seg[2*no+1].sum),seg[2*no].rsum+seg[2*no+1].lsum);
}
 
int query(int no,int a) //查询并返回标号最小的长度为a的连续空区间的左端点标号
{
  int mid=(seg[no].l+seg[no].r)/2;
  if (seg[no].l==seg[no].r) return seg[no].l;
  pushdown(no);
  if (seg[2*no].sum>=a) return query(2*no,a);
  if (seg[2*no].rsum+seg[2*no+1].lsum>=a) return mid-seg[2*no].rsum+1;
  if (seg[2*no+1].sum>=a) return query(2*no+1,a);
  return -1;
}
 
void checkin(int no,int s,int t) //将区间（s,t）覆盖
{
  int mid=(seg[no].l+seg[no].r)/2;
  if (seg[no].l>=s&&seg[no].r<=t)
  {
    seg[no].lsum=seg[no].rsum=seg[no].sum=0;
	seg[no].p=0;
	return;
  }
  pushdown(no);
  if (s<=mid) checkin(2*no,s,t);
  if (t>mid) checkin(2*no+1,s,t);
  pushup(no);
}
 
void checkout(int no,int s,int t) //清空区间（s,t）
{
  int mid=(seg[no].l+seg[no].r)/2;
  if (seg[no].l>=s&&seg[no].r<=t)
  {
    seg[no].lsum=seg[no].rsum=seg[no].sum=seg[no].r-seg[no].l+1;
	seg[no].p=1;
    return;
  }
  pushdown(no);
  if (s<=mid) checkout(2*no,s,t);
  if (t>mid) checkout(2*no+1,s,t);
  pushup(no);
}
 
int main()
{
  scanf("%d %d",&n,&m);
  buildtree(1,1,n);
  for(int i=1;i<=m;i++)
  {
    scanf("%d",&o);
	if (o==1)
	{
	  scanf("%d",&a);
	  if (seg[1].sum<a) printf("0\n"); //如果没有那么长的连续空区间，输出0
	  else
	  {
	    int f=query(1,a);
		printf("%d\n",f);
		checkin(1,f,f+a-1);
	  }
	}
	if (o==2)
	{
	  scanf("%d %d",&a,&x);
	  checkout(1,a,a+x-1);
	}
  }
  
  return 0;
}