//
//  HexGraph.h
//  HexGame
//
//  Created by Peter Trebing on 07.12.13.
//  Copyright (c) 2013 Peter Trebing. All rights reserved.
//

#ifndef __HexGame__HexGraph__
#define __HexGame__HexGraph__

#include <iostream>
#include <vector>
#include <set>

#include "Player.h"

using namespace std;

#endif /* defined(__HexGame__HexGraph__) */

class edge {
    
public:
    edge():state(COLOR::EMPTY){};

private:
    COLOR state;
    
};

class hex_graph {
    
public:
    hex_graph(int hsize);
    
    //return adjacensies of tile (i,j)
    set<int> adj(int i, int j);
    
    COLOR who_won();
    
    void make_next_move(int i, int j);
    
    COLOR play_game(COLOR beginner);
    
    void define_players(Player player1, Player player2);
    
private:
    
    inline int index(int i, int j);
    void makeNode( int i, int j, int n, set<int> &elist);
    vector<set<int>> g;
    const int board_side;
    vector<COLOR> stone; //0, 1, 2 - 0 means empty
    
    COLOR whos_turn;
    Player player[2];
    
};