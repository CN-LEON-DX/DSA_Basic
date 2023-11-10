#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fore(i,b,a) for(int i = b; i<a; i++)
#define null NULL
#define nl '\n'
#define yes "YES\n"
#define no "NO\n"
using namespace std;

string slove(string s){
    stack<char> st;
    string result = "";
    for (int i=0; i<s.size(); i++){
        if (s[i] == '('){
            st.push(s[i]);
        }
        else if (isdigit(s[i])){
            result += s[i];
            result += " ";
        }else if (s[i]==')'){
            if (st.top() != '('){
                result += st.top();
                result += " ";
                st.pop(); st.pop();
            }
        }else st.push(s[i]);
    }
    return result;
}
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0); cin.tie(0);
    ll t = 1;
    string str="((3+4)*(2-6))*(8-9)";//-> 3 4 + 2 6 - *
    while (t--){
    	cout << slove(str);
    }
}