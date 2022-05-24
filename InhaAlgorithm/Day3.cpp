#include "Day3.h"

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <limits>
#include <chrono>



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

bool IsPrimeNum( int n )
{
	for ( int divisor = 2; divisor < n; divisor++ )
	{
		const int mod = n % divisor;

		if ( mod == 0 )
		{
			return false;
		}
	}

	return true;
}

float GetTime(std::chrono::steady_clock::time_point last)
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

std::vector<int> Day3::PrimeNum(int n)
{
	std::vector<int> primeList;

	for ( int i = 2; i <= n; i++ )
	{
		if ( IsPrimeNum( i ) )
		{
			primeList.push_back( i );
		}
	}

	return primeList;
}

std::vector<int> Day3::PrimeNumOdd(int n)
{
	std::vector<int> primeList;
	primeList.push_back( 2 );
	primeList.push_back( 3 );

	for ( int i = 5; i <= n; i += 2 )
	{
		bool isPrime = true;
		for ( int j = 3; j < i; j+=2 )
		{
			if ( i % j == 0 )
			{
				isPrime = false;
				break;
			}
		}
		if ( isPrime )
		{
			primeList.push_back( i );
		}

	}
	return primeList;
}

std::vector<int> Day3::PrimeNumOddDivPrime( int n )
{
	std::vector<int> primeList;
	primeList.push_back( 2 );
	primeList.push_back( 3 );\
	int listSize = 1;
	for ( int i = 5; i <= n; i += 2 )
	{
		bool isPrime = true;

		for( int j = 0; j < listSize; j++ )
		{
			if ( i % primeList[j] == 0 )
			{
				isPrime = false;
				break;
			}
		}

		if ( isPrime )
		{
			primeList.push_back( i );
			listSize++;
		}
	}

	return primeList;
}


std::vector<int> Day3::PrimeNumSymmetry( int n )
{
	std::vector<int> primeList;
	primeList.push_back( 2 );
	primeList.push_back( 3 );
	
	for ( int i = 5; i < n; i += 2 )
	{
		bool isPrime = true;
		for ( int j = 1; primeList[j] * primeList[j] <= i; j++ )
		{
			if ( i % primeList[j] == 0 )
			{
				isPrime = false;
				break;
			}
		}

		if ( isPrime )
		{
			primeList.push_back( i );
		}
	}
	return primeList;
}



void Day3::FindEfficientPrimeNum()
{
	int n;
	std::cout << "2 이상의 정수를 입력하세요: ";
	std::cin >> n;

	std::vector<float> times;

	auto last = std::chrono::steady_clock::now();
	const std::vector<int> primeNumOrigin = PrimeNum( n );
	times.push_back( GetTime( last ) );
	for ( auto e : primeNumOrigin )
	{
		printf( "%d ", e );
	}
	printf( "\n" );

	last = std::chrono::steady_clock::now();
	const std::vector<int> primeNumOdd = PrimeNumOdd( n );
	times.push_back( GetTime( last ) );
	for ( auto e : primeNumOdd )
	{
		printf( "%d ", e );
	}
	printf( "\n" );

	last = std::chrono::steady_clock::now();
	const std::vector<int> primeNumOddDivPrime = PrimeNumOddDivPrime( n );
	times.push_back( GetTime( last ) );
	for ( auto e : primeNumOddDivPrime )
	{
		printf( "%d ", e );
	}
	printf( "\n" );

	last = std::chrono::steady_clock::now();
	const std::vector<int> primeNumSymmetry = PrimeNumSymmetry( n );
	times.push_back( GetTime( last ) );
	for ( auto e : primeNumSymmetry )
	{
		printf( "%d ", e );
	}
	printf( "\n" );

	

	for ( auto e : times )
	{
		printf( "%.8f\n", e );
	}
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

