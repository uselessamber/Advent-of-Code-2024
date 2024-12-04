#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const int dr[8] = { 0,  1,  1,  1,  0, -1, -1, -1};
const int dc[8] = { 1,  1,  0, -1, -1, -1,  0,  1};
vector<string> mp;
int R = 0, C = 0;

bool isValidDir(int cr, int cc, int dir, int mag){
    int nr = cr + dr[dir] * mag;
    int nc = cc + dc[dir] * mag;
    return (0 <= nr) && (nr < R) && (0 <= nc) && (nc < C);
}

bool extract(int r, int c, int dir, string &output){
    output = "";
    if (!isValidDir(r, c, dir, 3)) return false;
    for (int i = 0; i < 4; i++){ 
        output = output + mp[r + dr[dir] * i][c + dc[dir] * i];
    }
    return true;
}

int search(int r, int c){
    int xmasfound = 0;
    if (mp[r][c] != 'X') return xmasfound;
    for (int dir = 0; dir < 8; dir++){
        string check = "";
        if (extract(r, c, dir, check)){
            if (check == "XMAS"){
                xmasfound++;
            }
        }
    }
    return xmasfound;
}

int xmasfinder(){
    int total_xmas = 0;
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            total_xmas += search(r, c);
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