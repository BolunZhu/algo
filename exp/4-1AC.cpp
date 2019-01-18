#include <iostream> 
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1005;
vector<int> vec[N];
bool vis[N];
bool is_root[N];
int ans[N];
int father[N];
int ask[N][N];
 
int n, m, root;
 
 
void init_data(){
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) ask[i][j] = 0;
	for(int i=1; i<=n; ++i){
		vis[i] = false;
		is_root[i] = true;
		father[i] = i;
		ans[i] = 0;
		vec[i].clear();
	}
}
int Find(int x){
	if(x == father[x]){
		return x;
	}else{
		return father[x] = Find(father[x]);
	}
}
void show_is_root(){
	for(int i=1; i<=n; ++i){
		if(is_root[i] == true){
			printf("%4d",1);
		}else{
			printf("%4d",0);
		}
	}
	printf("\n");
}
void LCA(int root){
	for(int i=1; i<=n; ++i){		
		if(vis[i] && ask[root][i]){
			ans[Find(i)] += ask[root][i];
		}
	}
	vis[root] = true;	
	for(int i=0; i<vec[root].size(); ++i){
		int temp = vec[root][i];
		LCA(temp);
		father[temp] = root;
	}
	
}
 
int main(){
	int a,b,c;	
	while( ~scanf("%d", &n) ){		
		init_data();
				
		for(int i=1; i<=n; ++i){
			scanf("%d:(%d)", &a, &b);
			for(int i=1; i<=b; ++i){
				scanf("%d", &c);				
				is_root[c] = false;
				vec[a].push_back(c);
			}
		}		
		for(int i=1; i<=n; ++i){
			if(is_root[i]){
				root = i;
				break;
			}
		}
		scanf("%d", &m);
		for(int i=1; i<=m; ++i){
			scanf(" (%d %d)", &a, &b);
			ask[a][b]++;
			ask[b][a]++;
		}
				
		LCA(root);
		
		for(int i=1; i<=n; ++i){
			if(ans[i]){
				printf("%d:%d\n", i, ans[i]);
			}
		}
	}	
	return 0;
}