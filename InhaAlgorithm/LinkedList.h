#pragma once

#include <memory>

template<typename T>
class LinkedList
{
public:
	class Element
	{
	public:
		Element(T data, std::shared_ptr<Element> pAddr)
			:
			data(data),
			pNext(pAddr)
		{}
		~Element() = default;
		Element( const Element& src )
			:
			data(src.data)
		{
			if ( src.pNext != nullptr )
			{
				pNext = std::move( src.pNext );
			}
		}
		Element& operator=( const Element& src ) = default;

		std::shared_ptr<Element> CreateBackword(T data_in)
		{
			auto tmp = std::make_shared<Element>( data_in, nullptr );
			this->pNext = tmp;
			return tmp;
		}


		T GetData() const
		{
			return data;
		}
		std::shared_ptr<Element>& GetNext()
		{
			return pNext;
		}
		int CountSize()
		{
			if ( pNext != nullptr )
			{
				return pNext.get()->CountSize();
			}
			else
			{
				return 1;
			}
		}
		std::shared_ptr<Element> Disconnect()
		{
			auto pTmp = std::move(pNext);
			pNext = nullptr;
			return pTmp;
		}

	public:

	private:
		T data;
		std::shared_ptr<Element> pNext = nullptr;
	};

public:
	LinkedList() = default;
	LinkedList( const LinkedList& src )
	{
		*this = src;
	}
	LinkedList& operator=( const LinkedList& src )
	{
		if ( !Empty() )
		{
			pHead = nullptr;
		}
		if ( !src.Empty() )
		{
			pHead = std::move( src.pHead );
		}
		return *this;
	}
	~LinkedList() = default;

	void PushToHead( T data )
	{
		pHead = std::make_shared<Element>( data, pHead );
		if ( pTail == nullptr )
		{
			pTail = pHead;
		}
		++size;
	}

	void PushToTail( T data )
	{
		pTail = pTail->CreateBackword( data );
		++size;
	}

	void PushToPos( T data, int pos )
	{
		if ( pos > size )
		{
			pos = size;
		}

		auto pCur = pHead;
		for ( int i = 0; i < pos - 1; ++i )
		{
			pCur = pCur->GetNext();
		}

		if ( pos == 0 )
		{
			PushToHead(data);
		}
		else if ( pos == size )
		{
			PushToTail( data );
		}
		else
		{
			auto tmp = std::make_shared<Element>( data, pCur->GetNext() );
			pCur->GetNext() = tmp;
		}
		++size;
	}

	bool PopFromHead( T& data )
	{
		if ( !Empty() )
		{
			const T tmp = pHead->GetData();
			pHead = pHead->Disconnect();
			data = tmp;

			if ( pHead == nullptr )
			{
				pTail = nullptr;
			}

			--size;	
			return true;
		}
		else
		{
			return false;
		}
	}

	void DeleteNodeAtPos( int pos )
	{
		if ( !Empty() )
		{
			if ( pos > size )
			{
				pos = size;
			}

			auto pCur = pHead;
			for ( int i = 0; i < pos - 1; ++i )
			{
				pCur = pCur->GetNext();
			}

			if ( pos == 0 )
			{
				PopFromHead( data );
			}
			else if ( pos == size )
			{

			}
			else
			{

			}
			--size;
		}
	}

	template<typename F>
	int Find( T data, F compairFunc ) const
	{
		std::shared_ptr<Element> pCur = pHead;
		size_t i = 0;
		for (  ; pCur != nullptr; ++i )
		{
			if ( compairFunc( data, pCur->GetData() ) )
			{
				return i;
			}
			else
			{
				pCur = pCur->GetNext();
			}
		}
		return -1;
	}

	size_t Size() const
	{
		return size;
	}

	bool Empty() const
	{
		return pHead == nullptr;
	}
	
private:
	std::shared_ptr<Element> pHead = nullptr;
	std::shared_ptr<Element> pTail = nullptr;
	size_t size = 0;
};