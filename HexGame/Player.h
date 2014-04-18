//
//  Player.h
//  HexGame
//
//  Created by Peter Trebing on 15.12.13.
//  Copyright (c) 2013 Peter Trebing. All rights reserved.
//

#ifndef __HexGame__Player__
#define __HexGame__Player__

#include <iostream>
#include <string>

using namespace std;

#endif /* defined(__HexGame__Player__) */

enum COLOR : unsigned {
    BLACK = 1,
    WHITE = 2,
    EMPTY = 0
};

class Player {
    
public:
    
    enum KIND : unsigned {
        NONE = 0,
        HUMAN = 1,
        COMPUTER = 2
    };
    
public:
    
    Player(KIND kind_of_player = KIND::NONE, COLOR color = COLOR::EMPTY, string name = ""): my_kind(kind_of_player), my_color(color), my_name(name) {};
    
    Player(Player &other);
    
    string get_name();
    KIND get_kind();
    COLOR get_color();
    
    
private:
    string my_name;
    KIND my_kind;
    COLOR my_color;
    
};