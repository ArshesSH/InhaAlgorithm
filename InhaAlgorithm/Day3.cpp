#include "Day3.h"

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>


void Day3::ChangeDecimal()
{
	int num;
	int destNotation;

	std::cout << "변환할 10진수 입력 : ";
	std::cin >> num;
	destNotation = InputNotation( "목표 진수 입력(2 ~ 36) : " );

	char changedNum[BUFSIZ] = { 0, };
	char reversedNum[BUFSIZ] = { 0, };

	ChangeDecimalTo(changedNum, destNotation, num );
	ReverseCharArr( reversedNum, changedNum, (int)strlen( changedNum ) );

	std::cout << reversedNum << std::endl;
}

void Day3::ChangeNotation()
{
	char numList[BUFSIZ] = { 0, };
	char changedList[BUFSIZ] = { 0, };
	char reversedList[BUFSIZ] = { 0, };
	int curNotation;
	int destNotation;

	curNotation = InputNotation( "현재 진수(2~36) 입력: " );
	InputNumInNotationRange( numList, curNotation );
	destNotation = InputNotation( "목표 진수 입력: " );

	ChangeDecimalTo( changedList, destNotation, ChangeToDecimal( numList, (int)strlen( numList ), curNotation ) );
	ReverseCharArr( reversedList, changedList, (int)strlen( changedList ) );

	std::cout << reversedList << std::endl;
}

// Check Number Range
void Day3::InputNumInNotationRange(char* numList, int curNotation)
{
	bool isInputOver;

	do
	{
		isInputOver = false;

		std::cout << "숫자 입력: ";
		std::cin >> numList;

		// Check each char for over notaion's range, and change lowwer to Upper
		for (int i = 0; numList[i] != '\0'; ++i)
		{
			if (numList[i] >= 'a' && numList[i] <= 'z')
			{
				numList[i] = toupper( numList[i] );
			}

			const char notationChar = GetNotationalNum(curNotation);

			if (numList[i] >= notationChar)
			{
				std::cout << " 범위 초과!!!" << std::endl;
				isInputOver = true;
				break;
			}
		}
	} while (isInputOver);
}

// Input notation in 2 <= n <= 36
int Day3::InputNotation( const char* msg )
{
	int notation;
	do
	{
		std::cout << msg;
		std::cin >> notation;
		if (std::cin.fail())
		{
			std::cout << "Input error!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (notation < 2 || notation > 36);

	return notation;
}

void Day3::ChangeDecimalTo(char* list, int destNotation, int targetNum)
{
	for (int i = 0 ; targetNum > 0; targetNum /= destNotation, ++i )
	{
		const int rest = targetNum % destNotation;

		list[i] = GetNotationalNum( rest );
	}
}

int Day3::ChangeToDecimal( char* list, int size, int notation )
{
	int num = 0;
	for ( int i = size - 1,  j = 0; i >= 0; --i, ++j )
	{
		num += (int)(list[i] - '0') * (int)pow(notation, j);
	}
	return num;
}


void Day3::ReverseCharArr( char* reversedList, const char* list, int size )
{
	for ( int i = size - 1, pos = 0; i >= 0; --i, pos++ )
	{
		reversedList[pos] = list[i];
	}
}

int Day3::GetNotationalNum( int num )
{
	return (num >= 10) ? ('A' + num - 10) : ('0' + num);
}

