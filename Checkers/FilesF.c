#include "FilesH.h"

/*-------------------------------------------------------------------
part 5 related functions
-------------------------------------------------------------------*/
void StoreBoard(Board board, char* filename)
{
	FILE* fptr = fopen(filename, "wb");
	if (fptr == NULL)
	{
		printf("File was not found. Error.\n");
		return;
	}


	unsigned char mask = 0;
	unsigned char tempmask = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j = j + 4)
		{
			if (board[i][j] == 'T')
			{
				tempmask = 0x40;
				mask = mask | tempmask;

			}
			else if (board[i][j] == 'B')
			{
				tempmask = 0x80;
				mask = mask | tempmask;

			}
			if (board[i][j + 1] == 'T')
			{
				tempmask = 0x10;
				mask = mask | tempmask;

			}
			else if (board[i][j + 1] == 'B')
			{
				tempmask = 0x20;
				mask = mask | tempmask;

			}
			if (board[i][j + 2] == 'T')
			{
				tempmask = 0x4;
				mask = mask | tempmask;

			}
			else if (board[i][j + 2] == 'B')
			{
				tempmask = 0x8;
				mask = mask | tempmask;

			}
			if (board[i][j + 3] == 'B')
			{
				tempmask = 0x2;
				mask = mask | tempmask;

			}
			else if (board[i][j + 3] == 'T')
			{
				tempmask = 0x1;
				mask = mask | tempmask;

			}
			fwrite(&mask, sizeof(unsigned char), 1, fptr);
			mask = 0;
		}

	}
	fclose(fptr);

}
/*-------------------------------------------------------------------
part 6 related functions
-------------------------------------------------------------------*/
void LoadBoard(char* filename, Board board)
{
	unsigned char recL, recR, cost, mask = 0xC0;
	int filesize; FILE* fptr;
	fptr = fopen(filename, "rb");
	if (fptr == NULL)
	{
		printf("File was not found. Error.\n");
		return;
	}
	fseek(fptr, 0, SEEK_END);
	filesize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	while (ftell(fptr) < filesize)
	{
		for (int i = 0; i < 8; i++)
		{
			fread(&recL, sizeof(unsigned char), 1, fptr);
			fread(&recR, sizeof(unsigned char), 1, fptr);
			for (int k = 0; k < 4; k++)
			{
				cost = recL & mask;
				if (cost == 0)
				{
					board[i][k] = ' ';
				}
				else if (cost == 0x40)
				{
					board[i][k] = 'T';
				}
				else
				{
					board[i][k] = 'B';
				}
				recL = recL << 2;
			}
			for (int k = 4; k < 8; k++)
			{
				cost = recR & mask;
				if (cost == 0)
				{
					board[i][k] = ' ';
				}
				else if (cost == 0x40)
				{
					board[i][k] = 'T';
				}
				else
				{
					board[i][k] = 'B';
				}
				recR = recR << 2;

			}
		}
	}
	fclose(fptr);
}