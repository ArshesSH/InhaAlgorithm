#pragma once

#include <memory>

template<typename T>
class DoubleLinkedList
{
public:
	class Element
	{
	public:
		Element(T data)
			:
			data(data)
		{}
		Element( T data, std::shared_ptr<Element>& pNext, std::shared_ptr<Element>& pPrev )
			:
			data( data ),
			pNext(pNext),
			pPrev(pPrev)
		{}

		std::shared_ptr<Element> push_front( T data_in, std::shared_ptr<Element>& pSrc )
		{
			auto node = std::make_shared<Element>( data_in, pSrc, pSrc->pPrev );
			pSrc->pPrev = node;
			return node;
		}

		std::shared_ptr<Element> push_back( T data_in, std::shared_ptr<Element>& pSrc )
		{
			auto node = std::make_shared<Element>( data_in, pSrc->pNext, pSrc );
			pSrc->pNext = node;
			return node;
		}

		T GetData() const
		{
			return data;
		}
		std::shared_ptr<Element>& GetNext()
		{
			return pNext;
		}
		std::shared_ptr<Element>& GetPrev()
		{
			return pPrev;
		}
		void SetNext( std::shared_ptr<Element>& pSrc )
		{
			pNext = pSrc;
		}
		void SetPrev( std::shared_ptr<Element>& pSrc )
		{
			pPrev = pSrc;
		}
		std::shared_ptr<Element> Disconnect()
		{
			auto pTmp = std::move( pNext );
			pNext = nullptr;
			pPrev = nullptr;
			return pTmp;
		}
	private:
		T data;
		std::shared_ptr<Element> pNext = nullptr;
		std::shared_ptr<Element> pPrev = nullptr;
	};

public:
	DoubleLinkedList() = default;
	DoubleLinkedList( const DoubleLinkedList& src )
	{
		*this = src;
	}
	DoubleLinkedList& operator=( const DoubleLinkedList& src )
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
	~DoubleLinkedList() = default;


	void push_front( T data )
	{
		if ( Empty() )
		{
			pHead = std::make_shared<Element>( data );
			pTail = pHead;
			++size;
		}
		else
		{
			pHead = pHead->push_front( data, pHead );
			++size;
		}
	}
	void push_back( T data )
	{
		if ( Empty() )
		{
			pHead = std::make_shared<Element>( data );
			pTail = pHead;
			++size;
		}
		else
		{
			pTail = pTail->push_back( data, pTail );
			++size;
		}
	}
	void insert( T data, int pos )
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
			push_front( data );
		}
		else if ( pos == size )
		{
			push_back( data );
		}
		else
		{
			auto tmp = std::make_shared<Element>( data, pCur->GetNext(), pCur );
			pCur->GetNext() = tmp;
			if ( tmp->GetNext() == nullptr )
			{
				pTail = tmp;
			}
		}
		++size;
	}

	bool pop_front( T& data )
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

	bool remove( int pos )
	{
		if ( !Empty() )
		{
			if ( pos == 0 )
			{
				pHead = pHead->GetNext();
				--size;
				return true;
			}
			else
			{
				if ( pos > size )
				{
					return false;
				}

				auto pPrev = pHead;
				for ( int i = 0; i < pos - 1; ++i )
				{
					pPrev = pPrev->GetNext();
				}

				auto pCur = pPrev->GetNext();

				if ( pCur == pTail )
				{
					pTail = pPrev;
				}
				pPrev->GetNext() = pCur->GetNext();
				pCur->GetNext()->SetPrev( pPrev );
				--size;
				return true;
			}
		}
		return false;
	}

	template<typename F>
	int find_pos( T data, F compairFunc ) const
	{
		std::shared_ptr<Element> pCur = pHead;
		int i = 0;
		for ( ; pCur != nullptr; ++i )
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
		return i;
	}

	template<typename F>
	int find_pos_reverse( T data, F compairFunc ) const
	{
		std::shared_ptr<Element> pCur = pTail;
		int i = size;
		for ( ; pCur != nullptr; --i )
		{
			if ( compairFunc( data, pCur->GetData() ) )
			{
				return i;
			}
			else
			{
				pCur = pCur->GetPrev();
			}
		}
		return i;
	}

	template<typename F>
	T find_if( T data, F compairFunc ) const
	{
		std::shared_ptr<Element> pCur = pHead;
		int i = 0;
		for ( ; pCur != nullptr; ++i )
		{
			if ( compairFunc( data, pCur->GetData() ) )
			{
				return pCur->GetData();
			}
			else
			{
				pCur = pCur->GetNext();
			}
		}
		return T{};
	}

	template<typename F>
	T find_if_reverse( T data, F compairFunc ) const
	{
		std::shared_ptr<Element> pCur = pTail;
		int i = size;
		for ( ; pCur != nullptr; --i )
		{
			if ( compairFunc( data, pCur->GetData() ) )
			{
				return pCur->GetData();
			}
			else
			{
				pCur = pCur->GetPrev();
			}
		}
		return T{};
	}

	template<typename F>
	void do_loop( F functor )
	{
		for ( std::shared_ptr<Element> pCur = pHead; pCur != nullptr; pCur = pCur->GetNext() )
		{
			functor( (T*)pCur.get() );
		}
	}

	template<typename F>
	void do_loop_reverse( F functor )
	{
		for ( std::shared_ptr<Element> pCur = pTail; pCur != nullptr; pCur = pCur->GetPrev() )
		{
			functor( (T*)pCur.get() );
		}
	}

	int Size() const
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
	int size = 0;
};