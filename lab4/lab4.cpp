#include <iostream>
#include <math.h>
using namespace std;
//point ���ݽṹ
typedef struct Point{
    double x;
    double y;
} point;
//ȫ�ֱ�������
    static const int maxn=100000;
    point a[maxn];
    int n,s[maxn];
//������������
    bool cmpx(int i,int j){ return (a[i].x-a[j].x)<0; }
    bool cmpy(int i,int j){ return (a[i].y-a[j].y)<0; }
    double norm(point a,point b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y); }
//�ݹ麯��
double min_dist(point a[],int s[],int l , int r ){
    double ans=1e100;
    if(r-l<4){
        
        for(int i = l; i < r; i++)
        {
            
            for(int j = i+1; j < r; j++)
            {
                ans=min(ans,norm(a[s[i]],a[s[j]]));
            }
            
        }
        return ans;
    }
    int tl,tr,m=(l+r)/2;
    ans = min(min_dist(a,s,l,m),min_dist(a,s,m,r));
    for(tl=l;a[s[tl]].x<a[s[m]].x-ans;tl++);
    for(tr=r-1;a[s[tr]].x>a[s[m]].x+ans;tr++);
    sort(s+tl,s+tr,cmpy);
    for(int i = tl; i < tr; i++)
    {
        
        for(int j = i+1; j < min(tr,i+6); j++)
        {
            ans=min(ans,norm(a[s[i]],a[s[j]]));
        }
    }
    sort(s+tl,s+tr,cmpx);
    return ans;
}
//�ⲿ�ӿں���
// a ���е������
// s ���е㰴x���������ı��
// n ��ĸ���
double Min_Dist(point a[],int s[],int n){
    
    for(int i = 0; i < n; i++)
    {
        s[i]=i;
    }
    sort(s,s+n,cmpx);//Ԥ����
    return min_dist(a,s,0,n);
}

int main(){
    int n=0;
    while(scanf("%d",&n)&&n>1){
        for(int i=0;i<n;i++){
            scanf("%lf%lf",&(a[i].x),&(a[i].y));
        }
        printf("%lf\n",sqrt(Min_Dist(a,s,n)) );
    }
    
}