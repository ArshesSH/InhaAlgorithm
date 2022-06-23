#include "Day12.h"

#include <iostream>
#include <vector>
#include "StopWatch.h"
#include "SortAlgorithm.h"
#include <random>

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

	constexpr int size = 10000;
	origin.reserve( size );

	// For Reverse
	for ( int i = 0; i < size; i++ )
	{
		origin.push_back( size - i);
	}

	// For Random
	//std::random_device rd;
	//std::mt19937 rng( rd() );
	//std::uniform_int_distribution<int> randGen( 0, size );
	//for ( int i = 0; i < size; i++ )
	//{
	//	origin.push_back( randGen( rng ) );
	//}


	std::vector<int> copy = origin;


	StopWatch timer;

	int* arr = &copy[0];
	/*
	timer.Start();
	SortAlgorithm<int>::SelectionSort( arr, size, false );
	timer.Stop();
	//copy = origin;
	const double elapsed1 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::SelectionSort( arr, size, true );
	std::cout << "SelectionSort 1 속도 : " << elapsed1 << " ms" << std::endl;
	
	copy = origin;
	timer.Start();
	SortAlgorithm<int>::SelectionSortAlt( arr, size, false );
	timer.Stop();
	//copy = origin;
	const double elapsed2 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::SelectionSortAlt( arr, size, true );
	std::cout << "SelectionSort 2 속도 : " << elapsed2 << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::BubbleSort( arr, size );
	timer.Stop();
	//copy = origin;
	const double elapsed3 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "BubbleSort 속도 : " << elapsed3 << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::InsertSort( arr, size, false );
	timer.Stop();
	//copy = origin;
	const double elapsed4 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::InsertSort( arr, size, true );
	std::cout << "SelectSort 정렬 속도 : " << elapsed4 << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::ShellSort( arr, size, size, false );
	timer.Stop();
	copy = origin;
	const double elapsed5 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	//SortAlgorithm<int>::ShellSort( arr, size, size, true );
	std::cout << "shellSort 정렬 속도 : " << elapsed5 << " ms" << std::endl;

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::QuickSortStack( arr, size, 0, size-1, false );
	timer.Stop();
	copy = origin;
	const double elapsed6 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "QuickSort 정렬 속도 : " << elapsed6 << " ms" << std::endl;


	copy = origin;
	timer.Start();
	SortAlgorithm<int>::MergeSort( arr, size, false );
	timer.Stop();
	copy = origin;
	const double elapsed7 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "MergeSort 정렬 속도 : " << elapsed7 << " ms" << std::endl;
	*/

	copy = origin;
	timer.Start();
	SortAlgorithm<int>::HeapSort( arr, size, false );
	timer.Stop();
	copy = origin;
	const double elapsed8 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "HeapSort 정렬 속도 : " << elapsed8 << " ms" << std::endl;

}
