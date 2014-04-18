//
//  Player.cpp
//  HexGame
//
//  Created by Peter Trebing on 15.12.13.
//  Copyright (c) 2013 Peter Trebing. All rights reserved.
//

#include "Player.h"


string Player::get_name(){
    return my_name;
}

Player::KIND Player::get_kind(){
    return my_kind;
}

COLOR Player::get_color(){
    return my_color;
}