#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;


struct ships {

    int size = 0; 
    char Type = 'Z';

}typedef Ships;

struct direction {

    int up = 1, down = 1, right = 1, left = 1;
    char choice = 'D';

}typedef Direction;


class Player
{

private:

    char player_board[10][10] = { '~' };


public:

    //constructor
    Player()
    {
        init_board(player_board, 10, 10);//sets all positions to "~"
        Ships ShipTypes;                 //struct used for storing current ship to be placed
        Direction direction;             //struct to store directions ships can face
        randomly_place_ships_on_board(ShipTypes, direction);//places ships
    }



    int place_ship(int start_row, int length, int start_col, char direct, int check, char ship_type, Direction direction);
    Direction direction_check(int start_row, int start_col, int length, Direction direction);
    void randomly_place_ships_on_board(Ships ShipTypes, Direction direction);
    void init_board(char board[][10], int num_rows, int num_cols);
    void print_board();
};
#endif
