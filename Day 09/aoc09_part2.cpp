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

// Solution idea: Double-ended Linked List

struct block {
    // Pointer
    block *next_node = nullptr;
    block *prev_node = nullptr;

    // Block can either be empty or contain some data.
    int id = 0; // If ID < 0, this is an empty block
    int block_size = 0;

    block(int block_size, int id = -1){
        this->block_size = block_size;
        this->id = id;
    }
} *first, *last;

// Block infrastructure:
// b1 <> b2 <> b3 <> b4 <> b5 
// > = next
// < = prev

void disconnect_block(block *b){
    // 
    if (b->prev_node != nullptr)
        b->prev_node->next_node = b->next_node;
    else
        b->next_node->prev_node = nullptr;
    if (b->next_node != nullptr)
        b->next_node->prev_node = b->prev_node;
    else
        b->prev_node->next_node = nullptr;
    // 
    b->prev_node = nullptr;
    b->next_node = nullptr;
}

void insert_block(block *position, block *target){
    block *next_block_ptr = position->next_node;
    position->next_node = target;
    target->prev_node = position;

    target->next_node = next_block_ptr;
    next_block_ptr->prev_node = target;
}

void new_block(int block_size, int id = -1){
    block *tmp = new block(block_size, id);
    if (first == nullptr){
        first = tmp;
    }
    if (last != nullptr){
        tmp->prev_node = last;
        last->next_node = tmp;
    }
    last = tmp;
}

void clear(){
    while (last != first){
        block *follow = last->prev_node;
        delete last;
        last = follow;
    }
    delete last;
}

void left_most_insert(block *b){
    block* iter = first;
    while (iter != b && iter != nullptr){
        if ((iter->id != -1) || (iter->id == -1 && iter->block_size < b->block_size)) iter = iter->next_node;
        else{
            iter->block_size -= b->block_size;
            if (b->prev_node != nullptr && b->prev_node->id == -1){
                b->prev_node->block_size += b->block_size;
            }
            disconnect_block(b);
            insert_block(iter->prev_node, b);
            break;
        }
    }
}

string print_blocks(){
    block *iter = first;
    string output = "";
    while (iter != nullptr){
        for (int i = 0; i < iter->block_size; i++){
            char c = '0' + iter->id;
            if (iter->id < 0) output = output + '.';
            else output = output + c;
        }
        iter = iter->next_node;
    }
    return output;
}

long long checksum(){
    block *iter = first;
    long long ans = 0;
    int order = 0;
    while (iter != nullptr){
        for (int i = 0; i < iter->block_size; i++){
            ans += (long long)((iter->id < 0)? 0 : iter->id) * (long long)order;
            order += 1;
        }
        iter = iter->next_node;
    }
    return ans;
}

void block_move(){
    block *b = last;
    // cout << print_blocks() << "\n";
    while (b != nullptr){
        block *next_block = b->prev_node;
        if (b->id >= 0){
            left_most_insert(b);
        }
        b = next_block;
        // cout << print_blocks() << "\n";
    }
}

int main(){
    ifstream fi("aoc09.inp");
    ofstream fo("aoc09.out");
    auto start = chrono::high_resolution_clock::now();
    // Code start
    char inp;
    int order = 0;
    bool is_empty = false;
    while (fi >> inp){
        int block_size = (int)(inp - '0');
        if (!is_empty){
            new_block(block_size, order++);
        }else{
            new_block(block_size);
        }
        is_empty = !is_empty;
    }
    block_move();
    fo << checksum();
    clear();
    // Code end
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Execute time: " << (double)duration.count() / 1000.0 << "ms\n";
}