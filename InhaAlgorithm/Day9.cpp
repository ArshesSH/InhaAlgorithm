#include "Day9.h"

#include <iostream>
#include <string>
#include <vector>

/*
* ������ �Լ��� ����Ͽ� int���� ������ ȭ�鿡 ����ϴ� �ڵ� �ۼ�
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
* ������ ���� ���ڿ��� ��� ������ ����ϴ� ����Լ��� �ۼ��϶�
* ex > abc
*	abc
*	acb
*	bac
*	bca
*	cab
*	cba
*/

std::pair<std::string, std::string> GetParts( const std::string str )
{
	if ( str.size() > 2 )
	{
		GetParts( str.substr( 1, str.size() - 2 ) );
	}
	else
	{
		return { str, {str[1],str[0]} };
	}
}

std::string GetPermutation( const std::string str )
{
	for ( int i = 0; i < str.size(); ++i )
	{

	}
}

void Day9::ExRecursion2()
{
	
}
