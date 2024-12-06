#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
using namespace std;

const int dr[4] = {-1,  0,  1,  0};
const int dc[4] = { 0,  1,  0, -1};

vector<string> mp;
vector<vector<vector<bool>>> visit;
vector<vector<bool>> blockmap;
int R = 0, C = 0;
int sr, sc, sd;

bool in_bound(int r, int c){
    return (0 <= r && r < R) && (0 <= c && c < C);
}

bool wall_check(int row, int col, int dir){
    return in_bound(row + dr[dir], col + dc[dir]) && mp[row + dr[dir]][col + dc[dir]] == '#';
}

typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;

bool theoretical_step(int row, int col, int dir, int w_row, int w_col){
    if (!in_bound(row, col)) return false;
    if (visit[row][col][dir]) return true;
    visit[row][col][dir] = true;
    if (!wall_check(row, col, dir) && !(row + dr[dir] == w_row && col + dc[dir] == w_col)){
        if (theoretical_step(row + dr[dir], col + dc[dir], dir, w_row, w_col)){
            visit[row][col][dir] = false;
            return true;
        }else{
            visit[row][col][dir] = false;
            return false;
        }
    }else{
        if (theoretical_step(row, col, (dir + 1) % 4, w_row, w_col)){
            visit[row][col][dir] = false;
            return true;
        }else{
            visit[row][col][dir] = false;
            return false;
        }
    }
    visit[row][col][dir] = false;
    return false;
}

int path_scan(int start_row, int start_col, int start_dir){
    int ans = 0;
    visit.assign(R, vector<vector<bool>>(C, vector<bool>(4, false)));
    blockmap.assign(R, vector<bool>(C, false));

    for (int block_row = 0; block_row < R; block_row++){
        for (int block_col = 0; block_col < C; block_col++){
            if (mp[block_row][block_col] == '.'){
                ans += theoretical_step(start_row, start_col, start_dir, block_row, block_col);
            }
        }
    }

    return ans;
}

int main(){
    ifstream fi("aoc06.inp");
    ofstream fo("aoc06.out");

    string tmp;
    while (fi >> tmp){
        R += 1;
        C = (int)tmp.size();
        mp.push_back(tmp);

        for (int c = 0; c < C; c++){
            switch (mp[R - 1][c]){
                case '^':
                    sr = R - 1;
                    sc = c;
                    sd = 0;
                    break;
                case '>':
                    sr = R - 1;
                    sc = c;
                    sd = 1;
                    break;
                case 'v':
                    sr = R - 1;
                    sc = c;
                    sd = 2;
                    break;
                case '<':
                    sr = R - 1;
                    sc = c;
                    sd = 3;
            }
        }
    }
    fo << path_scan(sr, sc, sd);
}