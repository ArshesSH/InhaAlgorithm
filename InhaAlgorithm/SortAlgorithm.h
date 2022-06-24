#pragma once

#include <iostream>
#include <stack>
#include <map>

template<typename T>
class SortAlgorithm
{
public:
	static void BubbleSort( T* arr, size_t size, bool isPrint = false )
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
				if ( isPrint )
				{
					PrintSortArr( arr, size, curPos, nextPos );
				}
			}
			if ( !isChanged )
			{
				isFinished = !isChanged;
				return;
			}
		}
	}

	static void BubbleSortOrigin( T* arr, size_t size, bool isPrint = false )
	{
		int i, j;
		for ( i = 0; i < size - 1; i++ )
		{
			for ( j = 0; j < size - i - 1; j++ )
			{
				if ( arr[j] > arr[j + 1] )
				{
					std::swap( arr[j], arr[j + 1] );
				}
				if ( isPrint )
				{
					PrintSortArr( arr, size, i, j );
				}
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
					PrintSortArr( arr, size, curPos, nextPos );
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
				PrintSortArr( arr, size, curPos, targetPos );
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
					PrintSortArr( arr, size, curPos, curPos - 1 );
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
				PrintSortArr( arr, size, curPos, nextPos );
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
					PrintSortArr( arr, arrSize, pivot, targetPos );
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
			highIdx = idxStack.top().second;
			lowIdx = idxStack.top().first;
			idxStack.pop();

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
						PrintSortArr( arr, arrSize, pivot, targetPos );
					}
				}

				idxStack.push( { pivot + 1, highIdx } );
				idxStack.push( { lowIdx, pivot - 1 } );
			}
		}
	}

	static void Merge( T* arr, T* mergeArr, int originSize, int lowIdx, int midIdx, int highIdx, bool isPrint = false )
	{
		for ( int i = lowIdx; i <= highIdx; ++i )
		{
			mergeArr[i] = arr[i];
		}

		int leftIdx = lowIdx;
		int rightIdx = midIdx + 1;
		int arrIdx = lowIdx;
		for ( ; leftIdx <= midIdx && rightIdx <= highIdx; ++arrIdx )
		{
			if ( mergeArr[leftIdx] <= mergeArr[rightIdx] )
			{
				arr[arrIdx] = mergeArr[leftIdx];
				++leftIdx;
				if ( isPrint )
				{
					PrintSortArr( arr, originSize, arrIdx, leftIdx );
				}
			}
			else
			{
				arr[arrIdx] = mergeArr[rightIdx];
				++rightIdx;
				if ( isPrint )
				{
					PrintSortArr( arr, originSize, arrIdx, rightIdx );
				}
			}

		}
		for ( int i = 0; i <= midIdx - leftIdx; ++i )
		{
			arr[arrIdx + i] = mergeArr[leftIdx + i];
			if ( isPrint )
			{
				PrintSortArr( arr, originSize, arrIdx, leftIdx );
			}
		}
	}

	static void MergeSort( T* arr, int originSize, bool isPrint = false )
	{
		T* mergeArr = new T[originSize];
		DoMergeSort( arr, mergeArr, originSize, 0, originSize - 1, isPrint );
		if ( isPrint )
		{
			PrintSortArr( arr, originSize, 0, 0 );
		}
	}

	static void DoMergeSort( T* arr, T* mergeArr, int originSize, int lowIdx, int highIdx, bool isPrint = false )
	{
		if ( lowIdx < highIdx )
		{
			int size = (highIdx + lowIdx) / 2;
			DoMergeSort( arr, mergeArr, originSize, lowIdx, size, isPrint );
			DoMergeSort( arr, mergeArr, originSize, size + 1, highIdx, isPrint );
			Merge( arr, mergeArr, originSize, lowIdx, size, highIdx, isPrint );
		}
	}

	static void MakeMaxHeapBook( T* arr, int arrSize, int left, int right, bool isPrint = false )
	{
		int root = arr[left];
		int bigChildIdx;
		int parentIdx = left;
		for ( ; parentIdx < (right + 1) / 2; parentIdx = bigChildIdx )
		{
			const int leftChildIdx = parentIdx * 2 + 1;
			const int rightChildIdx = leftChildIdx + 1;
			if ( rightChildIdx <= right && arr[leftChildIdx] < arr[rightChildIdx] )
			{
				bigChildIdx = rightChildIdx;
			}
			else
			{
				bigChildIdx = leftChildIdx;
			}
			if ( root >= arr[bigChildIdx] )
			{
				break;
			}
			arr[parentIdx] = arr[bigChildIdx];

			if ( isPrint )
			{
				PrintSortArr( arr, arrSize, parentIdx, bigChildIdx );
			}
		}
		arr[parentIdx] = root;

		if ( isPrint )
		{
			PrintSortArr( arr, arrSize, parentIdx, parentIdx );
		}
	}

	static void HeapSortBook( T* arr, size_t arrSize, bool isPrint = false )
	{
		for ( int i = (arrSize - 1) / 2; i >= 0; --i )
		{
			MakeMaxHeapBook( arr, arrSize, i, arrSize - 1, isPrint );
		}
		for ( int i = arrSize - 1; i > 0; --i )
		{
			std::swap( arr[0], arr[i] );
			MakeMaxHeapBook( arr, arrSize, 0, i - 1, isPrint );
		}
		if ( isPrint )
		{
			PrintSortArr( arr, arrSize, 0, 0 );
		}
	}

	static void MakeHeap( T* arr, int arrSize, bool isPrint = false)
	{
		int parentIdx = (arrSize-2) / 2;
		int bigChildIdx = parentIdx * 2 + 1;
		for ( ; parentIdx >= 0; --parentIdx )
		{
			const int childLeftIdx = parentIdx * 2 + 1;
			const int childRightIdx = childLeftIdx + 1;

			if ( childRightIdx <= arrSize && arr[childRightIdx] >= arr[childLeftIdx] )
			{
				bigChildIdx = childRightIdx;
			}
			else
			{
				bigChildIdx = childLeftIdx;
			}
			
			if ( arr[bigChildIdx] > arr[parentIdx] )
			{
				std::swap( arr[parentIdx], arr[bigChildIdx] );
			}

			if ( isPrint )
			{
				PrintSortArr( arr, arrSize+1, parentIdx, bigChildIdx );
			}

		}
		parentIdx = bigChildIdx;
		for ( ; parentIdx * 2 + 1 < arrSize; )
		{
			const int childLeftIdx = parentIdx * 2 + 1;
			const int childRightIdx = childLeftIdx + 1;

			int bigChildIdx = childLeftIdx;
			if ( childRightIdx <= arrSize && arr[childRightIdx] >= arr[childLeftIdx] )
			{
				bigChildIdx = childRightIdx;
			}
			else
			{
				bigChildIdx = childLeftIdx;
			}

			if ( arr[bigChildIdx] > arr[parentIdx] )
			{
				std::swap( arr[parentIdx], arr[bigChildIdx] );
				parentIdx = bigChildIdx;
			}
			else
			{
				break;
			}
			if ( isPrint )
			{
				PrintSortArr( arr, arrSize+1, parentIdx, bigChildIdx );
			}
		}
	}

	static void HeapSort( T* arr, size_t arrSize, bool isPrint = false )
	{
		
		for ( int i = arrSize - 1; i > 0; --i )
		{
			MakeHeap( arr, i, isPrint );
			std::swap( arr[0], arr[i] );
			if ( isPrint )
			{
				PrintSortArr( arr, arrSize, i, 0 );
			}
		}
	}

	static void CountingSort( int* arr, size_t arrSize, int maxNum)
	{
		int* countArr = new int[maxNum + 1]();
		int* resultArr = new int[maxNum]();

		for ( int i = 0; i < arrSize; ++i )
		{
			++countArr[arr[i]];
		}
		for ( int i = 1; i <= maxNum; ++i )
		{
			countArr[i] += countArr[i - 1];
		}
		for ( int i = 0; i < arrSize; ++i )
		{
			resultArr[--countArr[arr[i]]] = arr[i];
		}
		for ( int i = 0; i < arrSize; ++i )
		{
			arr[i] = resultArr[i];
		}
		delete[] countArr;
		delete[] resultArr;
	}

	static void CountingSortMap( int* arr, size_t arrSize )
	{
		std::map<int, int> countingMap;
		for ( int i = 0; i < arrSize; ++i )
		{
			countingMap[arr[i]]++;
		}

		int i = 0;
		for ( auto e : countingMap )
		{
			const int count = e.second;
			for ( int j = 0; j < e.second; ++j )
			{
				arr[i++] = e.first;
			}
		}
	}


private:
	static void PrintSortArr(T* arr, size_t size, size_t curPos, size_t targetPos)
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
