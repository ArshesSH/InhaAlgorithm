#pragma once

#include <memory>
#include <stack>

template <typename K, typename V = int>
class BinarySearchTree
{
public:
	class Element
	{
	public:
		Element( const K& key, const V& value )
			:
			key( key ),
			value( value )
		{}

		~Element()
		{
			delete pLeft;
			pLeft = nullptr;
			delete pRight;
			pRight = nullptr;
		}

		Element( const Element& src )
			:
			key( key ),
			value( value )
		{}
		Element& operator=( const Element& src ) = default;

		bool operator<( const Element& rhs )
		{
			return key < rhs.key;
		}
		bool operator>( const Element& rhs )
		{
			return key > rhs.key;
		}
		bool operator==( const Element& rhs )
		{
			return key == rhs.key;
		}

		K GetKey() const
		{
			return key;
		}
		V GetValue() const
		{
			return value;
		}

		void SetValue( const V& value_in )
		{
			value = value_in;
		}
		Element* GetLeft() const
		{
			return pLeft;
		}
		Element* GetRight() const
		{
			return pRight;
		}
		
		void SetLeft( Element* pE )
		{
			pLeft = std::move(pE);
		}
		void SetRight( Element* pE )
		{
			pRight = std::move( pE );
		}

		bool CheckLeftIsLeaf( )
		{
			if (pLeft == nullptr )
			{
				return true;
			}
			return false;
		}
		bool CheckRightIsLeaf()
		{
			if (pRight == nullptr)
			{
				return true;
			}
			return false;
		}

	private:
		K key;
		V value;
		Element* pLeft = nullptr;
		Element* pRight = nullptr;
	};

public:
	BinarySearchTree() = default;
	BinarySearchTree( const BinarySearchTree& src )
	{
		*this = src;
	}
	BinarySearchTree& operator=( const BinarySearchTree& src )
	{
	}
	~BinarySearchTree()
	{
		delete pRoot;
		pRoot = nullptr;
	}

	void Add( K key, V value = V(0) )
	{
		auto node = new Element( key, value );

		// If Root
		if (pRoot == nullptr)
		{
			pRoot = std::move(node);
			node = nullptr;
			return;
		}
		
		// else
		Element* pCur = pRoot;
		for (; pCur != nullptr;)
		{
			// If aleady exist same key, than change value
			if (*pCur == *node)
			{
				pCur->SetValue( value );
				delete node;
				node = nullptr;
				return;
			}

			// If current key is greater than new node
			if (*pCur > *node)
			{
				//Check Left is Leaf, If so move node to leaf
				if (pCur->CheckLeftIsLeaf())
				{
					pCur->SetLeft( node );
					node = nullptr;
					return;
				}
				// Else Keep search
				pCur = pCur->GetLeft();
			}
			// Same as greater case
			else if (*pCur < *node)
			{
				if (pCur->CheckRightIsLeaf())
				{
					pCur->SetRight( node );
					node = nullptr;
					return;
				}
				pCur = pCur->GetRight();
			}
		}
	}

	Element* Search( K key )
	{
		for ( auto pCur = pRoot; pCur != nullptr; )
		{
			if ( pCur->GetKey() == key )
			{
				return pCur;
			}
			else if ( pCur->GetKey() > key )
			{
				if ( pCur->CheckLeftIsLeaf() )
				{
					return nullptr;
				}
				pCur = pCur->GetLeft();
			}
			else if ( pCur->GetKey() < key )
			{
				if ( pCur->CheckRightIsLeaf() )
				{
					return nullptr;
				}
				pCur = pCur->GetRight();
			}
		}
		return nullptr;
	}

	bool Remove( K key )
	{
		auto pTarget = Search( key );
		if ( pTarget == nullptr )
		{
			return false;
		}

		// If Left Child is empty
		if ( pTarget->CheckLeftIsLeaf() )
		{
			// Also Right Child is empty (it's leaf)
			if ( pTarget->CheckRightIsLeaf() )
			{
				delete pTarget;
				pTarget = nullptr;
				return true;
			}
			
			// If Left is Empty
			// Find Least Child and Copy values (Not include Child Pointers)
			auto pLeastChild = FindLeastChild( pTarget->GetRight() );
			*pTarget = *pLeastChild;
			return Remove( pLeastChild->GetKey() );
		
		}
		// If Right Child is empty
		else if ( pTarget->CheckRightIsLeaf() )
		{
			auto pGreatestChild = FindGreatestChild( pTarget->GetLeft() );
			*pTarget = *pGreatestChild;
			return Remove( pGreatestChild->GetKey() );
		}
		else
		{

		}

		return false;
	}

	template <typename F>
	void DoAscendingLoop( F func )
	{
		LoopInorder( pRoot, func );
	}

private:
	template <typename F>
	void LoopInorder( Element* pTarget, F func )
	{
		if ( pTarget != nullptr )
		{
			LoopInorder( pTarget->GetLeft(), func );
			func( pTarget );
			LoopInorder( pTarget->GetRight(), func );
		}
	}

	Element* FindGreatestChild( Element* pParent)
	{
		for ( auto pCur = pParent; pCur != nullptr; pCur = pCur->GetRight())
		{
			if ( pCur->CheckRightIsLeaf() )
			{
				return pCur;
			}
		}
		return nullptr;
	}
	Element* FindLeastChild( Element* pParent )
	{
		for ( auto pCur = pParent; pCur != nullptr; pCur = pCur->GetLeft() )
		{
			if ( pCur->CheckLeftIsLeaf() )
			{
				return pCur;
			}
		}
		return nullptr;
	}

private:
	Element* pRoot;
};