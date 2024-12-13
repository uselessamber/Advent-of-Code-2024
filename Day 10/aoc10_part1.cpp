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

vector<pos> start_loc, end_loc;

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

void flood(pos start_point){
    queue<pos> q;
    add_layer(start_point, 1);
    q.push(start_point);
    bool flood_map[N][N] = {};
    flood_map[start_point.row][start_point.col] = true;

    while (!q.empty()){
        pos curr_pos = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            pos next_pos = curr_pos.add(dr[i], dc[i]);
            if (next_pos.is_valid() && (get_map_loc(curr_pos) - 1 == get_map_loc(next_pos)) && !flood_map[next_pos.row][next_pos.col]){
                add_layer(next_pos, 1);
                q.push(next_pos);
                flood_map[next_pos.row][next_pos.col] = true;
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

            if (height_map[MAX_ROW][i] == 0) start_loc.push_back(pos(MAX_ROW, i));
            if (height_map[MAX_ROW][i] == 9) end_loc.push_back(pos(MAX_ROW, i));
        }
        MAX_ROW++;
    }
    // fo << get_map() << "\n";
    for (pos end_pos : end_loc){
        flood(end_pos);
        // fo << get_map() << "\n";
    }

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