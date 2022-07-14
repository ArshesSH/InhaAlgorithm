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
			RemoveTarget( pRoot->GetKey() );
		}
	}

	void AddElement( K key, V value = V(0) )
	{
		_Add( key, value, pRoot );
	}

	void _Add(K key, V value, std::shared_ptr<Element>& pParent )
	{
		if ( pParent == nullptr )
		{
			auto node = std::make_shared<Element>( key, value );
			pParent = std::move( node );
			return;
		}
		else if ( pParent->GetKey() > key  )
		{
			_Add( key, value, pParent->GetLeft() );
		}
		else if ( pParent->GetKey() < key )
		{
			_Add( key, value, pParent->GetRight() );
		}
		else if ( pParent->GetKey() == key )
		{
			pParent->SetValue( value );
			return;
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

	//bool Remove( K key, std::shared_ptr<Element>& pParent )
	//{
	//	const auto curKey = pParent->Getkey();

	//	// If we are not done, if p is not nullptr (which would mean the child of a leaf node), and p's key is
	//	// less than current key, recurse the left subtree looking for it.
	//	if ( pParent && key < curKey )
	//	{
	//		return remove( key, pParent->GetLeft() );
	//	}

	//	// ...else if we are not done, again because p is not nullptr (which would mean the child of a leaf node), and p's key is
	//	// greater than current key, recurse the right subtree looking for it.
	//	else if ( pParent && x > curKey )
	//	{
	//		return remove( key, pParent->right );
	//	}

	//	// ...else if p is not null, we compare it to the key.
	//	else if ( pParent && curKey == key )
	//	{
	//		// 1. If p has no left child, we replace it with its right child.
	//		// Note: p->right be nullptr, too, if it is a leaf.
	//		if ( !pParent->GetLeft() )
	//		{

	//			// ...remove node p by replacing it with its right child, effectively splicing
	//			// in the right subtree.
	//			pParent = pParent->right;

	//			// ...else if p has no right child and it does have a left child (since the first if-test failed)...
	//			// Note: p->left be nullptr, too, if it is a leaf, and we handle that here, too.
	//		}
	//		else if ( !pParent->right )
	//		{

	//			// ...remove node p by replacing it with its left child (which may be nullptr), effectively splicing in the
	//			// left subtree.
	//			pParent = pParent->left;

	//			// 2. Else if p is an internal node and has two non-nullptr children, so we swap p with its in-order predecessor
	//		}
	//		else
	//		{

	//			std::shared_ptr<Node> q = pParent->right; // <--- This line not possible with unique_ptr

	//			while ( q->left != nullptr ) // locate in-order successor in leaf node, with min value of p's
	//				q = q->left;        // right subtree.

	//			p->key = q->key; // Set in-order q's key in p's node effectively removing the key.

	//			remove( q->key, p->right ); // ...now delete q->key (which is also the value of p->key) from p's right subtree, recalling
	//									  // q was initially set to p->right, which is the root node of subtree that had the in-order
	//									  // successor key.
	//		}

	//		return true;
	//	}
	//	// Could not find x in p or any of its children
	//	return false;
	//}


	bool RemoveTarget( K key )
	{
		return _Remove( key, pRoot );
	}

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
	void DoAscendingLoop( F func )
	{
		LoopInorder( pRoot, func );
	}

private:
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

	std::shared_ptr<Element> FindGreatestChild( const std::shared_ptr<Element>& pParent)
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
	std::shared_ptr<Element> FindLeastChild( const std::shared_ptr<Element>& pParent )
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
	std::shared_ptr<Element> pRoot;
};