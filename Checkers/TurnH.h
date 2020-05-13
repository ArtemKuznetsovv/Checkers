#pragma once
#include "GeneralH.h"
#include "ListH.h"

//Q4
/*Recives game board and player name-B or T
Performing one move of player's checkers, which is the best move available according the given board*/
void Turn(Board board, Player player);
/*Auxiliary function of Turn.
Recives MultiPleSourceMovesList list and player name. Returns SingleSourceMovesList list that represente the best possible route of player's checkers*/
SingleSourceMovesList* FindOptimalMoveFromAllpieces(MultiPleSourceMovesList* all_moves, Player player);
/*Auxiliary function of Turn.
Recives MultiPleSourceMovesListCell cell and player name. If the best possible move of player's checker will cause to player's victory return TRUE. else, return FALSE*/
BOOL CheckWinCondition(MultiPleSourceMovesListCell* move_set, Player player);
/*Auxiliary function of Turn.
xxxxxx*/
void maketurn(Board board, SingleSourceMovesList* move_set, Player player);
/*
*/
unsigned short ListLength(SingleSourceMovesList* list);//calculates the list length
void printmove(SingleSourceMovesList* move);//prints the chosen move

//-------------------------------------------------------------------