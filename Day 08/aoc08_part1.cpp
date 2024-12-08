#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii; // first = row, second = col

vector<vector<bool>> antinodes;
int R, C;

bool in_bound(pii point){
    return (0 <= point.first && point.first < R) && (0 <= point.second && point.second < C);
}

pii get_inverse(pii &a){
    return pii(- a.first, - a.second);
}

pii get_diff(pii &a, pii &b){
    return pii(b.first - a.first, b.second - a.second);
}

pii get_new_point(pii &a, pii &v){
    return pii(a.first + v.first, a.second + v.second);
}

struct antenna {
    vector<pii> coordinates;
    void calculate_antinodes(vector<vector<bool>> &antinode_map) {
        for (int p1 = 0; p1 < (int)this->coordinates.size() - 1; p1++){
            for (int p2 = p1 + 1; p2 < (int)this->coordinates.size(); p2++){
                pii diff = get_diff(this->coordinates[p1], this->coordinates[p2]);
                pii idiff = get_inverse(diff);
                pii antinode1 = get_new_point(this->coordinates[p1], idiff);
                pii antinode2 = get_new_point(this->coordinates[p2], diff);

                if (in_bound(antinode1)) antinode_map[antinode1.first][antinode1.second] = true;
                if (in_bound(antinode2)) antinode_map[antinode2.first][antinode2.second] = true;
            }
        }
    }
};
antenna arr[256];

int main(){
    // Time setup
    auto start = chrono::high_resolution_clock::now();

    // File setup
    ifstream fi("aoc08.inp");
    ofstream fo("aoc08.out");

    // Code
    string tmp;
    while (fi >> tmp){
        R++;
        C = tmp.length();
        for (int i = 0; i < C; i++){
            if (tmp[i] != '.'){
                unsigned char identifier = tmp[i];
                arr[(int)identifier].coordinates.push_back(pii(R - 1, i));
            }
        }
    }
    
    antinodes.assign(R, vector<bool>(C, false));
    for (int i = 0; i < 256; i++){
        arr[i].calculate_antinodes(antinodes);
    }
    int ans = 0;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (antinodes[i][j]) ans++;
        }
    }
    fo << ans;
    
    // Time end
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execute time: " << duration.count() << "ms\n";
}