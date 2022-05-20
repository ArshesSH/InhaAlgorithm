#pragma once


class Day3
{
public:
	static void ChangeDecimal();
	static void ChangeNotation();
private:
	static void ChangeDecimalTo( char* list, int destNotation, int targetNum );
	static int ChangeToDecimal( char* list, int size, int notation );
	static void ReverseCharArr( char* reversedList, const char* list, int size );
};