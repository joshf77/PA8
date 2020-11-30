#include "Player.h"
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL));

	Player p1;
	p1.print_board();

	
	return 0;
}
