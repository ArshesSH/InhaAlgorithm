#include "Day9.h"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>

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
		Minus = 2,
		Asterisk = 3,
		Slash = 3,
		Tilde = 3
	};

public:
	Operators( const std::string str )
		:
		opStr(str)
	{
		switch (opStr[0] )
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
		case 'x':
		case 'X':
			opStr = '*';
			order = Order::Asterisk;
			break;
		case '/':
			order = Order::Slash;
			break;
		case '~':
			order = Order::Tilde;
			break;
		default:
			std::cout << "Input Error!\n";
			exit( 1 );
			break;
		}
	}

	bool operator>( const Operators& rhs ) const
	{
		return order > rhs.order;
	}
	bool operator<=( const Operators& rhs ) const
	{
		return order <= rhs.order;
	}
	bool operator==( char c ) const
	{
		return opStr[0] == c;
	}
	bool operator!=( char c ) const
	{
		return opStr[0] != c;
	}
	std::string GetOperator() const
	{
		return opStr;
	}

private:
	std::string opStr;
	Order order;
};

void PushOperator( std::stack<Operators>& opStack, std::queue<std::string>& postfix, const std::string& curOpStr )
{
	bool pushFlag = true;
	const Operators curOperator( curOpStr );

	while (pushFlag)
	{
		if (curOperator == '(')
		{
			opStack.push( curOperator );
			pushFlag = false;
		}
		else if(curOperator == ')')
		{
			for ( auto op = opStack.top(); op != '('; opStack.pop(), op = opStack.top())
			{
				postfix.push( op.GetOperator() );
			}
			opStack.pop();
			pushFlag = false;
		}
		else if (opStack.top() <= curOperator)
		{
			opStack.push( curOperator );
			pushFlag = false;
		}
		else if (opStack.top() > curOperator)
		{
			const std::string opStr = opStack.top().GetOperator();
			opStack.pop();
			postfix.push( opStr );
		}
	}
}

std::queue<std::string> InfixToPostfix( const std::string& infix )
{
	std::queue<std::string> postfix;
	std::stack<Operators> opStack;
	std::string passStr;
	std::string copiedInfix = "(" + infix + ")";
	// Parsing infix str
	for (auto i = 0; i < copiedInfix.size(); ++i)
	{
		// If Number
		if (isdigit( copiedInfix[i] ))
		{
			passStr += copiedInfix[i];
		}
		// If Space
		else if(copiedInfix[i] == ' ')
		{
			// Do Skip
		}
		// If Dot Keep track number (for float)
		else if (copiedInfix[i] == '.')
		{
			// If Dot at right of operand, then add 0 first
			if (!isdigit( copiedInfix[i - 1] ))
			{
				passStr += "0" + copiedInfix[i];
			}
			else
			{
				passStr += copiedInfix[i];
			}
		}
		// Rest operand, stop tracking number and push to 
		else
		{
			// If '-'on first letter or right of operand, Change to ~
			if (copiedInfix[i] == '-')
			{
				if (i == 0)
				{
					copiedInfix[i] = '~';
				}
				else if (!isdigit( copiedInfix[i - 1] ) && copiedInfix[i-1] != ')')
				{
					copiedInfix[i] = '~';
				}
			}

			if (passStr.size() != 0)
			{
				postfix.push( passStr );
				passStr.clear();
			}
			passStr += copiedInfix[i];
			PushOperator( opStack, postfix, passStr );
			passStr.clear();
		}
	}
	return postfix;
}

double CalcPostfix( std::queue<std::string>& postfix )
{
	std::stack<double> resultStack;
	
	while ( !postfix.empty() )
	{
		const std::string dataStr = postfix.front();
		postfix.pop();

		if (isdigit( dataStr[0] ))
		{
			resultStack.push( std::stod( dataStr ) );
		}
		else
		{
			const char operand = dataStr[0];

			if (operand == '+')
			{
				const double rhs = resultStack.top();
				resultStack.pop();
				const double lhs = resultStack.top();
				resultStack.pop();
				resultStack.push( lhs + rhs );
			}
			else if (operand == '-')
			{
				const double rhs = resultStack.top();
				resultStack.pop();
				const double lhs = resultStack.top();
				resultStack.pop();
				resultStack.push( lhs - rhs );
			}
			else if (operand == '*')
			{
				const double rhs = resultStack.top();
				resultStack.pop();
				const double lhs = resultStack.top();
				resultStack.pop();
				resultStack.push( lhs * rhs );
			}
			else if (operand == '/')
			{
				const double rhs = resultStack.top();
				resultStack.pop();
				const double lhs = resultStack.top();
				resultStack.pop();
				resultStack.push( lhs / rhs );
			}
			else if (operand == '~')
			{
				const double rhs = resultStack.top();
				resultStack.pop();
				resultStack.push( -1 * rhs );
			}
		}
	}
	return resultStack.top();
}

