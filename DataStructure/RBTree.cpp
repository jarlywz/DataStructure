#pragma once
#include "RBTree.h"

template<class K, class V>
bool RBTree<K, V>::Insert(const K& key, const V& value)
{
	if (nullptr == _root)
	{
		_root = new RBTreeNode<K, V>(key, value);
		_root->_color = Black;

		return true;
	}

	// 0. 找位置
	RBTreeNode<K, V>* cur = _root;
	RBTreeNode<K, V>* parent = nullptr;
	while (cur)
	{
		if (cur->_key > key)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else
		{
			return false;
		}
	}

	// 1. 插入
	cur = new RBTreeNode<K, V>(key, value);
	cur->_parent = parent;
	if (parent->_key > key)
	{
		parent->_left = cur;
	}
	else if (parent->_key < key)
	{
		parent->_right = cur;
	}

	// 2. 检查颜色分配是否满足要求
	while (parent && parent->_color == Red)
	{
		RBTreeNode<K, V>* grandfather = parent->_parent;
		if (parent == grandfather->_left)
		{
			RBTreeNode<K, V>* uncle = grandfather->_right;
			if (uncle && uncle->_color == Red)
			{
				// 2.1 第一种情况 变色
				grandfather->_color = Red;
				parent->_color = Black;
				uncle->_color = Black;

				cur = grandfather;
				parent = grandfather->_parent;
			}
			else if ((uncle && uncle->_color == Black) || nullptr == uncle)
			{
				// 2.2 叔节点为黑色或不存在			
				if (cur == parent->_left)
				{
					//2.2.1 插入节点为左节点	
					parent->_color = Black;
					grandfather->_color = Red;
					this->RotateR(grandfather);
				}
				else
				{
					//2.2.2 插入节点为右节点
					this->RotateL(parent);
					cur->_color = Black;
					grandfather->_color = Red;
					this->RotateR(grandfather);
				}

				break;
			}
		}
		else
		{
			RBTreeNode<K, V>* uncle = grandfather->_left;
			if (uncle && uncle->_color == Red)
			{
				grandfather->_color = Red;
				parent->_color = Black;
				uncle->_color = Black;

				cur = grandfather;
				parent = cur->_parent;
			}
			else if ((uncle && uncle->_color == Black) || nullptr == uncle)
			{
				if (cur == parent->_right)
				{
					parent->_color = Black;
					grandfather->_color = Red;
					this->RotateL(grandfather);
				}
				else
				{
					this->RotateR(parent);
					parent->_color = Black;
					grandfather->_color = Red;
					this->RotateL(grandfather);
				}

				break;
			}
		}
	}

	this->_root->_color = Black;
	
	return true;
}

template<class K, class V>
void RBTree<K, V>::RotateL(RBTreeNode<K, V>*& x)
{
	//       p                    p
	//       |                    |
	//       x                    y
	//      / \                  / \
	//     a   y                x   c
	//        / \              / \
	//       b   c            a   b
	RBTreeNode<K, V>* ppNode = x->_parent;       // p
	RBTreeNode<K, V>* pyNode = x->_right;        // y
	RBTreeNode<K, V>* pbNode = pyNode->_left;    // b

	// 0. x.right = y.left
	x->_right = pbNode;
	if (pbNode)pbNode->_parent = x;

	// 1. y.left = x
	pyNode->_left = x;
	x->_parent = pyNode;

	// 2. p.child = x  ----> p.child = y
	if (ppNode)
	{
		// 2.0 x is ppNode's left child or right child
		RBTreeNode<K, V>* tmpNode = (x == ppNode->_left ? ppNode->_left : ppNode->_right);
		tmpNode = pyNode;
		pyNode->_parent = tmpNode;
	}
	else
	{
		// 2.1 ppNode is null
		pyNode->_parent = nullptr;
		this->_root = pyNode;
	}

	x = pyNode;
}

template<class K, class V>
void RBTree<K, V>::RotateR(RBTreeNode<K, V>*& x)
{
	//       p                    p
	//       |                    |
	//       x                    y
	//      / \                  / \
	//     y   a                b   x
	//    / \                      / \  
	//   b   c                    c   a
	
	RBTreeNode<K, V>* pyNode = x->_left;         // y	

	// 0. x.left = y.right
	RBTreeNode<K, V>* pcNode = pyNode->_right;   // c
	x->_left = pcNode;
	if (pcNode)pcNode->_parent = x;

	// 1. y.right = x
	pyNode->_right = x;
	x->_parent = pyNode;

	// 2. p.child = x  ----> p.child = y
	RBTreeNode<K, V>* ppNode = x->_parent;       // p
	if (ppNode)
	{
		// 2.0 x is ppNode's left child or right child
		RBTreeNode<K, V>* tmpNode = (x == ppNode->_left ? ppNode->_left : ppNode->_right);
		tmpNode = pyNode;
		pyNode->_parent = tmpNode;
	}
	else
	{
		// 2.1 ppNode is null
		pyNode->_parent = nullptr;
		this->_root = pyNode;
	}

	x = pyNode;
}