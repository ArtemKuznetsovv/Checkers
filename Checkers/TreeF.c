#include "TreeH.h"

/*-------------------------------------------------------------------
part 1 related functions
-------------------------------------------------------------------*/
SingleSourceMovesTree* FindBestSingleSource(Board board, checkersPos* pos)
{
	int row, col;
	updateRowCol(&row, &col, pos);
	if (board[row][col] == ' ')
		return NULL;
	else
	{
		SingleSourceMovesTree* tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		alloCheck(tree);
		SingleSourceMovesTreeNode* root = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
		alloCheck(root);
		CopyBoard(root, board);//copies the board into the value "board" in root
		root->next_move[1] = root->next_move[0] = NULL;
		root->pos = pos;
		root->total_capture_so_far = 0;
		tree->source = FindBestSingleSourceAux(root, board, pos);
		return tree;

	}
}
SingleSourceMovesTreeNode* FindBestSingleSourceAux(SingleSourceMovesTreeNode* root, Board board, checkersPos* pos)
{
	if (canEatG(board, pos) == TRUE)
	{
		SendRecourEats(root, board, pos);
	}
	if (root->next_move[1] == NULL || root->next_move[0] == NULL)
	{
		SendMoveOne(root, board, pos);
	}
	return root;
}
void SendRecourEats(SingleSourceMovesTreeNode* root, Board board, checkersPos* pos)
{
	checkersPos* posL;
	checkersPos* posR;
	SingleSourceMovesTreeNode* newnode = malloc(sizeof(SingleSourceMovesTreeNode));
	alloCheck(newnode);
	if (canEatG(root->board, root->pos) == FALSE)
	{
		return;
	}

	if (canEat(RIGHT, root->board, root->pos) == TRUE)
	{

		posR = UpdatedPos(pos, RIGHT, CAPTURE, board);
		Board temp_b;
		CopyBoardV2(&temp_b, board);//creates exact copie of board , in , temp_b
		UpdatedBoard(pos, RIGHT, CAPTURE, board, &temp_b);//updates by ref temp_b after the change 
		root->next_move[1] = UpdateNode(CAPTURE, root, posR, temp_b);
		SendRecourEats(root->next_move[1], temp_b, posR);
	}

	if (canEat(LEFT, root->board, root->pos) == TRUE)
	{

		posL = UpdatedPos(pos, LEFT, CAPTURE, board);
		Board temp_b;
		CopyBoardV2(&temp_b, board);
		UpdatedBoard(pos, LEFT, CAPTURE, board, &temp_b);
		root->next_move[0] = UpdateNode(CAPTURE, root, posL, temp_b);
		SendRecourEats(root->next_move[0], temp_b, posL);

	}

}
void SendMoveOne(SingleSourceMovesTreeNode* root, Board board, checkersPos* pos)
{
	SingleSourceMovesTreeNode* newnode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	alloCheck(newnode);
	checkersPos* posR;
	checkersPos* posL;

	if (root->next_move[1] == NULL)
	{
		if (canMove(RIGHT, board, pos) == TRUE)
		{
			posR = UpdatedPos(pos, RIGHT, MOVE, board);
			Board temp_b;
			CopyBoardV2(&temp_b, board);
			UpdatedBoard(pos, RIGHT, MOVE, board, &temp_b);
			root->next_move[1] = UpdateNode(MOVE, root, posR, temp_b);
		}
	}
	if (root->next_move[0] == NULL)
	{
		if (canMove(LEFT, board, pos) == TRUE)
		{
			posL = UpdatedPos(pos, LEFT, MOVE, board);
			Board temp_b;
			CopyBoardV2(&temp_b, board);
			UpdatedBoard(pos, LEFT, MOVE, board, &temp_b);
			root->next_move[0] = UpdateNode(MOVE, root, posL, temp_b);
		}
	}

}
void CopyBoard(SingleSourceMovesTreeNode* node, Board board) {
	int i = 0, j = 0;

	for (j; j < Board_Size; j++) {
		for (i; i < Board_Size; i++)
			node->board[j][i] = board[j][i];
		i = 0;
	}

}
void CopyBoardV2(Board* new_board, Board old_board) {
	int i = 0, j = 0;

	for (j; j < Board_Size; j++) {
		for (i; i < Board_Size; i++)
			(*new_board)[j][i] = old_board[j][i];
		i = 0;
	}
}
void UpdatedBoard(checkersPos* oldpos, int direction, int move, Board oldboard, Board* newboard)
{

	int row, col;
	updateRowCol(&row, &col, oldpos);
	int x;
	if (move == MOVE) x = 1; else x = 2;
	if (direction == RIGHT && oldboard[row][col] == 'B')
	{
		(*newboard)[row][col] = ' ';
		(*newboard)[row - x][col + x] = 'B';
		if (move == CAPTURE)
			(*newboard)[row - x + 1][col + x - 1] = ' ';
	}
	else if (direction == LEFT && oldboard[row][col] == 'B')
	{
		(*newboard)[row][col] = ' ';
		(*newboard)[row - x][col - x] = 'B';
		if (move == CAPTURE)
			(*newboard)[row - x + 1][col - x + 1] = ' ';
	}
	else if (direction == RIGHT && oldboard[row][col] == 'T')
	{
		(*newboard)[row][col] = ' ';
		(*newboard)[row + x][col + x] = 'T';
		if (move == CAPTURE)
			(*newboard)[row + x - 1][col + x - 1] = ' ';

	}
	else if (direction == LEFT && oldboard[row][col] == 'T')
	{
		(*newboard)[row][col] = ' ';
		(*newboard)[row + x][col - x] = 'T';
		if (move == CAPTURE)
			(*newboard)[row + x - 1][col - x + 1] = ' ';
	}

}
checkersPos* UpdatedPos(checkersPos* curr, int direction, int move, Board board)
{
	int row, col;
	updateRowCol(&row, &col, curr);
	checkersPos* newpose = (checkersPos*)malloc(sizeof(checkersPos));
	alloCheck(newpose);
	newpose->col = newpose->row = '-1';
	int x;
	if (move == MOVE) x = 1;
	else x = 2;
	if (board[row][col] == 'B' && direction == RIGHT)
	{
		newpose->col = curr->col + x;
		newpose->row = curr->row - x;

	}
	else if (board[row][col] == 'B' && direction == LEFT)
	{

		newpose->col = curr->col - x;
		newpose->row = curr->row - x;
	}
	else if (board[row][col] == 'T' && direction == RIGHT)
	{

		newpose->col = curr->col + x;
		newpose->row = curr->row + x;
	}
	else if (board[row][col] == 'T' && direction == LEFT)
	{
		newpose->row = curr->row + x;
		newpose->col = curr->col - x;
	}
	return newpose;
}
SingleSourceMovesTreeNode* UpdateNode(int typeOfMove, SingleSourceMovesTreeNode* root, checkersPos* pos, Board newboard)
{
	SingleSourceMovesTreeNode* node = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	alloCheck(node);
	if (typeOfMove == CAPTURE)
	{
		node->next_move[1] = node->next_move[0] = NULL;
		node->total_capture_so_far = root->total_capture_so_far + 1;
		CopyBoard(node, newboard);
		node->pos = (checkersPos*)malloc(sizeof(checkersPos));
		alloCheck(node->pos);
		node->pos = pos;
	}
	else if (typeOfMove == MOVE)
	{
		node->next_move[1] = node->next_move[0] = NULL;
		node->total_capture_so_far = root->total_capture_so_far;
		CopyBoard(node, newboard);
		node->pos = (checkersPos*)malloc(sizeof(checkersPos));
		alloCheck(node->pos);
		node->pos = pos;
	}
	return node;
}
BOOL isLeaf(SingleSourceMovesTreeNode* node) {
	return (node->next_move[0] == NULL && node->next_move[1] == NULL);
}
int TrimTree(SingleSourceMovesTreeNode* node)
{
	int left = 0, right = 0;

	if (isLeaf(node)) return node->total_capture_so_far;

	if (node->next_move[0] == NULL) {
		return TrimTree(node->next_move[1]);
	}
	if (node->next_move[1] == NULL) {
		return TrimTree(node->next_move[0]);
	}

	left = TrimTree(node->next_move[0]);
	right = TrimTree(node->next_move[1]);

	if (left > right) {
		freeTreeRec(node->next_move[1]);
		node->next_move[1] = NULL;
		return left;
	}

	if (left == right) {
		if (rand() % 2 == 0) {
			freeTreeRec(node->next_move[1]);
			node->next_move[1] = NULL;
			return left;

		}
		else {

			freeTreeRec(node->next_move[0]);
			node->next_move[0] = NULL;
			return right;

		}


	}
	else if (right > left)
	{
		freeTreeRec(node->next_move[0]);
		node->next_move[0] = NULL;
		return right;
	}
}