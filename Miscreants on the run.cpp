/*
The college authorities is fed up of a few miscreants. They are running away from the authorities. The college authorities wants to catch them on run. They are developing a computer system, which will help them catch these miscreants.
The college is made up N blocks, numbered from 1 to N, and E stairs connecting them. Looking at map of college, they want to determine where to keep the stair blocks. The computer system has to answer queries:
1. Given two blocks, A and B, and one stair connecting blocks P and Q. The system has to answer whether the miscreants can get from A to B if the given stair is closed and they can't use it.
2. Given three blocks, A, B and C. Can the miscreants can get from block A to block B, it they can't use or enter block C.
You have to implement such system.
Input Format:
The first line of input contains contains two integers N and E (1 <= N <= 100000 and 1<= E <= 500000), that denote the value of number  of blocks and stairs. 
Each of the following E lines contain two distinct integers between 1 and N - numbers of two blocks connected by a stair. There will be at most one stair between any pair of blocks. 
The following Q lines contains queries (1 <= Q <= 300000). Each of the queries contain four or five integers. The first of these integers is the type of query - 1 or 2. If the query is of type 1, then same line contains four more integers: A, B, P and Q. A and B will represent different blocks and P and Q will be an existing stair. 
If the query is of type 2, then the same line contains three more integers: A, B and C. A, B and C will be distinct integers.
The test cases will be such that it is initially possible to go from each block to every other block. 
Constraints:
Time Limit: 3 seconds
Output format:
For each query, output the answers, one per line. The answer to a query can be "yes" or "no" 
Sample Input 1:
13 15
1 2
2 3
3 5
2 4
4 6
2 6
1 4
1 7
7 8
7 9
7 10
8 11
8 12
9 12
12 13
5
1 5 13 1 2
1 6 2 1 4
1 13 6 7 8
2 13 6 7
2 13 6 8 
Sample Output 1:
yes
yes
yes
no
yes 
*/

#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pb push_back
#define FILL(a, b) memset(a, b, sizeof(a))
typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
const int INF = 0x3F3F3F3F;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;
const int MAXL = 17;
int N, M, Q;
vi adj[MAX];
int dfn[MAX], low[MAX], out[MAX];
bool vis[MAX];
int par[MAX], depth[MAX];
int cnt = 0;
int dp[MAX][MAXL + 1];
void tarj(int u, int prev) {
dfn[u] = low[u] = ++cnt;
vis[u] = true;
for (int v : adj[u]) {
if (!vis[v]) {
par[v] = u;
depth[v] = depth[u] + 1;
tarj(v, u);
low[u] = min(low[u], low[v]);
} else if (v != prev && dfn[v] < dfn[u]) {
low[u] = min(low[u], dfn[v]);
}
}
out[u] = cnt;
}
bool desc(int u, int v) {
return dfn[u] >= dfn[v] && out[u] <= out[v];
}
int anc(int u, int d) {
int n = MAXL;
while (d) {
if (d - (1 << n) >= 0) {
u = dp[u][n];
d -= 1 << n;
} else {
n--;
}
}
return u;
}
int main() {
scanf("%d%d", &N, &M);
int t, a, b, c, d;
while (M--) {
scanf("%d%d", &a, &b);
adj[a].pb(b);
adj[b].pb(a);
}
tarj(1, -1);
FILL(dp, -1);
for (int i = 1; i <= N; i++) {
dp[i][0] = par[i];
}
for (int j = 1; (1 << j) < N; j++) {
for (int i = 1; i <= N; i++) {
if (dp[i][j - 1] != -1) {
dp[i][j] = dp[dp[i][j - 1]][j - 1];
}
}
}
scanf("%d", &Q);
while (Q--) {
scanf("%d", &t);
if (t == 1) {
scanf("%d%d%d%d", &a, &b, &c, &d);
if (dfn[c] < dfn[d]) {
swap(c, d);
}
printf(low[c] <= dfn[d] || desc(a, c) == desc(b, c) ? "yes\n" : "no\n");
} else {
scanf("%d%d%d", &a, &b, &c);
bool ac = desc(a, c), bc = desc(b, c);
if (!ac && !bc) {
printf("yes\n");
} else if (ac && bc) {
int p1 = anc(a, depth[a] - depth[c] - 1);
int p2 = anc(b, depth[b] - depth[c] - 1);
printf(p1 == p2 || (low[p1] < dfn[c] && low[p2] < dfn[c]) ? "yes\n" : "no\n");
} else {
if (!ac) {
swap(a, b);
}
int p = anc(a, depth[a] - depth[c] - 1);
printf(low[p] < dfn[c] ? "yes\n" : "no\n");
}
}
}
return 0;
}
