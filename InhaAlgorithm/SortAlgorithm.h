#pragma once

#include <iostream>
#include <stack>

template<typename T>
class SortAlgorithm
{
public:
	static void BubbleSort( T* arr, size_t size )
	{
		bool isFinished = false;

		for ( int pass = 1; !isFinished; ++pass )
		{
			bool isChanged = false;

			for ( int curPos = 0, nextPos = 1; nextPos < size; ++curPos, ++nextPos )
			{
				if ( arr[curPos] > arr[nextPos] )
				{
					std::swap( arr[curPos], arr[nextPos] );
					isChanged = true;
				}
			}
			if ( !isChanged )
			{
				isFinished = !isChanged;
				return;
			}
		}
	}

	static void SelectionSort( T* arr, size_t size, bool isPrint = false )
	{
		for ( int startPos = 0; startPos < size; ++startPos )
		{
			int curPos = startPos;
			int nextPos = startPos + 1;
			for ( ; nextPos < size; ++nextPos )
			{
				if ( arr[curPos] > arr[nextPos] )
				{
					std::swap( arr[curPos], arr[nextPos] );
				}
				if ( isPrint )
				{
					PrintSelectionSort( arr, size, curPos, nextPos );
				}
			}
		}
	}
	static void SelectionSortAlt( T* arr, size_t size, bool isPrint = false )
	{
		for ( int startPos = 0; startPos < size; ++startPos )
		{
			int targetPos = startPos;
			int curPos = startPos;
			int nextPos = startPos + 1;
			for ( ; nextPos < size; ++nextPos )
			{
				if ( arr[curPos] > arr[nextPos] )
				{
					targetPos = nextPos;
				}
			}
			std::swap( arr[curPos], arr[targetPos] );
			if ( isPrint )
			{
				PrintSelectionSort( arr, size, curPos, targetPos );
			}
		}
	}
	static void InsertSort( T* arr, size_t size, bool isPrint = false )
	{
		
		for ( int startPos = 0 ; startPos < size; ++startPos )
		{
			for ( int curPos = startPos; (curPos > 0 && curPos < size ); --curPos )
			{
				if ( arr[curPos] < arr[curPos - 1] )
				{
					std::swap( arr[curPos], arr[curPos - 1] );
				}
				if ( isPrint )
				{
					PrintSelectionSort( arr, size, curPos, curPos - 1 );
				}
			}
		}
	}

	static void ShellSort( T* arr, size_t size, size_t sortSize, bool isPrint = false )
	{
		sortSize = sortSize / 2;

		if ( sortSize == 0 )
		{
			InsertSort(arr, size, isPrint);
			return;
		}
		for ( int curPos = 0, nextPos = curPos + sortSize; nextPos < size; curPos++, nextPos++ )
		{
			if ( arr[curPos] > arr[nextPos] )
			{
				std::swap( arr[curPos], arr[nextPos] );
			}
			for ( int prevPos = curPos - sortSize, startPos = curPos; prevPos >= 0; startPos -= sortSize, prevPos -= sortSize )
			{
				if ( arr[prevPos] > arr[startPos] )
				{
					std::swap( arr[prevPos], arr[startPos] );
				}
			}

			if ( isPrint )
			{
				PrintSelectionSort( arr, size, curPos, nextPos );
			}
		}
		ShellSort( arr, size, sortSize, isPrint );
	}

	static void QuickSortRecursion( T* arr, size_t arrSize, int lowIdx, int highIdx, bool isPrint = false )
	{
		if ( lowIdx < highIdx )
		{
			int pivot = highIdx;
			int targetPos = lowIdx - 1;

			// Partition
			while ( pivot != targetPos )
			{
				if ( pivot > targetPos )
				{
					++targetPos;
					if ( arr[pivot] < arr[targetPos] )
					{
						std::swap( arr[pivot], arr[targetPos] );
						std::swap( pivot, targetPos );
					}
				}
				else if ( pivot < targetPos )
				{
					--targetPos;
					if ( arr[pivot] > arr[targetPos] )
					{
						std::swap( arr[pivot], arr[targetPos] );
						std::swap( pivot, targetPos );
					}
				}
				if ( isPrint )
				{
					PrintSelectionSort( arr, arrSize, pivot, targetPos );
				}
			}

			QuickSortRecursion( arr, arrSize, lowIdx, pivot - 1, isPrint );
			QuickSortRecursion( arr, arrSize, pivot + 1, highIdx, isPrint );
		}
	}
	
	static void QuickSortStack( T* arr, size_t arrSize, int lowIdx, int highIdx, bool isPrint = false )
	{
		std::stack<std::pair<int, int>> idxStack;

		idxStack.push( { lowIdx, highIdx } );

		while ( !idxStack.empty() )
		{
			int pivot = idxStack.top().second;
			int targetPos = idxStack.top().first - 1;
			idxStack.pop();

			if ( targetPos < pivot )
			{
				// Partition
				while ( pivot != targetPos )
				{
					if ( pivot > targetPos )
					{
						++targetPos;
						if ( arr[pivot] < arr[targetPos] )
						{
							std::swap( arr[pivot], arr[targetPos] );
							std::swap( pivot, targetPos );
						}
					}
					else if ( pivot < targetPos )
					{
						--targetPos;
						if ( arr[pivot] > arr[targetPos] )
						{
							std::swap( arr[pivot], arr[targetPos] );
							std::swap( pivot, targetPos );
						}
					}
					if ( isPrint )
					{
						PrintSelectionSort( arr, arrSize, pivot, targetPos );
					}
				}

				idxStack.push( { pivot + 1, highIdx } );
				idxStack.push( { lowIdx, pivot - 1 } );
			}
		}
	}

private:
	static void PrintSelectionSort(T* arr, size_t size, size_t curPos, size_t targetPos)
	{
		for ( size_t i = 0; i < size; ++i )
		{
			if ( i == curPos )
			{
				std::cout << " * ";
			}
			else if ( i == targetPos )
			{
				std::cout << " + ";
			}
			else
			{
				std::cout << "   ";
			}
		}
		std::cout << std::endl;
		for ( size_t i = 0; i < size; ++i )
		{
			std::cout << " " << arr[i] << " ";
		}
		std::cout << std::endl;
	}
private:

};
