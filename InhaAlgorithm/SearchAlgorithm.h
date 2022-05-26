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
		int startPos = 0;
		int endPos = (int)list.size()-1;
		int midPos;
		bool isTarget = false;
		while ( startPos <= endPos )
		{
			midPos = ((endPos - startPos) / 2) + startPos;
			if ( target < list[midPos] )
			{
				endPos = midPos - 1;
			}
			else if ( target > list[midPos] )
			{
				startPos = midPos + 1;
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

