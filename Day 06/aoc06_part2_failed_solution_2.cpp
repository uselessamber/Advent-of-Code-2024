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
enum TABLE_RESULT {
    not_visited, visited, loopable, non_loopable
};
vector<vector<vector<int>>> memoization_table;
vector<vector<bool>> blockmap;
int R = 0, C = 0;
int sr, sc, sd;

bool in_bound(int r, int c){
    return (0 <= r && r < R) && (0 <= c && c < C);
}

bool wall_check(int row, int col, int dir){
    return in_bound(row + dr[dir], col + dc[dir]) && mp[row + dr[dir]][col + dc[dir]] == '#';
}

int search(int row, int col, int dir){
    if (!in_bound(row, col)) return non_loopable;

    if (memoization_table[row][col][dir] != not_visited){
        if (memoization_table[row][col][dir] == visited) return loopable;
        return memoization_table[row][col][dir];
    }

    memoization_table[row][col][dir] = visited;

    if (!wall_check(row, col, dir)){
        memoization_table[row][col][dir] = search(row + dr[dir], col + dc[dir], dir);
    }else{
        memoization_table[row][col][dir] = search(row, col, dir);
    }
}

int path_scan(int start_row, int start_col, int start_dir){
    int ans = 0;
    memoization_table.assign(R, vector<vector<int>>(C, vector<int>(4, not_visited)));
    blockmap.assign(R, vector<bool>(C, false));

    

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