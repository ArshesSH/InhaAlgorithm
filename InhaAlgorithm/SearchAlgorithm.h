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


	static T* bsearch( const void* key, const void* base, size_t nmemb, size_t size, T(*compar)(const void*, const void*) )
	{
		T* pStart = (T*)base;
		T* pEnd = pStart + nmemb;
		T* pMid = ((pEnd - pStart) / 2) + pStart;

		bool isTarget = false;
		while ( compar( pStart, pEnd ) != 0 )
		{
			pMid = ((pEnd - pStart) / 2) + pStart;

			// Set MidPos to Left of same elements
			for ( T* pTmp = pMid; compar( pMid, pTmp ) == 0; pTmp -= size )
			{
				pMid = pTmp;
			}

			int compareResult = compar( key, pMid );

			if ( compareResult == -1 )
			{
				pEnd = pMid - size;
			}
			else if ( compareResult == 1 )
			{
				pStart = pMid + size;
			}
			else
			{
				isTarget = true;
				break;
			}
		}

		return isTarget ? pMid : NULL;
	}

};

