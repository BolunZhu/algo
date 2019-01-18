#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000000+5;
int next[maxn];
char input[maxn];

//kmp solve
void solve(char *s) {
    int len = strlen(s);
    int j = 0, k = -1;
    next[0] = -1;
    while(j < len) {
        if(k == -1 || s[j] == s[k]) {
            j++;
            k++;
            next[j]  = k;
        } else {
            k = next[k];
        }
    }
}
int main() {
    while(gets(input) ) {
        if(strcmp(input,".") == 0) {
            return 0;
        }
        solve(input);
        int len = strlen(input);
        int ans = 1;
        if(len % (len - next[len]) == 0) {
            ans = len / (len - next[len]);
        }
        printf("%d\n", ans);
    }
    return 0;
}