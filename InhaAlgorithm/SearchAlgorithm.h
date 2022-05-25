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
};

