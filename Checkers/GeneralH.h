

#pragma once
//Includations:
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definitions:
#define Board_Size 8
#define FALSE 0
#define TRUE 1
#define CAPTURE 1
#define MOVE 0
#define LEFT 1
#define RIGHT -1
#define Max_Len 150

//Type Definitions and structs:
typedef int BOOL;
typedef struct _checkersPos
{
	char row;
	char col;
}checkersPos;
typedef unsigned char Board[Board_Size][Board_Size];
typedef unsigned char Player;
typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos* pos;
	unsigned short total_capture_so_far;
	struct _SingleSourceMovesTreeNode* next_move[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

typedef struct _SingleSourceMovesListCell {
	checkersPos* posit;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMoveList
{
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;

typedef struct _multiPleSourceMovesListCell
{
	SingleSourceMovesList* single_s_m_list;//==single_source_moves_list
	struct _multiPleSourceMovesListCell* next;
}MultiPleSourceMovesListCell;
typedef struct _multiPleSourceMovesList
{
	MultiPleSourceMovesListCell* head;
	MultiPleSourceMovesListCell* tail;
}MultiPleSourceMovesList;


/*-------------------------------------------------------------------
general system function
-------------------------------------------------------------------*/
/*Receives a given board, position of a checker on the board and direction of movement
If the current checker is able to make a "caputure" in the given dierection, returns TRUE. Else-returns FALSE.*/
BOOL canEat(int direction, Board board, checkersPos* pos);
/*Receives a given board and a position of a checker on the board
If the current checker is able to make a "caputure" on the given board, returns TRUE. Else-returns FALSE.*/
BOOL canEatG(Board board, checkersPos* pos);
/*Receives a given board, position of a checker on the board and direction of movement
If the current checker is able to make a a single move in the given dierection, returns TRUE. Else-returns FALSE.*/
BOOL canMove(int direction, Board board, checkersPos* pos);
/*Receives a given board and a position of a checker on the board
If the current checker is able to make a single move on the given board, returns TRUE. Else-returns FALSE.*/
BOOL canMoveG(Board board, checkersPos* pos);
/*Receives a given position of a checker on the board, and two intergers by refernce
Convets the data of the position into the two integers and updating their value*/
void updateRowCol(int* row, int* col, checkersPos* pos);
/*Receives a memory address and checks if the address is different than NULL value or not
*/
void build_default_board(Board b);/*/builds the default board which is stated in the project definition/*/


void alloCheck(void* ptr);/*/check Allocation/*/
void freeTreeRec(SingleSourceMovesTreeNode* root);//Recursive function which frees the tree

void free_Single_source_moves_list(SingleSourceMovesList* lst);
void free_Multiple_source_moves_list(MultiPleSourceMovesList* lst);
