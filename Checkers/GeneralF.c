#include "GeneralH.h"

/*-------------------------------------------------------------------
general system function
-------------------------------------------------------------------*/

BOOL canEat(int direction, Board board, checkersPos* pos)
{
	int row, col;
	updateRowCol(&row, &col, pos);
	if (board[row][col] == 'B')
	{
		if (direction == RIGHT)
		{
			if (row - 2 >= 0 && col + 2 <= 7)
			{
				if (board[row - 1][col + 1] == 'T' && board[row - 2][col + 2] == ' ')
					return TRUE;
				else return FALSE;
			}
		}
		else if (direction == LEFT)
		{
			if (row - 2 >= 0 && col - 2 >= 0)
			{
				if (board[row - 1][col - 1] == 'T' && board[row - 2][col - 2] == ' ')
					return TRUE;
				else return FALSE;
			}

		}
	}
	else if (board[row][col] == 'T')
	{
		if (direction == RIGHT)
		{
			if (row + 2 <= 7 && col + 2 <= 7)
				if (board[row + 1][col + 1] == 'B' && board[row + 2][col + 2] == ' ')
					return TRUE;
				else return FALSE;
			else return FALSE;
		}
		else if (direction == LEFT)
		{
			{
				if (row + 2 <= 7 && col - 2 >= 0)
					if (board[row + 1][col - 1] == 'B' && board[row + 2][col - 2] == ' ')
						return TRUE;
					else return FALSE;
				else return FALSE;
			}
		}
	}
	else return FALSE;
}
BOOL canEatG(Board board, checkersPos* pos)
{
	BOOL right = canEat(RIGHT, board, pos);
	BOOL left = canEat(LEFT, board, pos);
	if (right || left)return TRUE;
	else return FALSE;

}
BOOL canMove(int direction, Board board, checkersPos* pos)
{
	int row, col;
	updateRowCol(&row, &col, pos);
	if (board[row][col] == 'B')
	{
		if (direction == RIGHT)
		{
			if (row - 1 >= 0 && col + 1 <= 7)
				if (board[row - 1][col + 1] == ' ')
					return TRUE;
				else return FALSE;
			else return FALSE;

		}
		else if (direction == LEFT)
		{
			if (row - 1 >= 0 && col - 1 >= 0)
				if (board[row - 1][col - 1] == ' ')
					return TRUE;
				else return FALSE;
			else return FALSE;
		}
	}
	else if (board[row][col] == 'T')
	{
		if (direction == RIGHT)
		{
			if (row + 1 <= 7 && col + 1 <= 7)
				if (board[row + 1][col + 1] == ' ')
					return TRUE;
				else return FALSE;
			else return FALSE;

		}
		else if (direction == LEFT)
		{
			if (row + 1 <= 7 && col - 1 >= 0)
				if (board[row + 1][col - 1] == ' ')
					return TRUE;
				else return FALSE;
			else return FALSE;
		}
	}
	else return FALSE;
}
BOOL canMoveG(Board board, checkersPos* pos)
{
	BOOL right = canMove(RIGHT, board, pos);
	BOOL left = canMove(LEFT, board, pos);
	if (right || left)return TRUE;
	else return FALSE;
}
void updateRowCol(int* row, int* col, checkersPos* pos)
{
	*col = (pos->col - '0') - 1;
	char ch = pos->row - 17;
	*row = atoi(&ch);
}
void build_default_board(Board b) {
	int j;

	for (int i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			b[i][j] = ' ';
		}

	}
	j = 1;
	for (int i = 0; i < 3; i++)
	{

		for (j; j < 8; j = j + 2)
		{
			b[i][j] = 'T';
		}
		if (i == 0)
			j = 0;

		else
			j = 1;


	}
	j = 0;
	for (int i = 5; i < 8; i++)
	{

		for (j; j < 8; j = j + 2)
		{
			b[i][j] = 'B';
		}
		if (i == 5)
			j = 1;
		else
			j = 0;

	}

}
void alloCheck(void* ptr)
{
	if (ptr == NULL) exit(1);
}

void freeTreeRec(SingleSourceMovesTreeNode* node)
{
	if (node == NULL)
		return;

	freeTreeRec(node->next_move[1]);
	freeTreeRec(node->next_move[0]);
	free(node);
}
void free_Single_source_moves_list(SingleSourceMovesList* lst) {
	SingleSourceMovesListCell* curr = lst->head;
	SingleSourceMovesListCell * saver;

	while (curr) {
		saver = curr->next;
		free(curr->posit);
		free(curr);
		curr = saver;

	}
}
void free_Multiple_source_moves_list(MultiPleSourceMovesList* lst) {
	MultiPleSourceMovesListCell* curr = lst->head, *saver;
	while (curr) {
		saver = curr->next;
		SingleSourceMovesList *curr_single = curr->single_s_m_list;
		free_Single_source_moves_list(curr_single);
		free(curr);
		curr = saver;


	}
}