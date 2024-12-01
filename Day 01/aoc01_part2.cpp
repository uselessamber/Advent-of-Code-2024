#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    freopen("aoc01.inp", "r", stdin);
    freopen("aoc01.out", "w", stdout);

    // Counting Sort?
    int v1, v2;
    std::vector <int> l1, match;

    // Assumption: a[i] < 100000
    match.assign(100000, 0);
    
    // Read the numbers and put them into vectors.
    while (std::cin >> v1 >> v2){
        l1.push_back(v1);
        match[v2] += 1;
    }
    
    long long p = 0;
    for (int i : l1){
        p += i * match[i];
    }
    
    std::cout << p;
}