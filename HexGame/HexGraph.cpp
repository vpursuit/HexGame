
//
//  HexGraph.cpp
//  HexGame
//
//  Created by Peter Trebing on 07.12.13.
//  Copyright (c) 2013 Peter Trebing. All rights reserved.
//
#include <tuple>
#include <assert.h>
#include <math.h>

#include "HexGraph.h"

using namespace std;

tuple<int, int> get_user_move() {
    
    return make_tuple(1, 1);
}

COLOR hex_graph::play_game(COLOR beginner) {
    
    whos_turn = beginner;
    
    COLOR winner = COLOR::EMPTY;
    while (winner == COLOR::EMPTY) {
        
        if(player[whos_turn].get_kind() == Player::KIND::COMPUTER) {
            
            
        } else {
           
            tuple<int, int> move = get_user_move();
            make_next_move(get<0>(move), get<1>(move));
            
        }

        winner = who_won();
    
    }
    
    return winner;
}

void hex_graph::define_players(Player player1, Player player2){
    player[player1.get_color()] = player1;
    player[player2.get_color()] = player2;
}

void hex_graph::make_next_move(int i, int j) {
    
    assert((i >=0 ) && (i < board_side));
    assert((j >=0 ) && (j < board_side));
    assert(stone[index(i,j)] == COLOR::EMPTY);

    stone[index(i,j)] = whos_turn;
    if (whos_turn == COLOR::WHITE) {
        whos_turn = COLOR::BLACK;
    } else {
        whos_turn = COLOR::WHITE;
    }
    
}

set<int> hex_graph::adj(int i, int j){
    return g[index(i, j)];
}

inline int hex_graph::index(int i, int j){
    return j*board_side+i;
}

void hex_graph::makeNode(int i, int j, int n, set<int> &elist) {
    
    if(j == 0) {
        
        if (i == 0) { //upper left corner
            elist.insert(index(0,1));
            elist.insert(index(1,0));
        } else if (i == n-1) {  //upper right corner
            elist.insert(index(i-1,0));
            elist.insert(index(i,1));
            elist.insert(index(i-1,1));
        } else { // upper line
            elist.insert(index(i-1,j));
            elist.insert(index(i+1,j));
            elist.insert(index(i,j+1));
            elist.insert(index(i-1,j+1));
        }
        
    } else if( j == n-1) {
        
        if (i == 0) { //lower left corner
            elist.insert(index(1,j));
            elist.insert(index(0,j-1) );
            elist.insert(index(1,j-1));
        } else if (i == n-1){ //lower right corner
            elist.insert(index(i-1,j));
            elist.insert(index(i,j-1));
        } else { // lower line
            elist.insert(index(i-1,j));
            elist.insert(index(i+1,j));
            elist.insert(index(i,j-1));
            elist.insert(index(i+1,j-1));
        }
        
    }  else if (i == 0 && j > 0 && j < n-1) { //left vertical
        
        elist.insert(index(i+1,j));
        elist.insert(index(i+1,j-1));
        elist.insert(index(i,j-1));
        elist.insert(index(i,j+1));
        
    }  else if (i == n-1 && j > 0 && j < n-1) { //right vertical
        
        elist.insert(index(i-1,j));
        elist.insert(index(i,j-1));
        elist.insert(index(i,j+1));
        elist.insert(index(i-1,j+1));
        
    } else { //internal node
        
        elist.insert(index(i-1,j));
        elist.insert(index(i+1,j));
        
        elist.insert(index(i,j-1));
        elist.insert(index(i+1,j-1));
        
        elist.insert(index(i,j+1));
        elist.insert(index(i-1,j+1));
        
    }
    
}

hex_graph::hex_graph(int hsize): board_side(hsize) {
    g.resize(hsize*hsize);
    stone.resize(hsize*hsize);
    for(int i = 0; i < hsize; i++) {
        for(int j =0; j < hsize; j++) {
            makeNode( i, j, board_side, g[index(i,j)]);
        }
    }
}

// stone_index = i* board_side + j
//
// --> i
// |   /\ /\ /\ /\ /\
// j  | o| *| o| o| o|
//     \/ \/ \/ \/ \/\
//     | o| *| o| *| o|
//      \/ \/ \/ \/ \/\
//      | o| *| o| o| *|
//       \/ \/ \/ \/ \/\
//       | *| *| o| *| *|
//        \/ \/ \/ \/ \/\
//        | o| *| *| *| o|
//         \/ \/ \/ \/ \/

// * won!

// #Tiles: board_side^2
// #Connections: (board_side - 1) (3*board_side - 1)
// Beispiel: 11x11:
// #Tiles = 121
// #Connections = 320

// Beispiel: 5x5
// #Tiles = 25
// #Connections = 56

// Check who won the game. Call the method only if the board is
// completely filled. Otherwise the result is undefined.
COLOR hex_graph::who_won() {
    
    COLOR result = COLOR::EMPTY;
    vector<bool> prev_open(board_side, false);
    vector<bool> curr_open(board_side, false);
    
    // initializing northern(the whitebase-) line
    for (int i = 0; i < board_side; ++i) {
        prev_open[i] = (stone[i] == (COLOR::WHITE));
    }
    
    for (int i = 1; i < board_side; ++i) {
        
        for (int j = 0; j<board_side - 1; ++j) {
            
            if (stone[index(i,j)] == COLOR::WHITE && (prev_open[j]||prev_open[j+1])) {
                curr_open[j] = true;
            } else {
                curr_open[j] = false;
            }
            
        } // conditions to move one row down
        
        // stone on the right edge
        int j = board_side - 1;
        if (stone[i*board_side+j] == COLOR::WHITE && prev_open[j]) {
            curr_open[j] = true;
        } else {
            curr_open[j] = false;
        }
        
    }
    
    // initializing southern line
    for (int i = 0; i < board_side; ++i) {
        if (curr_open[i]) {
            result = COLOR::WHITE;
            break;
        }
    }
    
    return result;
}