/*
A student called Slon is very mischievous in school. He is always bored in class and he is always making a mess. The teacher wanted to calm him down and “tame” him, so he has given him a difficult mathematical problem.
The teacher gives Slon an arithmetic expression A, the integer P and M. Slon has to answer the following question: “What is the minimal non-negative value of variable x in expression A so that the remainder of dividing A with M is equal to P?”. The solution will always exist.
Additionally, it will hold that, if we apply the laws of distribution on expression A, variable x will not multiply variable x (formally, the expression is a polynomial of the first degree in variable x).
Examples of valid expressions A: 5+x∗(3+2), x+3∗x+4∗(5+3∗(2+x−2∗x)).
Examples of invalid expressions A: 5∗(3+x∗(3+x)), x∗(x+x∗(1+x)).
Input Format:
The first line of input contains the expression A.
The second line of input contains two integers P and M.
The arithmetic expression A will only consists of characters +, -, *, (, ), x and digits from 0 to 9.
The brackets will always be paired, the operators +, - and * will always be applied to exactly two values (there will not be an expression (-5) or (4+-5)) and all multiplications will be explicit (there will not be an expression 4(5) or 2(x)).
*/

#include <bits/stdc++.h>
#define vec vector
#define sz(c) int(c.size())
#define FOR(i, a, b) for (int i = a; i < (b); ++i)
#define DOWN(i, a, b) for(int i = (a) - 1; i >= (b); --i)
#define cerr2 cerr << __func__ << ":" << __LINE__ << ": "
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef vec<int> vi;
typedef tuple<int,int,int> tiii;
const char eol = '\n';
int M, P;
struct num {
int value;
num() {}
num(ll _value): value(int(_value % M)) {}
num operator+(const num &other) const { return num(value + other.value); }
num operator-(const num &other) const { return num(value + M - other.value); }
num operator*(const num &other) const { return num(ll(value) * other.value); }
int operator()() const { return value; }
};
struct val {
num a;
num b;
val() {}
val(num _a, num _b): a(_a), b(_b) {}
val operator+(const val &other) const { return val(a + other.a, b + other.b); }
val operator-(const val &other) const { return val(a - other.a, b - other.b); }
val operator*(const val &other) const {
if (a.value == 0) {
return val(other.a * b, other.b * b);
}
else if (other.a.value == 0) {
return val(a * other.b, b * other.b);
}
else {
assert(false);
}
}
num operator()(int x) const {
return a * x + b;
}
};
ostream& operator<<(ostream &os, const val &v) {
os << "(";
if (v.a() != 1 && v.a() != 0) os << v.a();
if (v.a() != 0) os << "x";
if (v.a() != 0 && v.b() != 0) os << "+";
if (v.a() == 0 || v.b() != 0) os << v.b();
os << ")";
return os;
}
struct token {
char op;
val value;
token(char _op): op(_op) {}
token(char _op, val _value): op(_op), value(_value) {}
};
bool is_op(char c) {
return c == '+' || c == '-' || c == '*';
} 
int op_pr(char c) {
// cerr << c << endl;
if (c == '+' || c == '-') return 0;
if (c == '*') return 1;
assert(c == '(');
return -1;
}
vec<token> build_rpn(string s) {
stack<char> ops;
vec<token> rpn;
#define pop_op(rpn, ops, vals) \
FOR(i, 0, sz(s)) {
char c = s[i];
if (c == '(') {
ops.push(c);
}
else if (c == ')') {
while (ops.top() != '(') {
rpn.push_back(token(ops.top()));
ops.pop();
}
ops.pop();
}
else if (is_op(c)) {
while (!ops.empty() && op_pr(c) < op_pr(ops.top())) {
rpn.push_back(token(ops.top()));
ops.pop();
}
ops.push(c);
}
else if (c == 'x') {
rpn.push_back(token(0, val{1, 0}));
}
else {
assert(isdigit(c));
val tmp{0, 0};
while (i < sz(s) && isdigit(s[i])) {
tmp.b = tmp.b * 10 + int(s[i]) - '0';
i += 1;
}
i -= 1;
rpn.push_back(token(0, tmp));
}
}
while (!ops.empty()) {
rpn.push_back(ops.top());
ops.pop();
}
#undef pop_op
return rpn;
}
val eval(string s) {
vec<token> rpn = build_rpn(s);
stack<val> vals;
for (token t : rpn) {
if (t.op == 0) {
vals.push(t.value);
continue;
}
val b = vals.top(); vals.pop();
val a = vals.top();
vals.pop();
switch (t.op) {
case '+':
// cerr << a << " + " << b << " = " << (a + b) << endl;
vals.push(a + b);
break;
case '-':
// cerr << a << " - " << b << " = " << (a - b) << endl;
vals.push(a - b);
break;
case '*':
// cerr << a << " * " << b << " = " << (a * b) << endl;
vals.push(a * b);
break;
}
}
assert(sz(vals) == 1);
return vals.top();
}
tiii pulv(int a, int b) {
if (a == 0) return tiii{b, 0, 1};
int d, x0, y0;
tie(d, y0, x0) = pulv(b % a, a);
int x = x0 - b/a * y0;
int y = y0;
return tiii{d, x, y};
}
num mod_inv(int x) {
int d, a, b;
tie(d, a, b) = pulv(x, M);
assert(d == 1);
return num((a + M) % M);
}
int main() {
ios_base::sync_with_stdio(false);
cin.tie(0);
cout << fixed << setprecision(10);
#ifdef STRESS
srand(int(time(0)));
while (true) stress();
return 0;
#endif
string s;
cin >> s;
cin >> P >> M;
val t = eval(s);
// cerr << t << endl;
FOR(x, 0, M) {
if (t(x)() == P) {
cout << x << endl;
break;
}
} 
  return 0;
}
int const max_val = 5;
int const max_tokens = 5;
string const ops = "+-*";
