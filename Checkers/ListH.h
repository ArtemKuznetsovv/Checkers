#pragma once
#include "GeneralH.h"
#include "TreeH.h"
/*-------------------------------------------------------------------
part 2 related functions
-------------------------------------------------------------------*/

//Q2
//Recives SingleSourceMovesTree and returns SingleSourceMovesList that representes the best route of the tree-the longest route*/
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* tree);
/*Auxiliary function of FindSingleSourceOptimalMove.
Recives SingleSourceMovesList list and initialize it*/
void initializeList(SingleSourceMovesList* list);
/*Auxiliary function of FindSingleSourceOptimalMove.
Recives SingleSourceMovesList and SingleSourceMovesTreeNode node and builds a list from the SingleSourceMovesTreeNode node*/
void buildList(SingleSourceMovesList* list, SingleSourceMovesTreeNode* root);
/*Auxiliary function of FindSingleSourceOptimalMove.
Recives SingleSourceMovesListCell cell and SingleSourceMovesTreeNode node and builds a new SingleSourceMovesListCell cell from the SingleSourceMovesTreeNode node*/
void updatedListCell(SingleSourceMovesTreeNode* root, SingleSourceMovesListCell* node);
/*Auxiliary function of FindSingleSourceOptimalMove.
Recives SingleSourceMovesList list and SingleSourceMovesListCell cell and adds the cell to the end of the list*/
void addToEndOfList(SingleSourceMovesList* list, SingleSourceMovesListCell* node);
//-------------------------------------------------------------------
//Q3
/*Recives given board and name of player-T or B
Returns MultiPleSourceMovesList list that representes all the best routes of all the checkers of the given player*/
MultiPleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
/*Auxiliary function of FindAllPossiblePlayerMoves
Recives MultiPleSourceMovesList list and initialize it*/
void initializeListBestMove(MultiPleSourceMovesList* list);
/*Auxiliary function of FindAllPossiblePlayerMoves.
Recives MultiPleSourceMovesList list and SingleSourceMovesList list and adds the SingleSourceMovesList list to the end of the MultiPleSourceMovesList list*/
void addToEndOfBestMoves(MultiPleSourceMovesList* list, SingleSourceMovesList* listforOnePlayer);
/*Auxiliary function of FindAllPossiblePlayerMoves.
Recives two integers and checkersPos position. Concerts from the two intergers that represente a position, into checkersPos data type*/
void FromRowAndColToPos(int row, int col, checkersPos* pos);
/*Auxiliary function of FindAllPossiblePlayerMoves.
Recives SingleSourceMovesList list and creates new MultiPleSourceMovesListCell according to the given SingleSourceMovesList list*/
MultiPleSourceMovesListCell* Allocate_MultipleSourceMovesListCell(SingleSourceMovesList* lst);
//-------------------------------------------------------------------