#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const int dr[4] = {-1,  0,  1,  0};
const int dc[4] = { 0,  1,  0, -1};

vector <string> mp;
vector <vector <bool>> visit;
int R = 0, C = 0;
int sr, sc, sd;

bool in_bound(int r, int c){
    return (0 <= r && r < R) && (0 <= c && c < C);
}

int path_scan(){
    ofstream debug("debug.txt");
    int occupied = 1;
    visit.assign(R, vector<bool>(C, false));
    visit[sr][sc] = true;
    int cr = sr;
    int cc = sc;
    int cd = sd;
    debug << cr << " " << cc << " " << cd << "\n";

    while (in_bound(cr, cc)){
        for (int i = 0; i < 4; i++){
            int nd = (cd + i) % 4;
            int nr = cr + dr[nd];
            int nc = cc + dc[nd];

            if (!in_bound(nr, nc) || (in_bound(nr, nc) && mp[nr][nc] != '#')){
                if (in_bound(nr, nc) && !visit[nr][nc]){
                    occupied += 1;
                    visit[nr][nc] = true;
                    debug << nr << " " << nc << " " << nd << "\n";
                }
                cr = nr;
                cc = nc;
                cd = nd;
                break;
            }
        }
    }
    return occupied;
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
    fo << path_scan();
}