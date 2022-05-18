#include <cstdio>
#include "Day1.h"

int main()
{
	while ( true )
	{
		int a, b, c;
		printf( "input 3 values : " );
		scanf_s( "%d %d %d", &a, &b, &c );

		printf( "medium = %d\n\n", Day1::med3( a, b, c ) );
	}


	return 0;
}