#pragma once

#include <iostream>

void PrintStrSearch( const char* srcStr, const char* targetStr, int srcCursor, int searchCur, int targetCursor)
{
	printf( "\t%s\n", srcStr );
	printf( "\t" );
	for ( int i = 0; i < srcCursor + targetCursor; ++i )
	{
		printf( " " );
	}
	if ( srcStr[searchCur] == targetStr[targetCursor] )
	{
		printf( "+\n" );
	}
	else
	{
		printf( "|\n" );
	}
	printf( "\t" );
	for ( int i = 0; i < srcCursor; ++i )
	{
		printf( " " );
	}
	printf("%s\n\n", targetStr );
}

int FindSubStr_Brute(const char* srcStr, const char* targetStr, bool isPrintProcess)
{
	int idxSrc = 0;
	int count = 0;
	for ( ; srcStr[idxSrc] != '\0'; ++idxSrc )
	{
		int idxTarget = 0;
		for ( int idxSearchStart = idxSrc ; targetStr[idxTarget] != '\0'; ++idxTarget, ++idxSearchStart )
		{
			if ( isPrintProcess )
			{
				++count;
				if ( idxTarget == 0 )
				{
					printf( "%d", idxSrc );
				}
				else
				{
					printf( " " );
				}
				PrintStrSearch( srcStr, targetStr, idxSrc, idxSearchStart, idxTarget );
			}

			if ( srcStr[idxSearchStart] != targetStr[idxTarget] )
			{
				idxTarget = 0;
				break;
			}
		}
		if ( targetStr[idxTarget] == '\0' )
		{
			if ( isPrintProcess )
			{
				printf( "ºñ±³ È½¼ö: %d\n", count );
			}

			return idxSrc;
		}
	}
	return idxSrc;
}

void PrintKMP( const char* srcStr, const char* targetStr, int srcCursor, int targetCursor, int subShiftCursor )
{
	printf( "%s\n", srcStr );
	for ( int i = 0; i < srcCursor; ++i )
	{
		printf( " " );
	}
	if ( srcStr[srcCursor] == targetStr[targetCursor] )
	{
		printf( "+\n" );
	}
	else
	{
		printf( "|\n" );
	}
	for ( int i = 0; i < subShiftCursor; ++i )
	{
		printf( " " );
	}
	printf( "%s\n\n", targetStr );
}

void GetPattern( const char* subStr, int* patternArr, int size )
{
	for ( int i = 0, j = 1; j < size; )
	{
		if ( subStr[i] != subStr[j] )
		{
			if ( i == 0 )
			{
				j++;
			}
			else
			{
				i = patternArr[i];
			}
		}
		else
		{
			patternArr[j] = ++i;
			j++;
		}
	}
}

int FindSubStr_KMP( const char* srcStr, const char* subStr, int subStrSize, bool isPrintArr = false )
{
	int* patternArr = new int[subStrSize]();
	GetPattern( subStr, patternArr, subStrSize );

	if ( isPrintArr )
	{
		for ( int i = 0; i < subStrSize; ++i )
		{
			std::cout << patternArr[i] << " ";
		}
		std::cout << std::endl;
	}
	
	int i = 0;
	int j = 0;

	if ( isPrintArr )
	{
		PrintKMP( srcStr, subStr, i, j, i - j );
	}

	for ( ; srcStr[i] != 0 && subStr[j] != 0; )
	{
		if ( srcStr[i] == subStr[j] )
		{
			++i;
			++j;
		}
		else if ( j != 0 )
		{
			j = patternArr[j - 1];
		}
		else
		{
			++i;
		}

		if ( srcStr[i] == '\0' )
		{
			delete[] patternArr;
			return i - j;
		}

		if ( isPrintArr )
		{
			PrintKMP( srcStr, subStr, i, j, i - j );
		}
	}

	delete[] patternArr;
	return -1;
}

void CreateBadMatchTable( const char* subStr, int* table, int subStrSize, int tableSize, bool isPrintStr = false )
{
	for ( int subIdx = 0; subIdx < subStrSize - 1; ++subIdx )
	{
		const int charPos = subStr[subIdx];
		table[charPos] = subStrSize - subIdx - 1;
	}
	for ( int i = 0; i < tableSize; ++i )
	{
		if ( table[i] == 0 )
		{
			table[i] = subStrSize;
		}
	}
	
	if ( isPrintStr )
	{
		printf( "Table : " );
		for ( int i = 0; i < tableSize; ++i )
		{
			if ( table[i] != subStrSize )
			{
				printf( "%c:%d  ", (i), table[i]);
			}
		}
		printf( "\n" );
	}
}

int FindStr_BoyerMoore(const char* srcStr, const char* subStr, int subStrSize, bool isPrintStr = false)
{
	constexpr int tableSize = 93;
	int badMatchTable[tableSize] = { 0, };

	CreateBadMatchTable( subStr, badMatchTable, subStrSize, tableSize, isPrintStr );

	for ( int srcIdx = 0; srcStr[srcIdx] != '\0';)
	{
		int subIdx = subStrSize - 1;
		int searchIdx = srcIdx + subIdx;
		int matchCount = 0;

		for ( ; srcStr[searchIdx] == subStr[subIdx]; --subIdx, --searchIdx, ++matchCount )
		{
			if ( isPrintStr )
			{
				PrintKMP( srcStr, subStr, searchIdx, subIdx, srcIdx );
			}
		}
		if ( isPrintStr )
		{
			PrintKMP( srcStr, subStr, searchIdx, subIdx, srcIdx );
		}
		
		if ( subIdx == -1 )
		{
			return srcIdx;
		}

		const int curPos = srcStr[searchIdx] ;
		const int moveAmount = badMatchTable[curPos];
		if ( moveAmount == subStrSize )
		{
			srcIdx += moveAmount - matchCount;
		}
		else
		{
			srcIdx = moveAmount;
		}
	}
	return -1;
}