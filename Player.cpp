#include "Player.h"


void Player::init_board(char board[][10], int num_rows, int num_cols)// sets board to ~ in 2d array 10x10
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index] = '~';
		}
	}
}


void Player::print_board()//prints a board when called
{
	int num_rows = 10, num_cols = 10;
	int row_index = 0, col_index = 0;
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	for (; row_index < num_rows; ++row_index)
	{
		cout << row_index << " ";
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			cout << player_board[row_index][col_index] << " ";
		}
		cout << endl;
	}
}



Ships ship_select(Ships shiptypes, int count)//change ship types when called
{
    if (count == 0)
    {
        shiptypes.Type = 'C';
        shiptypes.size = 5;
    }
    if (count == 1)
    {
        shiptypes.Type = 'B';
        shiptypes.size = 4;
    }
    if (count == 2)
    {
        shiptypes.Type = 'R';
        shiptypes.size = 3;
    }
    if (count == 3)
    {
        shiptypes.Type = 'S';
        shiptypes.size = 3;
    }
    if (count == 4)
    {
        shiptypes.Type = 'D';
        shiptypes.size = 2;
    }
    return shiptypes;
}



void Player::randomly_place_ships_on_board(Ships shiptypes, Direction direction)//this uses same functions as manual but makes starting point and direction random.
{
    int start_row = 0, start_col = 0, count = 0;
    int size = 5;


        int varify = 1, check = 0;

        do//run through all this code until all ships are places
        {
            do
            {
                start_row = rand() % 9 + 1;//randomly select starting row
                start_col = rand() % 9 + 1;// randomly select starting col
            } while (player_board[start_row][start_col] != '~');                    //dont let starting point be on another ship

            shiptypes = ship_select(shiptypes, count);
            direction.down = 1, direction.left = 1, direction.right = 1, direction.up;
            direction = direction_check(start_row, start_col, shiptypes.size, direction);//choose a random direction that does not allow impossible starting points

            varify = 1;
            if ((direction.right == 0) && (direction.left == 0) && (direction.up == 0) && (direction.down == 0))// if no direction is avalible based off starting point dont allow ship placement
            {
                varify = 0;
            }

            char RandomDirection = 'z';
            check = 0;// code below runs till a ship is placed which sets this to 1


            if (varify != 0)// if at least one direction is avalible place the ship starting point
            {
                do
                {
                    int RandInt = rand() % 4 + 1;//choose a random direction for ship to face
                    while (RandomDirection == 'z')
                    {
                        RandInt = rand() % 4 + 1;
                        if (RandInt == 1 && direction.down == 1)
                        {
                            RandomDirection = 'd';
                        }
                        if (RandInt == 2 && direction.up == 1)
                        {
                            RandomDirection = 'u';
                        }
                        if (RandInt == 3 && direction.left == 1)
                        {
                            RandomDirection = 'l';
                        }
                        if (RandInt == 4 && direction.right == 1)
                        {
                            RandomDirection = 'r';
                        }
                    }
                    direction.choice = RandomDirection;

                    check = place_ship(start_row, shiptypes.size, start_col, RandomDirection, check, shiptypes.Type, direction);//place ship

                } while (check == 0);//if direction was invalid check isnt increased so a random direction is chosen again
                count++;
            }
        } while (count < 5);
}


int Player::place_ship(int start_row, int length, int start_col, char direct, int check, char ship_type, Direction direction)                                                                                //as long as a direction is avalible
{

    int index_row_end = (start_row + length);
    int row_index = start_row;
    int index_col_end = (start_col + length);
    int col_index = start_col, z = start_col, y = start_col;


    if ((direction.right == 1) && (direct == 'r' || direct == 'R'))
    {
        index_col_end = (start_col + length);
        col_index = start_col;
        while (col_index != index_col_end) //faces ship to the right from starting point
        {
            if (player_board[start_row][col_index] == '~')
            {
                player_board[start_row][col_index] = ship_type;
            }
            col_index++;
        }
        return 1;
    }

    if ((direction.left == 1) && (direct == 'l' || direct == 'L'))
    {
        index_col_end = (start_col - length);
        col_index = start_col;
        while (col_index != index_col_end) //faces ship to the left from starting point
        {
            if (player_board[start_row][col_index] == '~')
            {
                player_board[start_row][col_index] = ship_type;
            }
            col_index--;
        }
        return 1;
    }

    if ((direction.up == 1) && (direct == 'u' || direct == 'U'))
    {
        index_row_end = (start_row - length);
        row_index = start_row;
        while (row_index != index_row_end) //faces ship up from starting point
        {
            if (player_board[row_index][start_col] == '~')
            {
                player_board[row_index][start_col] = ship_type;
            }
            row_index--;
        }
        return 1;
    }

    if ((direction.down == 1) && (direct == 'd' || direct == 'D'))
    {
        index_row_end = (start_row + length);
        row_index = start_row;
        while (row_index != index_row_end) //faces ship down from starting point
        {
            if (player_board[row_index][start_col] == '~')
            {
                player_board[row_index][start_col] = ship_type;
            }
            row_index++;
        }
        return 1;
    }


}

Direction Player::direction_check(int start_row, int start_col, int length, Direction direction)
{
    int index_row_end = (start_row + length);//temp indexes to keep original choices unchanged
    int row_index = start_row;
    int index_col_end = (start_col + length);
    int col_index = start_col, z = start_col, y = start_col, x = start_row;

    while (col_index != index_col_end) //checks right direction
    {
        if (player_board[start_row][col_index] != '~' || (z + length - 1 > 9))
        {
            direction.right = 0;//if at any point ship hits another ship, right is made unavalible                    
        }
        col_index++;
    }

    index_col_end = (start_col - length);
    col_index = start_col;
    while (col_index != index_col_end) //checks left direction
    {
        if (player_board[start_row][col_index] != '~' || ((y - length) + 1 < 0))
        {
            direction.left = 0;//if at any point ship hits another ship, left is made unavalible
        }
        col_index--;
    }

    while (row_index != index_row_end) //checks down direction
    {
        if (player_board[row_index][start_col] != '~' || ((x + length) > 9))
        {
            direction.down = 0;//if at any point ship hits another ship, down is made unavalible
        }
        row_index++;
    }

    index_row_end = (start_row - length);
    row_index = start_row;
    while (row_index != index_row_end) //checks up direction
    {
        if (player_board[row_index][start_col] != '~')
        {
            direction.up = 0;//if at any point ship hits another ship, up is made unavalible
        }
        row_index--;
    }

    return direction;
}
