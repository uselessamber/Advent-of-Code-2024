#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;

map <pli, bool> dp;
int n;
ll target;
vector<ll> a;
ll result = 0;

bool dpf(ll curr, int pos){
    if (dp.find(pli(curr, pos)) != dp.end()) return dp[pli(curr, pos)];
    if (pos >= n){
        if (curr == target) return dp[pli(curr, pos)] = true;
        else return dp[pli(curr, pos)] = false;
    }
    if (curr > target) dp[pli(curr, pos)] = false;
    return dp[pli(curr, pos)] = dpf(curr + a[pos], pos + 1) || dpf(curr * a[pos], pos + 1);
}

int main(){
    ifstream fi("aoc07.inp");
    ofstream fo("aoc07.out");
    string temp;

    while (fi >> temp){
        temp.erase(temp.end() - 1);
        target = stoll(temp);

        getline(fi, temp);
        stringstream ss;
        ss << temp;
        ll choice;

        while (ss >> choice){
            a.push_back(choice);
        }
        n = (int)a.size();

        if (dpf(a[0], 1)){
            result += target;
        }

        a.clear();
        dp.clear();
    }
    fo << result;
}