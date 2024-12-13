#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;
const int N     = 1000;
const int dr[4] = {  1,  0, -1,  0};
const int dc[4] = {  0,  1,  0, -1};
int height_map[N][N];
int layer_map[N][N];
int MAX_ROW = 0, MAX_COL = 0;

struct pos{
    int row = 0;
    int col = 0;

    pos(int row, int col){
        this->row = row;
        this->col = col;
    }

    bool is_valid(){
        return (0 <= this->row && this->row < MAX_ROW) && (0 <= this->col && this->col < MAX_COL);
    }

    pos add(int delta_row, int delta_col){
        return pos(this->row + delta_row, this->col + delta_col);
    }
};

vector<pos> start_loc;

string get_map(){
    string output = "";
    for (int r = 0; r < MAX_ROW; r++){
        for (int c = 0; c < MAX_COL; c++){
            char p1 = (char)('0' + height_map[r][c]);
            char p2 = (char)('0' + layer_map[r][c]);
            output = output + '[';
            output = output + p1;
            output = output + " - {";
            output = output + p2;
            output = output + "}] ";
        }
        output = output + "\n";
    }
    return output;
}

int get_map_loc(pos location){
    return height_map[location.row][location.col];
}

int get_layer(pos location){
    return layer_map[location.row][location.col];
}

void add_layer(pos location, int value){
    layer_map[location.row][location.col] += value;
}

void flood(int type){
    for (int r = 0; r < MAX_ROW; r++){
        for (int c = 0; c < MAX_COL; c++){
            pos curr(r, c);
            if (get_map_loc(curr) != type) continue;
            for (int d = 0; d < 4; d++){
                pos nxt = curr.add(dr[d], dc[d]);
                if ((nxt.is_valid()) && (get_map_loc(curr) - 1 == get_map_loc(nxt))){
                    add_layer(nxt, get_layer(curr));
                }
            }
        }
    }
}

int main(){
    ifstream fi("aoc10.inp");
    ofstream fo("aoc10.out");
    auto start = chrono::high_resolution_clock::now();
    // Code start
    string inp;
    while (fi >> inp){
        MAX_COL = inp.length();
        for (int i = 0; i < MAX_COL; i++){
            height_map[MAX_ROW][i] = (int)(inp[i] - '0');

            if (height_map[MAX_ROW][i] == 9) add_layer(pos(MAX_ROW, i), 1);
            if (height_map[MAX_ROW][i] == 0) start_loc.push_back(pos(MAX_ROW, i));
        }
        MAX_ROW++;
    }
    for (int i = 0; i < 9; i++){
        // fo << get_map() << "\n";
        flood(9 - i);
    }
    // fo << get_map() << "\n";

    long long ans = 0;
    for (pos start_pos : start_loc){
        ans += get_layer(start_pos);
    }
    fo << ans;

    // Code end
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Execute time: " << (double)duration.count() / 1000.0 << "ms\n";
}