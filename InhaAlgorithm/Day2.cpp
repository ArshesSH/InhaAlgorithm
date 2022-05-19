#include "Day2.h"

#include <iostream>

void Day2::Day2Main()
{
	int n;
	std::cout << "����8�� : 1~n������ ���콺 ��, n �Է�: ";
	std::cin >> n;
	std::cout << GetGaussSumN( n ) << std::endl;

	int a, b;
	std::cout << "����9�� : a~b������ ���� ��, a,b �Է�: ";
	std::cin >> a >> b;
	std::cout << SumOf( a, b ) << std::endl;

	// ���� ����� �� ���
	std::cout << "����9�� : a~b������ ��� ��, a,b �Է�: ";
	std::cin >> a >> b;
	std::cout << SumOfPostive( a, b ) << std::endl;

}

void Day2::PrintSandglass( int n )
{
	const int maxCnt = (n * 2) - 1;
	int num = 1;
	for ( int y = 0; y < maxCnt; y++)
	{
		for ( int x = 0; x < num - 1; x++ )
		{
			std::cout << " ";
		}
		for ( int x = 0; x < maxCnt - (num - 1) * 2; x++ )
		{
			std::cout << num;
		}
		std::cout << std::endl;

		if ( y < n - 1 )
		{
			num++;
		}
		else
		{
			num--;
		}
	}
}

int Day2::GetGaussSumN( int n )
{
	return GaussSum(1,n);
}

int Day2::SumOf( int a, int b )
{
	if ( a < b )
	{
		return GaussSum( a, b );
	}
	return GaussSum( b, a );
}


int Day2::GaussSum( int min, int max )
{
	return (min + max) * ((max - min + 1) / 2);
}

int Day2::SumOfPostive( int a, int b )
{
	if ( a <= 0 || b <= 0 )
	{
		return -1;
	}
	return SumOf( a, b );
}