#include "GeneralH.h"
#include "PlayGame.h"
void main()
{
	srand(time(0));
	Board board;
	build_default_board(board);
	Player starting_player;
	printf("Choose The Player You Would Like To play : T/B \n");
	scanf("%c", &starting_player);
	getchar();
	PlayGame(board, starting_player);


}