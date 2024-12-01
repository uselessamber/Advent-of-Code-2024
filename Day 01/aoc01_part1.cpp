#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    freopen("aoc01.inp", "r", stdin);
    freopen("aoc01.out", "w", stdout);

    // Sorting Problem.
    int v1, v2;
    std::vector <int> l1, l2;
    
    // Read the numbers and put them into vectors.
    while (std::cin >> v1 >> v2){
        l1.push_back(v1);
        l2.push_back(v2);
    }

    // Sort the numbers
    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());

    // Output solution (sum(abs(l1[i] - l2[i]) for i in all))
    // An unspoken but implied rule is that the two lists are the same size.
    long long d = 0;
    for (int i = 0; i < (int)l1.size(); i++){
        d += abs(l1[i] - l2[i]);
    }
    std::cout << d;
}