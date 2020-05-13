#pragma once

#include "GeneralH.h"
//Q5
/*Recives game board and a filename.
Saves the board set in a binary file while each free cell represented by 2 bits '00', each 'T' checker cell represented by 2 bits '01'
each 'B' checker cell represented by 2 bits '10'
*/
void StoreBoard(Board board, char* filename);
//-------------------------------------------------------------------
//Q6
/*Recives game board and a filename.
Loads the board set from a binary file with the name 'filename'. Each 2 bits '00' representes a free cell
,each 2 bits '01' representes a 'T' checker cell
each 2 bits '10' representes a 'B' checker cell
*/
void LoadBoard(char* filename, Board board);
//-------------------------------------------------------------------

