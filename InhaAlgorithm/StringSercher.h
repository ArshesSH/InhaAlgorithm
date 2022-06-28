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