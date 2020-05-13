#include "PlayGame.h"





/*-------------------------------------------------------------------
part 7 related functions
-------------------------------------------------------------------*/


void PlayGame(Board board, Player starting_player)
{
	BOOL flag = TRUE;

	MultiPleSourceMovesList* allmoves;
	int turnscounter = 0;
	char playerZog, playerEiZog;
	char *strZog, *strEiZog;

	playerZog = starting_player;
	PrintBoardFinale(board);

	if (starting_player == 'B')
	{
		strZog = "BOTTOM_UP";
		strEiZog = "TOP_DOWN";
		playerEiZog = 'T';
	}
	else
	{
		strEiZog = "BOTTOM_UP";
		strZog = "TOP_DOWN";
		playerEiZog = 'B';
	}
	while (CheckWinBoard(board) == 'F'&&flag == TRUE)
	{
		if (turnscounter % 2 == 0)
		{
			allmoves = FindAllPossiblePlayerMoves(board, playerZog);
			if (check_if_can_move(allmoves) == FALSE)
				flag = FALSE;
			else {
				printf("player %s's turn", strZog);
				printf("\n");
				Turn(board, playerZog);

			}

		}
		else
		{
			allmoves = FindAllPossiblePlayerMoves(board, playerEiZog);
			if (check_if_can_move(allmoves) == FALSE)
				flag = FALSE;
			else {
				printf("player %s's turn", strEiZog);
				printf("\n");
				Turn(board, playerEiZog);

			}


		}
		PrintBoardFinale(board);
		turnscounter++;
		free_Multiple_source_moves_list(allmoves);
	}




	if (flag == FALSE)
		printf("No movement avaible , so it's a tie");

	else
		printf("Player : %c ,Is the winner \n", CheckWinBoard(board));





}
char CheckWinBoard(Board board)
{
	if (condition1EndGame(board) == 'B')//B returned. Means T has no players left. B is winner.
		return 'T';
	else if (condition1EndGame(board) == 'T')//T returned. Means B has no players left. T is winner.
		return 'T';
	else
	{
		if (condition2EndGame(board) == TRUE)//T is winner.
			return 'T';
		else if (condition3EndGame(board) == TRUE)//B is winner.
			return 'B';
		else return 'F';//Was not found a winner currently.
	}
}
char condition1EndGame(Board board)//Returns the player that still have soldiers on board
								   //while the second doesn't have any left
{
	int countB = 0, countT = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 'B') countB++;
			else if (board[i][j] == 'T') countT++;
		}
	}
	if (countB == 0) return 'T';
	else if (countT == 0) return 'B';
	else return 'F';
}
BOOL condition2EndGame(Board board)//PlayerTArrivedToH
{
	for (int i = 0; i < 8; i++)
	{
		if (board[7][i] == 'T')
			return TRUE;
	}
	return FALSE;
}
BOOL condition3EndGame(Board board)//PlayerBArrivedToA
{
	for (int i = 0; i < 8; i++)
	{
		if (board[0][i] == 'B')
			return TRUE;
	}
	return FALSE;

}

void PrintBoardFinale(Board board)
{
	int conv = 0;
	for (int i = 0; i < 19; i++)
	{
		if (i % 2 == 0)
			printf("+-+-+-+-+-+-+-+-+-+\n");
		else if (i == 1)
			printf("+ |1|2|3|4|5|6|7|8|\n");
		else
		{
			printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", (char)(conv + 65), board[conv][0], board[conv][1], board[conv][2], board[conv][3], board[conv][4], board[conv][5], board[conv][6], board[conv][7]);
			conv++;

		}

	}
}
BOOL check_if_can_move(MultiPleSourceMovesList* allmoves) {
	MultiPleSourceMovesListCell* curr = allmoves->head;
	while (curr) {
		if (ListLength(curr->single_s_m_list) > 1)
			return TRUE;
		curr = curr->next;


	}
	return FALSE;
}