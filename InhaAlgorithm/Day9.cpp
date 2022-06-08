#include "Day9.h"

#include <iostream>
#include <string>
#include <vector>

/*
* 다음의 함수를 사용하여 int값을 역으로 화면에 출력하는 코드 작성
* void reverseDisplay(int value)
* ex > reverseDisplay(12345)
*  > 54321
* void reverseDisplay(const string& s)
* ex > reverseDisplay("abcd")
*  > dcba
*/

void reverseDisplay( int value )
{
	const int nextValue = value / 10;
	std::cout << value % 10;
	if ( nextValue > 0 )
	{
		reverseDisplay( nextValue );
	}
}

void reverseDisplay( const std::string& s )
{
	static int destPos = s.size() - 1;
	static int curPos = 0;
	
	if ( curPos < destPos )
	{
		curPos++;
		reverseDisplay( s );
	}

	std::cout << s[curPos--];
	destPos--;
}

void Day9::ExRecursion()
{
	reverseDisplay( 4321 );
	reverseDisplay( "Hello World!" );
}

/*
* 다음과 같이 문자열의 모든 순열을 출력하는 재귀함수를 작성하라
* ex > abc
*	abc
*	acb
*	bac
*	bca
*	cab
*	cba
*/

void permute( const std::string& str, int iLeft, int iRight )
{
	std::string copied = str;
	if ( iLeft == iRight )
	{
		std::cout << copied << std::endl;
	}
	else
	{
		for ( int i = iLeft; i <= iRight; ++i )
		{
			std::swap( copied[iLeft], copied[i] );
			permute( copied, iLeft + 1, iRight );
			std::swap( copied[iLeft], copied[i] );
		}
	}
}

void Day9::ExRecursion2()
{

	permute( "abcd", 0, 3 );
}
