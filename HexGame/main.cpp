#include <iostream>
#include <string>
#include <set>
#include <algorithm>    // std::move_backward
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <assert.h>
#include "HexGraph.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    std::vector<int> foo {1,2,3,4,5};
    
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
    
    std::cout << "shuffled elements:";
    for (int& x: foo) std::cout << ' ' << x;
    std::cout << '\n';
    
    
    hex_graph g(3);
    
    COLOR won = g.who_won();
    
    vector<set<int>> test;

    test.push_back({1, 3});
    test.push_back({0, 2, 3, 4});
    test.push_back({1, 4, 5});
    test.push_back({0, 1, 4, 6});
    test.push_back({3, 5, 1, 2, 6, 7});
    test.push_back({2, 4, 7, 8});
    test.push_back({3, 4, 7});
    test.push_back({6, 8, 4, 5});
    test.push_back({7, 5});
    
    bool correct = true;
    int graph_size = 0;
    
    for (int i = 0; i < 3; i++) {
        
        for (int j = 0; j < 3; j++) {
            
            set<int> act_adj = g.adj(i, j);
            graph_size += act_adj.size();
            
            set<int> act_test = test[j*3+i];
            set<int> diff;
            
            set_difference( act_adj.begin(), act_adj.end(), act_test.begin(), act_test.end(),
                             std::inserter( diff, diff.begin() ) );
            if (diff.size() > 0) {
                correct = false;
                break;
            }
        }
    }
    
    int board_side = 3;
    int act_size = (board_side - 1) * (3*board_side - 1);
    assert(graph_size == (act_size * 2));
    assert(correct);
    cout << "Check of 3x3 board: " << correct << endl;
    
    hex_graph g1(11);
    
    return 0;
}

