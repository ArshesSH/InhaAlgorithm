#pragma once

#include <functional>

template <typename D>
class HashMap
{
public:
	class Element
	{
	public:
		Element() = default;
		Element( D data, Element* pAddr )
			:
			data( data ),
			pNext( pAddr )
		{}
		~Element()
		{
			delete pNext;
			pNext = nullptr;
		}
		Element* Disconnect()
		{
			auto pTmp = pNext;
			pNext = nullptr;
			return pTmp;
		}
		Element* GetNext() const
		{
			return pNext;
		}
		void SetNext( Element* pSrc )
		{
			pNext = pSrc;
		}
	public:
		D data = 0;
	private:
		Element* pNext = nullptr;
	};



public:
	HashMap( std::function<int( D data )> GetKeyFunc )
		:
		hashSize( 13 ),
		map( new Element* [hashSize]() ),
		GetKeyFunc( GetKeyFunc )
	{
	}
	HashMap( int hashSize, std::function<int(D data)> GetKeyFunc )
		:
		hashSize( hashSize ),
		map( new Element*[hashSize]() ),
		GetKeyFunc( GetKeyFunc )
	{
	}
	~HashMap()
	{
		delete[] map;
	}

	void Add( D data )
	{
		const int hash = GetHash(data);
		map[hash] = new Element( data, map[hash] );
	}
	template <typename F>
	Element* SearchByData( D data, F Pred )
	{
		const int hash = GetHash( data );

		auto curNode = map[hash];
		for ( ; curNode != nullptr; )
		{
			if ( Pred(curNode->data, data) )
			{
				return curNode;
			}
			curNode = curNode->GetNext();
		}
		if ( curNode == nullptr )
		{
			return nullptr;
		}
		return nullptr;
	}

	Element* SearchByKey( int key )
	{
		const int hash = GetHashFromKey( key );

		auto curNode = map[hash];
		for ( ; curNode != nullptr; )
		{
			if ( key == GetKey(curNode->data) )
			{
				return curNode;
			}
			curNode = curNode->GetNext();
		}
		if ( curNode == nullptr )
		{
			return nullptr;
		}
		return nullptr;
	}

	template <typename F>
	bool RemoveByData( D data, F Pred )
	{
		const int hash = GetHash( data );

		auto curNode = map[hash];
		auto prevNode = map[hash];

		for ( ; curNode != nullptr; )
		{
			if ( Pred( curNode->data, data ) )
			{
				if ( curNode == prevNode )
				{
					curNode->Disconnect();
					return true;
				}

				prevNode->SetNext( curNode->GetNext() );
				curNode->Disconnect();
				curNode = nullptr;
				return true;
			}
			prevNode = curNode;
			curNode = curNode->GetNext();
		}
		return false;
	}

	bool RemoveByKey(int key)
	{
		const int hash = GetHashFromKey( key );

		auto curNode = map[hash];
		auto prevNode = map[hash];

		for ( ; curNode != nullptr; )
		{
			if ( key == GetKey( curNode->data ) )
			{
				if ( curNode == prevNode )
				{
					curNode->Disconnect();
					return true;
				}

				prevNode->SetNext( curNode->GetNext() );
				curNode->Disconnect();
				curNode = nullptr;
				return true;
			}
			prevNode = curNode;
			curNode = curNode->GetNext();
		}
		return false;
	}

	template <typename F>
	void DoLoop( F func )
	{
		for ( int i = 0; i < hashSize; ++i )
		{
			func( map, i );
		}
	}

	void RemoveAll()
	{
		for ( auto i = 0; i < hashSize; ++i )
		{
			delete map[i];
		}
	}

private:
	int GetKey( D data )
	{
		return GetKeyFunc( data );
	}
	int GetHash( D data )
	{
		return GetKeyFunc( data ) % hashSize;
	}
	int GetHashFromKey( int key )
	{
		return key % hashSize;
	}
	

private:
	int hashSize;
	Element** map = nullptr;
	std::function<int(D data)> GetKeyFunc;
};