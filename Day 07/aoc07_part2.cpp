#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const bool debug = false;

enum state{
    visited_left,
    visited_right
};

map <pli, state> dp;
int n;
ll target;
vector<ll> a;
ll result = 0;

ll concat(ll a, ll b){
    ll ans = 0;
    string sa = to_string(a);
    string sb = to_string(b);
    return stoll(sa + sb);
}

ll f(int type, ll a, ll b){
    switch (type){
        case 0:
            return a + b;
        case 1:
            return a * b;
        case 2:
            return concat(a, b);
    }
    return -1;
}

ll split(ll a, ll b){
    if (a < b) return -1;
    ll temp = 0;
    int d = 1;
    while (temp < b){
        temp += (a % 10) * d;
        a /= 10;
        d *= 10;
    }
    if (temp == b){
        return a;
    }
    return -1;
}

ll _f(int type, ll a, ll b){
    switch (type){
        case 0:
            return a - b;
        case 1:
            if (a % b == 0)
                return a / b;
            else
                return -1;
        case 2:
            return split(a, b);
    }
    return -1;
}

bool meet_in_the_middle(){
    queue <pli> qleft;
    qleft.push(pli(a[0], 1));
    dp[pli(a[0], 1)] = visited_left;
    queue <pli> qright;
    qright.push(pli(target, n));
    dp[pli(target, n)] = visited_right;
    int middle = n / 2;

    while (!qleft.empty() || !qright.empty()){
        // Left side
        pli current_state;

        if (!qleft.empty()){
            current_state = qleft.front();
            qleft.pop();
            if (debug) cerr << " left> total: " << current_state.first << " | pos: " << current_state.second << "\n";

            if (current_state.second < middle){
                for (int i = 0; i < 3; i++){
                    ll next_running_total = f(i, current_state.first, a[current_state.second]);
                    if (next_running_total > target) continue;
                    pli next_state = pli(next_running_total, current_state.second + 1); 

                    if (dp.find(next_state) == dp.end()){
                        dp[next_state] = visited_left;
                        qleft.push(next_state);
                    }else if (dp[next_state] == visited_right){
                        return true;
                    }
                }
            }
        }

        // Right side

        if (!qright.empty()){
            current_state = qright.front();
            qright.pop();
            if (debug) cerr << "right> total: " << current_state.first << " | pos: " << current_state.second << "\n";

            if (current_state.second > middle){
                for (int i = 0; i < 3; i++){
                    ll next_running_total = _f(i, current_state.first, a[current_state.second - 1]);
                    if (next_running_total <= 0) continue;
                    pli next_state = pli(next_running_total, current_state.second - 1); 

                    if (dp.find(next_state) == dp.end()){
                        dp[next_state] = visited_right;
                        qright.push(next_state);
                    }else if (dp[next_state] == visited_left){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main(){
    ifstream fi("aoc07.inp");
    ofstream fo("aoc07.out");
    string temp;

    int test_case = 0;

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

        if (debug) cerr << "test_case_" << test_case << ": \n";
        if (meet_in_the_middle()){
            if (debug) cerr << target << " reached\n";
            result += target;
        }
        test_case += 1;

        a.clear();
        dp.clear();
    }
    fo << result;
}