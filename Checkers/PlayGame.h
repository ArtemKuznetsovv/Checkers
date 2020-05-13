#pragma once
#include "GeneralH.h"
#include "TurnH.h"
#include "ListH.h"
//Q7
/*
Recives game board and a player name.
Runs the game while the starting player is the given player, until one of the players win*/
void PlayGame(Board board, Player starting_player);
/*Auxiliary function of PlayGame.
Recives game board. Return 'F' if there's no winner. Otherwise returns the name of the winning player*/
char CheckWinBoard(Board board);
/*Auxiliary function of PlayGame.
Recives game board. Return 'F' if both player have at least one checker. Otherwise returns the name of the player that still has checker left
while the other doesn't have any left*/
char condition1EndGame(Board board);
/*Auxiliary function of PlayGame.
Recives game board. Return 'F' if both player have at least one checker. Otherwise returns the name of the player that still has checker left
while the other doesn't have any left*/
BOOL condition2EndGame(Board board);
/*Auxiliary function of PlayGame.
Recives game board. Return 'F' if both player have at least one checker. Otherwise returns the name of the player that still has checker left
while the other doesn't have any left*/
BOOL condition3EndGame(Board board);
/*Auxiliary function of PlayGame.
Recives SingleSourceMovesList list. Prints the list that representes the best route that was chosen*/

void PrintBoardFinale(Board board);
BOOL check_if_can_move(MultiPleSourceMovesList* allmoves);//runs on the list which containts all the player moves and checks if there is a move which the player moves forward
//-------------------------------------------------------------------