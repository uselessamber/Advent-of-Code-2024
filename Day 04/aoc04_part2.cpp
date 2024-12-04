#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const char x_mas[3][3] = {
    {'M','.','S'},
    {'.','A','.'},
    {'M','.','S'}
};
vector<string> mp;
int R = 0, C = 0;

bool isInBound(int r, int c){
    return 0 <= r && r < R && 0 <= c && c < C;
}

bool match(int r, int c){
    if (!isInBound(r + 2, c + 2)) return false;
    bool matched = true;
    for (int idx = 0; idx < 9; idx += 1){
        char check0 = mp[r + idx / 3][c + idx % 3];
        char check1 = x_mas[idx / 3][idx % 3];
        if (check1 != '.' && check0 != check1){
            matched = false;
            break;
        }
    }
    if (matched) return true;
    matched = true;
    for (int idx = 0; idx < 9; idx += 1){
        char check0 = mp[r + idx / 3][c + idx % 3];
        char check1 = x_mas[idx % 3][2 - idx / 3];
        if (check1 != '.' && check0 != check1){
            matched = false;
            break;
        }
    }
    if (matched) return true;
    matched = true;
    for (int idx = 0; idx < 9; idx += 1){
        char check0 = mp[r + idx / 3][c + idx % 3];
        char check1 = x_mas[2 - idx / 3][2 - idx % 3];
        if (check1 != '.' && check0 != check1){
            matched = false;
            break;
        }
    }
    if (matched) return true;
    matched = true;
    for (int idx = 0; idx < 9; idx += 1){
        char check0 = mp[r + idx / 3][c + idx % 3];
        char check1 = x_mas[2 - idx % 3][idx / 3];
        if (check1 != '.' && check0 != check1){
            matched = false;
            break;
        }
    }
    if (matched) return true;
    return false;
}

int xmasfinder(){
    int total_xmas = 0;
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            total_xmas += match(r, c);
        }
    }
    return total_xmas;
}

int main(){
    ifstream fi("aoc04.inp");
    ofstream fo("aoc04.out");
    string tmp;
    if (!fi.is_open()){
        cerr << "What the fuck";
        return 0;
    }
    while (fi >> tmp){
        mp.push_back(tmp);
        C = max(C, (int)tmp.length());
        R++;
    }
    fo << xmasfinder();
}