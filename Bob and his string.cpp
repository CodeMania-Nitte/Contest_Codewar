/*King Bob is in playful mood today. He started playing with string S. As he was playing, a weird question came in his mind. He wondered what is the maximum number of characters, between any two same characters in the string. He needs your help in solving this question. Can you help him solve this question?
Note: String S is composed of lowercase letters of the Latin alphabet. If there are no two same characters in the string, print -1.
Input Format:
The first line of input contains one integer T, denoting the number of test cases. 
Each of the next T line contains one string S.
Constraints:
1 < T < 10
1 < |S| < 100000, where S determines the length of the string.
String is composed of lowercase alphabets ranging from a to z.
Time limit : 1 sec
Output Format:
For each test case, output the maximum number of characters between any two same characters in the string. If there are no two same characters in the string, print -1. 
Print answer for each test case in a new line.*/

#include <bits/stdc++.h>
using namespace std;
void solve()
{
string s;
cin >> s;
int firstPos[50], res = -1;
for(char q = 'a'; q <= 'z'; ++q)
firstPos[q - 'a'] = -1;
for(int i = 0; i < s.size(); ++i)
if(firstPos[s[i] - 'a'] == -1)
firstPos[s[i] - 'a'] = i;
else
res = max(res, i - firstPos[s[i] - 'a'] - 1);
cout << res << '\n';
}
int main()
{
int t;
cin >> t;
while(t --> 0)
solve();
}
