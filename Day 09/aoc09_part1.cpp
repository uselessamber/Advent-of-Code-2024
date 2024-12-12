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

vector<int> arr;
string diskmap;

int main(){
    ifstream fi("aoc09.inp");
    ofstream fo("aoc09.out");
    auto start = chrono::high_resolution_clock::now();
    // Code start
    fi >> diskmap;
    bool is_file = true;
    int block_id = 0;

    for (char c : diskmap){
        int block_size = (int)(c - '0');
        for (int i = 0; i < block_size; i++){
            if (is_file){
                arr.push_back(block_id);
            }else{
                arr.push_back(-1);
            }
        }
        is_file = !is_file;
        block_id += is_file;
    }

    int l = 0, r = (int)arr.size() - 1;
    cout << "\n";
    while (l < r){
        while (arr[l] != -1 && l < r) l++;
        while (arr[r] == -1 && r > l) r--;
        if (l < r){
            swap(arr[l], arr[r]);
        }
    }
    long long ans = 0;
    for (int i = 0; i < (int)arr.size(); i++){
        if (arr[i] != -1) {
            ans += (long long)i * (long long)arr[i];
        }
    }

    fo << ans;
    // Code end
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Execute time: " << (double)duration.count() / 1000.0 << "ms\n";
}