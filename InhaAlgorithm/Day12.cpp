#include "Day12.h"

#include <iostream>
#include "StopWatch.h"
#include "SortAlgorithm.h"

void BubbleSort(int* targetArr, int arrSize)
{
	bool isFinished = false;
	char c;
	for ( int pass = 1; !isFinished; ++pass )
	{
		bool isChanged = false;

		std::cout << "�н� " << pass << std::endl;
		for ( int curPos = 0, nextPos = 1; nextPos < arrSize; ++curPos, ++nextPos )
		{
			if ( targetArr[curPos] > targetArr[nextPos] )
			{
				std::swap( targetArr[curPos], targetArr[nextPos] );
				c = '+';
				isChanged = true;
			}
			else
			{
				c = '-';
			}
			
			for ( int i = 0; i < arrSize; i++ )
			{
				std::cout << targetArr[i];
				if ( i == curPos )
				{
					std::cout << " " << c << " ";
				}
				else
				{
					std::cout << "   ";
				}
			}
			std::cout << std::endl;
		}
		if ( !isChanged )
		{
			isFinished = !isChanged;
			return;
		}
	}
}

void Day12::UseBubbleSort()
{
	int a[7] = { 6,4,3,7,1,9,8 };
	StopWatch timer;
	BubbleSort( a, 7 );
	timer.Stop();
	const double elapsed = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "�ɸ��ð� : " << elapsed << " �и� ��\n";
}

void Day12::UseSelectionSort()
{
	int a[7] = { 6,4,8,3,1,9,7 };
	int b[7] = { 6,4,8,3,1,9,7 };
	int c[7] = { 6,4,8,3,1,9,7 };
	int d[7] = { 6,4,8,3,1,9,7 };
	int e[7] = { 6,4,8,3,1,9,7 };
	int f[7] = { 6,4,8,3,1,9,7 };
	int g[8] = { 8, 1, 4, 2, 7, 6, 3, 5 };
	int h[8] = { 8, 1, 4, 2, 7, 6, 3, 5 };
	int i[8] = { 8, 1, 4, 2, 7, 6, 3, 5 };

	StopWatch timer;

	timer.Start();
	SortAlgorithm<int>::SelectionSort( a, 7, false );
	timer.Stop();
	const double elapsedFirst = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	SortAlgorithm<int>::SelectionSort( b, 7, true );
	std::cout << "1��° ��� ���� �ӵ� : " << elapsedFirst << " ms" << std::endl;	

	timer.Start();
	SortAlgorithm<int>::SelectionSortAlt( c, 7, false );
	timer.Stop();
	const double elapsedSecond = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	SortAlgorithm<int>::SelectionSortAlt( a, 7, true );
	std::cout << "2��° ��� ���� �ӵ� : " << elapsedSecond << " ms" << std::endl;

	timer.Start();
	SortAlgorithm<int>::BubbleSort( d, 7 );
	timer.Stop();
	const double elapsedThird = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "BubbleSort �ӵ� : " << elapsedSecond << " ms" << std::endl;

	timer.Start();
	SortAlgorithm<int>::InsertSort( e, 7, false );
	timer.Stop();
	const double elapsedFourth = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	SortAlgorithm<int>::InsertSort( f, 7, true );
	std::cout << "SelectSort ���� �ӵ� : " << elapsedFourth << " ms" << std::endl;

	timer.Start();
	//SortAlgorithm<int>::ShellSort( g, 7,7, false );
	timer.Stop();
	//const double elapsed5 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	SortAlgorithm<int>::ShellSort( h, 8, 8, true );
	std::cout << "SelectSort ���� �ӵ� : " << elapsedFourth << " ms" << std::endl;
}
