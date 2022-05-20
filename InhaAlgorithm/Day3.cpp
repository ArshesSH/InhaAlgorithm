#include "Day3.h"

#include <iostream>
#include <cmath>
#include <cstring>


void Day3::ChangeDecimal()
{
	int num;
	int destNotation;
	std::cout << "변환할 10진수 입력 : ";
	std::cin >> num;
	do
	{
		std::cout << "목표 진수 입력( 2~36) : ";
		std::cin >> destNotation;
	} while ( destNotation < 2 || destNotation > 36 );

	char changedNum[BUFSIZ] = { 0, };
	char reversedNum[BUFSIZ] = { 0, };
	ChangeDecimalTo(changedNum, destNotation, num );
	ReverseCharArr( reversedNum, changedNum, strlen( changedNum ) );
	std::cout << reversedNum << std::endl;
}

void Day3::ChangeNotation()
{
	char numList[BUFSIZ] = { 0, };
	char changedList[BUFSIZ] = { 0, };
	int curNotation;
	int destNotation;
	
	do
	{
		std::cout << "현재 진수(2~36) 입력: ";
		std::cin >> curNotation;
	} while ( curNotation < 2 || curNotation > 36 );

	std::cout << "숫자 입력: ";
	std::cin >> numList;
	do
	{
		std::cout << "목표 진수 입력: ";
		std::cin >> destNotation;
	} while ( destNotation < 2 || destNotation > 36 );

	ChangeDecimalTo( changedList, destNotation, ChangeToDecimal( numList, strlen( numList ), curNotation ) );
	std::cout << changedList << std::endl;
}

void Day3::ChangeDecimalTo(char* list, int destNotation, int targetNum)
{
	for (int i = 0 ; targetNum > 0; targetNum /= destNotation, ++i )
	{
		const int rest = targetNum % destNotation;

		const char changedRest = (rest >= 10) ? ('A' + rest - 10) : ('0' + rest);
		list[i] = changedRest;
	}
}

int Day3::ChangeToDecimal( char* list, int size, int notation )
{
	int num = 0;
	for ( int i = size - 1,  j = 0; i >= 0; --i, ++j )
	{
		num += (list[i] - '0') * pow(notation, j);
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
