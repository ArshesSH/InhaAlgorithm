#include "Day9.h"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

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

class Operators
{
public:
	enum class Order
	{
		LeftParentheses = 0,
		RightParentheses = 0,
		Plus = 1,
		Minus = 1,
		Asterisk = 2,
		Slash = 2
	};

public:
	Operators( const std::string str )
		:
		opChar(str[0])
	{
		switch ( opChar )
		{
		case '(':
			order = Order::LeftParentheses;
			break;
		case ')':
			order = Order::RightParentheses;
			break;
		case '+':
			order = Order::Plus;
			break;
		case '-':
			order = Order::Minus;
			break;
		case '*':
			order = Order::Asterisk;
			break;
		case '/':
			order = Order::Slash;
			break;
		}
	}

	bool operator>( const Operators& rhs ) const
	{
		return order > rhs.order;
	}
	bool operator==( const char c ) const
	{
		return opChar == c;
	}

private:
	char opChar;
	Order order;
};

std::queue<std::string> InfixToPostfix( const std::string& s )
{
	std::queue<std::string> postfix;
	std::stack<Operators> OpStack;
	std::string passStr;
	postfix.push( "(" );
	for ( const auto c : s )
	{
		if ( isdigit( c ) )
		{
			passStr += c;
		}
		else if ( c == '-' )
		{

		}
	}

	postfix.push( ")" );
	return postfix;
}

void Day9::UsePostfixCalculator()
{

}
