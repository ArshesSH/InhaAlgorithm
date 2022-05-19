#pragma once

class Day2
{
public:
	static int GetGaussSumN( int n );
	static int SumOf( int a, int b );
	static void Day2Main();
	static void PrintSandglass( int n );
private:
	static int GaussSum( int min, int max );
	static int SumOfPostive( int a, int b );
};