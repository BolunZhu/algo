#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int  N=100000+10;
struct Node{
    int l, r, ls, rs, sum;
}tree[N<<5]; 
int rt[N], a[N], b[N], pos, cnt;
void build( int &nd, int l, int r ){
    nd=++cnt;
    tree[nd].l=l, tree[nd].r=r;
    if( l==r ) return ;
    int mid=(l+r)>>1;
    //×óÓÒ¶þ·Ö
    build(tree[nd].ls,l,mid);
    build(tree[nd].rs,mid+1,r); 
}
void insert( int pre, int &nd ){
    nd=++cnt;
    tree[nd]=tree[pre];
    tree[nd].sum++;
    int mid=(tree[nd].l+tree[nd].r)>>1;
    if( tree[nd].l==tree[nd].r ) return;
    if( mid>=pos ) insert(tree[pre].ls,tree[nd].ls);
    else insert(tree[pre].rs,tree[nd].rs); 
}
int query( int pre, int nd, int k ){
    if( tree[nd].ls==tree[nd].rs ) return b[tree[nd].l];
    int cmp=tree[tree[nd].ls].sum-tree[tree[pre].ls].sum;
    if( cmp>=k ) return query(tree[pre].ls,tree[nd].ls,k);
    else return query(tree[pre].rs,tree[nd].rs,k-cmp);
}
int main(){
    int n, m;
    scanf("%d%d", &n, &m );
    for ( int i=1; i<=n; b[i]=a[i], i++ ) scanf("%d", &a[i] );
    cnt=0;
    sort(b+1,b+n+1);
    build(rt[0],1,n);
    for ( int i=1; i<=n; i++ ){
        pos=lower_bound(b+1,b+1+n,a[i])-b;
        insert(rt[i-1],rt[i]); 
    }
    for(int i=0;i<m;i++){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k );
        printf("%d\n", query(rt[l-1],rt[r],k) ); 
    }
    return 0;
}