#pragma once

#include <vector>

class Day3
{
public:
	static void ChangeDecimal();
	static void ChangeNotation();
	static std::vector<int> PrimeNum( int n );
	static std::vector<int> PrimeNumOdd(int n);
	static std::vector<int> PrimeNumOddDivPrime( int n );
	static std::vector<int> PrimeNumSymmetry( int n );
	static void FindEfficientPrimeNum();
private:
	static void InputNumInNotationRange( char* numList, int curNotation );
	static int InputNotation( const char* msg );
	static void ChangeDecimalTo( char* list, int destNotation, int targetNum );
	static int ChangeToDecimal( char* list, int size, int notation );
	static void ReverseCharArr( char* reversedList, const char* list, int size );
	static int GetNotationalNum( int num );
};
