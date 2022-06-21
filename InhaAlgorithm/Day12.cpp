#include "Day12.h"

#include <iostream>
#include <vector>
#include "StopWatch.h"
#include "SortAlgorithm.h"

void BubbleSort(int* targetArr, int arrSize)
{
	bool isFinished = false;
	char c;
	for ( int pass = 1; !isFinished; ++pass )
	{
		bool isChanged = false;

		std::cout << "패스 " << pass << std::endl;
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
	std::cout << "걸린시간 : " << elapsed << " 밀리 초\n";
}

void Day12::UseSelectionSort()
{
	std::vector<int> origin;
	constexpr int size = 100;
	origin.reserve( size );
	for ( int i = 0; i < size; i++ )
	{
		origin.push_back( size - i);
	}

	std::vector<int> copy = origin;


	StopWatch timer;

	int* arr = &copy[0];
	timer.Start();
	SortAlgorithm<int>::SelectionSort( arr, size, false );
	timer.Stop();
	//copy = origin;
	const double elapsedFirst = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::SelectionSort( arr, size, true );
	std::cout << "1번째 방식 정렬 속도 : " << elapsedFirst << " ms" << std::endl;	
	
	copy = origin;
	timer.Start();
	SortAlgorithm<int>::SelectionSortAlt( arr, size, false );
	timer.Stop();
	//copy = origin;
	const double elapsedSecond = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::SelectionSortAlt( arr, size, true );
	std::cout << "2번째 방식 정렬 속도 : " << elapsedSecond << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::BubbleSort( arr, size );
	timer.Stop();
	//copy = origin;
	const double elapsedThird = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "BubbleSort 속도 : " << elapsedSecond << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::InsertSort( arr, size, false );
	timer.Stop();
	//copy = origin;
	const double elapsedFourth = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::InsertSort( arr, size, true );
	std::cout << "SelectSort 정렬 속도 : " << elapsedFourth << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::ShellSort( arr, size, size, false );
	timer.Stop();
	copy = origin;
	const double elapsed5 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::ShellSort( arr, size, size, true );
	std::cout << "shellSort 정렬 속도 : " << elapsed5 << " ms" << std::endl;

	int a[] = { 5,7,1,4,6,2,3,9,8 };
	copy = origin;
	timer.Start();
	SortAlgorithm<int>::QuickSortStack( a, 9, 0, 8, true );
	timer.Stop();
	const double elapsed6 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "QuickSort 정렬 속도 : " << elapsed6 << " ms" << std::endl;
}
