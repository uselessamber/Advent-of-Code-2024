#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

const int dr[4] = {-1,  0,  1,  0};
const int dc[4] = { 0,  1,  0, -1};

vector<string> mp;
vector<vector<vector<bool>>> highway;
vector<vector<bool>> assume_blockable;
int R = 0, C = 0;
int sr, sc, sd;

bool in_bound(int r, int c){
    return (0 <= r && r < R) && (0 <= c && c < C);
}

// Algorithm Idea: Highway Builder
/*
    Idea: When encountering a blocker, before turning, mark every tile behind self until the next blocker as a highway in that direction.
    A highway is a path where once the guard travels on it in the right direction, he will always loop back on himself.
    The final turn before leaving the graph is saved. After leaving, a highway is built to check for any missed loop.
*/

bool wall_check(int row, int col, int dir){
    return in_bound(row + dr[dir], col + dc[dir]) && mp[row + dr[dir]][col + dc[dir]] == '#';
}

void build_highway(int at_row, int at_col, int at_dir){
    int current_row = at_row;
    int current_col = at_col;
    int current_dir = at_dir;

    while (in_bound(current_row, current_col) && mp[current_row][current_col] != '#'){
        highway[current_row][current_col][current_dir] = true;
        if (wall_check(current_row, current_col, (current_dir + 3) % 4) 
            && !highway[current_row][current_col][(current_dir + 3) % 4]) 
            build_highway(current_row, current_col, (current_dir + 3) % 4);
        current_row -= dr[current_dir];
        current_col -= dc[current_dir];
    }
}

int path_scan(int start_row, int start_col, int start_dir){
    highway.assign(R, vector<vector<bool>>(C, vector<bool>(4, false)));
    assume_blockable.assign(R, vector<bool>(C, false));
    int answer = 0;

    int last_turn_row = start_row;
    int last_turn_col = start_col;

    int current_row = start_row;
    int current_col = start_col;
    int current_dir = start_dir;

    while (in_bound(current_row, current_col)){
        cerr << current_row << " " << current_col << " " << current_dir << "\n";
        if (highway[current_row][current_col][(current_dir + 1) % 4] 
            && !assume_blockable[current_row + dr[current_dir]][current_col + dc[current_dir]]){
            assume_blockable[current_row + dr[current_dir]][current_col + dc[current_dir]] = true;
            answer += 1;
        }
        if (!wall_check(current_row, current_col, current_dir)){
            current_row += dr[current_dir];
            current_col += dc[current_dir];
        }else{
            build_highway(current_row, current_col, current_dir);
            last_turn_row = current_row;
            last_turn_col = current_col;
            current_dir = (current_dir + 1) % 4;
        }
    }
    current_row -= dr[current_dir];
    current_col -= dc[current_dir];
    build_highway(current_row, current_col, current_dir);

    current_row = last_turn_row;
    current_col = last_turn_col;

    while (in_bound(current_row, current_col)){
        cerr << current_row << " " << current_col << " " << current_dir << "\n";
        if (highway[current_row][current_col][(current_dir + 1) % 4] 
            && !assume_blockable[current_row + dr[current_dir]][current_col + dc[current_dir]]){
            assume_blockable[current_row + dr[current_dir]][current_col + dc[current_dir]] = true;
            answer += 1;
        }
        if (!wall_check(current_row, current_col, current_dir)){
            current_row += dr[current_dir];
            current_col += dc[current_dir];
        }else{
            build_highway(current_row, current_col, current_dir);
            last_turn_row = current_row;
            last_turn_col = current_col;
            current_dir = (current_dir + 1) % 4;
        }
    }
    return answer;
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