#pragma once

#include "GeneralH.h"

/*-------------------------------------------------------------------
part 1 related functions
-------------------------------------------------------------------*/
/*Recives a given board and a position on the board
If there's a checker on the current position on the board, returns a SingleSourceMovesTree that representes all of the possible moves of the current checker
Else, returns NULL*/
SingleSourceMovesTree* FindBestSingleSource(Board board, checkersPos* pos);
/*Auxiliary function of FindBestSingleSource
Returns SingleSourceMovesTreeNode node that representes the root of all the possible moves from pos on board*/
SingleSourceMovesTreeNode* FindBestSingleSourceAux(SingleSourceMovesTreeNode* root, Board board, checkersPos* pos);
/*Auxiliary function of FindBestSingleSourceAux.
Build SingleSourceMovesTree in a recursive way of captures (if there are any) for the checker*/
void SendRecourEats(SingleSourceMovesTreeNode* root, Board board, checkersPos* pos);
/*Auxiliary function of FindBestSingleSourceAux.
Build SingleSourceMovesTree in a recursive way of single-moves (if there are any) for the checker*/
void SendMoveOne(SingleSourceMovesTreeNode* root, Board board, checkersPos* pos);
/*Updates board of a checker according to the kind of movement (sinlge move or capture) that was done and the direction that was done
Updates occur accroding to the board that belongs to beofre of the movemnt, and updating the new board by refernce of the the position of the checker*/
void UpdatedBoard(checkersPos* oldpos, int direction, int move, Board oldboard, Board* newboard);
/*Auxiliary function of FindBestSingleSourceAux.
RReturns new position of a checker according to the kind of movement (sinlge move or capture) that was done and the direction that was done*/
checkersPos* UpdatedPos(checkersPos* curr, int direction, int move, Board board);
/*Returns new node of SingleSourceMovesTree of a checker according to the kind of movement (sinlge move or capture) that was done and the direction that was done
*/
SingleSourceMovesTreeNode* UpdateNode(int typeOfMove, SingleSourceMovesTreeNode* root, checkersPos* pos, Board newboard);
//-------------------------------------------------------------------
//Q1-Second Part (Q1P2)
void CopyBoard(SingleSourceMovesTreeNode* node, Board board);//copies into the value "board" of node , the board .
void CopyBoardV2(Board* new_board, Board old_board);//copies into new_board the existent board.												


/*Recives SingleSourceMovesTreeNode which related to a SingleSourceMovesTree of a checker
Trims all the branches that are not part of the best route of the tree-the longest route*/
int TrimTree(SingleSourceMovesTreeNode* node);
/*Auxiliary function of TrimTree. Recives SingleSourceMovesTreeNode.
If the tree node is a leaf, returns TRUE. else return FALSE*/
BOOL isLeaf(SingleSourceMovesTreeNode* node);
//-------------------------------------------------------------------