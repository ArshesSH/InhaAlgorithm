#pragma once

template<typename T>
class SearchAlgorithm
{
public:
	static size_t LinearSearch( std::vector<T> list, T target )
	{
		size_t pos;
		for ( pos = 0; pos < list.size(); pos++ )
		{
			if ( list[pos] == target )
			{
				return pos;
			}
		}
		return pos;
	}

	static size_t LinearSearchAlter( std::vector<T> list, T target )
	{
		list.push_back( target );

		size_t pos;
		for ( pos = 0; list[pos] != target; pos++ )
		{
			;
		}
		return pos;
	}

	static int BinarySearch( const std::vector<T>& list, T target )
	{
		int startPos = -1;
		size_t endPos = list.size();
		size_t midPos = ((endPos - startPos) / 2) + startPos;

		bool isTarget = false;
		while ( midPos != startPos)
		{
			if ( target < list[midPos] )
			{
				endPos = midPos;
				midPos = ((endPos - startPos) / 2) + startPos;
			}
			else if ( target > list[midPos] )
			{
				startPos = midPos;
				midPos = ((endPos - startPos) / 2) + startPos;
			}
			else
			{
				isTarget = true;
				break;
			}
		}

		return isTarget ?  midPos : -1;
	}
};

