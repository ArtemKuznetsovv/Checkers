#include "TurnH.h"


/*-------------------------------------------------------------------
part 4 related functions
-------------------------------------------------------------------*/
void Turn(Board board, Player player)
{
	SingleSourceMovesList* bestmove;
	MultiPleSourceMovesList* bestmoves;
	if (player == 'B')
	{
		bestmoves = FindAllPossiblePlayerMoves(board, 'B');
		bestmove = FindOptimalMoveFromAllpieces(bestmoves, 'B');


	}
	else
	{
		bestmoves = FindAllPossiblePlayerMoves(board, 'T');
		bestmove = FindOptimalMoveFromAllpieces(bestmoves, 'T');


	}
	maketurn(board, bestmove, player);
	printmove(bestmove);
	free_Multiple_source_moves_list(bestmoves);




}
unsigned short ListLength(SingleSourceMovesList* list) {
	SingleSourceMovesListCell* curr = list->head;
	int count = 0;
	while (curr) {
		count++;
		curr = curr->next;
	}
	return count;
}
SingleSourceMovesList* FindOptimalMoveFromAllpieces(MultiPleSourceMovesList* all_moves, Player player) {
	MultiPleSourceMovesListCell* curr = all_moves->head;
	SingleSourceMovesList* list_to_return = curr->single_s_m_list;

	unsigned short max_turn = ListLength(list_to_return);
	while (curr != NULL) {
		if (CheckWinCondition(curr, player) == TRUE)
			return curr->single_s_m_list;
		if (ListLength(curr->single_s_m_list) > max_turn || curr->single_s_m_list->tail->captures > list_to_return->tail->captures) {
			max_turn = ListLength(curr->single_s_m_list);
			list_to_return = curr->single_s_m_list;

		}
		curr = curr->next;

	}
	return list_to_return;

}
BOOL CheckWinCondition(MultiPleSourceMovesListCell* move_set, Player player) {
	if (player == 'B') {
		if (move_set->single_s_m_list->tail->posit->row == 'A')
			return TRUE;
	}
	if (player == 'T') {
		if (move_set->single_s_m_list->tail->posit->row == 'H')
			return TRUE;
	}
	return FALSE;
}
void maketurn(Board board, SingleSourceMovesList* move_set, Player player) {

	SingleSourceMovesListCell* curr = move_set->head;
	checkersPos* old_pos = curr->posit;
	curr = curr->next;
	Board newb;
	CopyBoardV2(&newb, board);
	while (curr != NULL) {
		if (curr->posit->col - 2 == old_pos->col)
			UpdatedBoard(old_pos, RIGHT, CAPTURE, board, &newb);

		if (curr->posit->col + 2 == old_pos->col)
			UpdatedBoard(old_pos, LEFT, CAPTURE, board, &newb);

		if (curr->posit->col - 1 == old_pos->col)
			UpdatedBoard(old_pos, RIGHT, MOVE, board, &newb);

		if (curr->posit->col + 1 == old_pos->col)
			UpdatedBoard(old_pos, LEFT, MOVE, board, &newb);

		old_pos = curr->posit;
		curr = curr->next;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j] = newb[i][j];
			}
		}

	}


}
void printmove(SingleSourceMovesList* move) {

	SingleSourceMovesListCell* curr = move->head;
	while (curr->next != NULL) {
		printf("%c%c -> %c%c ", curr->posit->row, curr->posit->col, curr->next->posit->row, curr->next->posit->col);
		printf("\n");
		curr = curr->next;

	}
}