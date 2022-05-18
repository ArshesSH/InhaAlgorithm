#pragma once

class Day1
{
public:
	static int max4( int a, int b, int c, int d );
	static int med3( int a, int b, int c );
private:
	static int GetMax( int lhs, int rhs );
	static void Swap( int& lhs, int& rhs );
};