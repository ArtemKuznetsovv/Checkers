#include "ListH.h"

/*-------------------------------------------------------------------
part 2 related functions
-------------------------------------------------------------------*/

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* tree)
{
	if (tree == NULL)
		return NULL;
	else
	{
		TrimTree(tree->source);
		SingleSourceMovesList* list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
		alloCheck(list);
		initializeList(list);
		buildList(list, tree->source);



		return list;
	}
}
void initializeList(SingleSourceMovesList* list)
{
	list->head = list->tail = NULL;
}
void buildList(SingleSourceMovesList* list, SingleSourceMovesTreeNode* root)
{

	while (root)
	{
		SingleSourceMovesListCell* node = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
		alloCheck(node);
		updatedListCell(root, node);
		addToEndOfList(list, node);
		if (root->next_move[1] == NULL) {
			root = root->next_move[0];

		}

		else {
			root = root->next_move[1];

		}
	}
}
void updatedListCell(SingleSourceMovesTreeNode* root, SingleSourceMovesListCell* node)
{
	node->captures = root->total_capture_so_far;
	node->posit = (checkersPos*)malloc(sizeof(checkersPos));
	alloCheck(node->posit);
	node->posit = root->pos;
	node->next = NULL;
}
void addToEndOfList(SingleSourceMovesList* list, SingleSourceMovesListCell* node)
{
	if (list->head == NULL)
	{
		list->head = list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}
/*-------------------------------------------------------------------
part 3 related functions
-------------------------------------------------------------------*/
MultiPleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	MultiPleSourceMovesList* bestmoves = (MultiPleSourceMovesList*)malloc(sizeof(MultiPleSourceMovesList));
	alloCheck(bestmoves);
	initializeListBestMove(bestmoves);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == player)
			{
				checkersPos* pos = (checkersPos*)malloc(sizeof(checkersPos));
				alloCheck(&pos);
				FromRowAndColToPos(i, j, pos);
				SingleSourceMovesTree* treeForOnePlayer = FindBestSingleSource(board, pos);
				SingleSourceMovesList* listforOnePlayer = FindSingleSourceOptimalMove(treeForOnePlayer);
				freeTreeRec(treeForOnePlayer->source);
				addToEndOfBestMoves(bestmoves, listforOnePlayer);






			}
		}
	}
	return bestmoves;
}
void FromRowAndColToPos(int row, int col, checkersPos* pos)
{
	pos->row = (char)row + 65;
	pos->col = (char)col + 49;
}
void initializeListBestMove(MultiPleSourceMovesList* list)
{
	list->head = list->tail = NULL;
}
void addToEndOfBestMoves(MultiPleSourceMovesList* list, SingleSourceMovesList* listforOnePlayer)
{
	MultiPleSourceMovesListCell* cell_to_add = Allocate_MultipleSourceMovesListCell(listforOnePlayer);
	if (list->head == NULL)
	{
		list->head = list->tail = cell_to_add;
	}
	else
	{
		list->tail->next = cell_to_add;
		list->tail = cell_to_add;
	}

}
MultiPleSourceMovesListCell* Allocate_MultipleSourceMovesListCell(SingleSourceMovesList* lst) {
	MultiPleSourceMovesListCell* cell_to_add = (MultiPleSourceMovesListCell*)malloc(sizeof(MultiPleSourceMovesListCell));
	alloCheck(cell_to_add);
	cell_to_add->single_s_m_list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	alloCheck(cell_to_add->single_s_m_list);
	cell_to_add->single_s_m_list = lst;
	cell_to_add->next = NULL;
	return cell_to_add;

}