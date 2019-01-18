#include<stdio.h>
#include<stack>
 
using namespace std;
const int N = 50000+5;
typedef long long LL;
int C[N+1];
stack<int> st;
bool vis[N];
int n,m;
int lowBit(int i){
	return i&(-i);
}
LL getSum(int i){
	LL ans = 0;
	while(i > 0){
		ans += C[i];
		i -= lowBit(i);
	}
	return ans;
}
void add(int i, int x){
	while(i <= N){
		C[i] += x;
		i += lowBit(i);
	}
}

 
int main()
	{
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; ++i){
			add(i,1);
		} 
		char c[5];
		int d;
		while(m--){
			scanf("%s",c);
			if(c[0] == 'D'){
				scanf("%d",&d);
				if(!vis[d]){
					add(d,-1);
					st.push(d);
					vis[d] = true;
				}
			}
			else if(c[0] == 'R'){
				if(!st.empty()){
					int t = st.top();
					st.pop();
					add(t,1);
					vis[t] = false;
				} 
			}
			else{			
				scanf("%d",&d);
				if(vis[d]){
					printf("0\n");
					continue;
				}
				int rs,re,l,r,t;
				l = d; r = n; 				
				while(l <= r){
					int mid = (l+r)/2;
					if(getSum(mid) - getSum(d-1) == mid-d+1){
						t = mid;
						l = mid+1;
					}
					else{
						r = mid-1;
					}
				}
				re = t;
				l = 1; r = d;
				while(l <= r){
					int mid = (l+r)/2;
					if(getSum(d) - getSum(mid-1) == d-mid+1){
						r = mid-1;
						t = mid;
					}
					else{
						l = mid+1;
					}
				}
				rs = t;
				printf("%d\n",re-rs+1);
			}	
		}
			
		return 0;
	}
