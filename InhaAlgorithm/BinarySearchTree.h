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
		{
			pLeft = nullptr;
			pRight = nullptr;
		}

		~Element() = default;
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

		void SetKey( const K& key_in )
		{
			key = key_in;
		}
		void SetValue( const V& value_in )
		{
			value = value_in;
		}
		std::shared_ptr<Element>& GetLeft()
		{
			return pLeft;
		}
		std::shared_ptr<Element>& GetRight()
		{
			return pRight;
		}
		
		void SetLeft( std::shared_ptr<Element>& pE )
		{
			pLeft = std::move(pE);
		}
		void SetRight( std::shared_ptr<Element>& pE )
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
		std::shared_ptr<Element> pLeft;
		std::shared_ptr<Element> pRight;
	};

public:
	BinarySearchTree() = default;
	~BinarySearchTree()
	{
		while ( pRoot )
		{
			Remove( pRoot->GetKey() );
		}
	}

	void Add( K key, V value = V(0) )
	{
		auto node = std::make_shared<Element>( key, value );

		// If Root
		if (pRoot == nullptr)
		{
			pRoot = std::move(node);
			return;
		}
		
		// else
		std::shared_ptr<Element> pCur = pRoot;
		for (; pCur != nullptr;)
		{
			// If aleady exist same key, than change value
			if (*pCur == *node)
			{
				pCur->SetValue( value );
				return;
			}

			// If current key is greater than new node
			if (*pCur > *node)
			{
				//Check Left is Leaf, If so move node to leaf
				if (pCur->CheckLeftIsLeaf())
				{
					pCur->SetLeft( node );
					return;
				}
				// Else Keep search
				pCur = pCur->GetLeft();
			}
			// Same as greater case
			if (*pCur < *node)
			{
				if (pCur->CheckRightIsLeaf())
				{
					pCur->SetRight( node );
					return;
				}
				pCur = pCur->GetRight();
			}
		}
	}

	std::shared_ptr<Element> Search( K key )
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
		return _Remove( key, pRoot );
	}


	template <typename F>
	void DoAscendingLoop( F func )
	{
		LoopInorder( pRoot, func );
	}

private:
	bool _Remove( K key, std::shared_ptr<Element>& p )
	{
		if ( p != nullptr )
		{
			const auto& curKey = p->GetKey();
			if ( key < curKey )
			{
				return _Remove( key, p->GetLeft() );
			}
			else if ( key > curKey )
			{
				return _Remove( key, p->GetRight() );
			}
			else if ( key == curKey )
			{
				if ( !p->GetLeft() )
				{
					p = p->GetRight();
				}
				else if ( !p->GetRight() )
				{
					p = p->GetLeft();
				}
				else
				{
					std::shared_ptr<Element> q = p->GetLeft();
					while ( q->GetRight() )
					{
						q = q->GetRight();
					}
					const auto childKey = q->GetKey();
					p->SetKey( childKey );
					_Remove( childKey, p->GetLeft() );
				}
				return true;
			}
			return false;
		}
		return false;
	}

	template <typename F>
	void LoopInorder( const std::shared_ptr<Element>& pTarget, F func )
	{
		if ( pTarget != nullptr )
		{
			LoopInorder( pTarget->GetLeft(), func );
			func( pTarget );
			LoopInorder( pTarget->GetRight(), func );
		}
	}

private:
	std::shared_ptr<Element> pRoot;
};