void PrintPostfixCalcResult( const std::string& infix )
{
	auto postfix = InfixToPostfix( infix );
	double result = CalcPostfix( postfix );
	std::cout << "Result = " << result << std::endl;
}

void Day9::UsePostfixCalculator()
{
	int menu = 1;
	while (menu)
	{
		std::cout << "\nCalculator\n"
			<< "0: Exit, 1: Keboard Input, 2: File Input : ";
		std::cin >> menu;
		if (menu == 0)
		{
			break;
		}
		else if (menu == 1)
		{
			std::string infix;

			std::cin.get();
			std::cout << "Input Calculation formula (Infix): ";
			std::getline( std::cin, infix );
			
			PrintPostfixCalcResult( infix );
		}
		else if (menu == 2)
		{
			std::vector<std::string> formulas;

			std::ifstream in( L"data/InfixFormulas.txt" );
			for (std::string str; std::getline( in, str );)
			{
				if (str.empty())
				{
					continue;
				}
				formulas.push_back( str );
			}
			in.close();

			for (const auto e : formulas)
			{
				PrintPostfixCalcResult( e );
			}
		}
	}
}

enum class Tower
{
	A,
	B,
	C,
	Count
};


int TowerNumFix( int n )
{
	if (n < 0)
	{
		return TowerNumFix((int)Tower::Count + n);
	}
	else if (n >= (int)Tower::Count)
	{
		return TowerNumFix( n - (int)Tower::Count);
	}
	else
	{
		return n;
	}
}

int	GetMoveDir(int ringCnt)
{
	// move right when even
	if ( ringCnt % 2 == 0 )
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool MoveRing( std::vector<int>& curTower, std::vector<int>& nextTower )
{
	// If curTower is empty skip
	if (curTower.empty())
	{
		return false;
	}

	const int curTowerTop = curTower[curTower.size() - 1];

	//Move if Next Tower is Empty or curTop < nextTop
	if (nextTower.empty())
	{
		curTower.pop_back();
		nextTower.push_back( curTowerTop );
		return true;
	}
	else if (curTowerTop < nextTower[nextTower.size() - 1])
	{
		curTower.pop_back();
		nextTower.push_back( curTowerTop );
		return true;
	}
	else
	{
		return false;
	}
}

void PrintTower( const std::vector<std::vector<int>>& towers, int ringCnt )
{
	printf( " A   B   C\n" );
	
	for ( int j = ringCnt - 1; j >= 0; --j )
	{
		for ( int i = 0; i < towers.size(); ++i )
		{
			const int towerTopPos = (int)towers[i].size() - 1;
			if ( j > towerTopPos )
			{
				printf( "[ ] " );
			}
			else
			{
				printf( "[%d] ", towers[i][j] );
			}
		}
		printf( "\n" );
	}

	printf( "\n" );
}

void Day9::ExTowerOfHanoi()
{
	int ringCntMax = 0;
	while ( ringCntMax <= 0 )
	{
		std::cout << "하노이의 탑\n링의 개수를 입력하세요 : ";
		std::cin >> ringCntMax;
	}

	constexpr int towerCnt = (int)Tower::Count;
	std::vector<std::vector<int>> towers(towerCnt);

	// Init Tower
	for ( int i = ringCntMax; i > 0; --i )
	{
		towers[(int)Tower::A].push_back( i );
	}
	PrintTower( towers, ringCntMax );

	int moveDir = GetMoveDir( ringCntMax );
	int moveCount;
	int curTowerPos = 0;
	int nextTowerPos = 0;

	// Get Result
	for (moveCount = 0; towers[towerCnt - 1].size() < ringCntMax; )
	{
		bool isMoved = false;

		// Try Move at CurTower
		for (int i = 1; (i <= towerCnt - 1) && !isMoved; ++i)
		{
			nextTowerPos = TowerNumFix( curTowerPos + (moveDir * i) );
			isMoved = MoveRing( towers[curTowerPos], towers[nextTowerPos] );
		}

		// Change Tower
		if (isMoved)
		{
			++moveCount;
			curTowerPos = TowerNumFix( nextTowerPos + moveDir );
			PrintTower( towers, ringCntMax );
		}
		else
		{
			curTowerPos = TowerNumFix( curTowerPos + moveDir );
		}
	}
	std::cout << "움직인 횟수 : " << moveCount << std::endl;
}
