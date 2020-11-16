#pragma once
enum  Color
{
	Red,
	Black,
};

template<class K, class V>
struct RBTreeNode
{
	K _key;
	V _value;
	Color _color;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const K& key = K(), const V& value = V())
		:_key(key)
		, _value(value)
		, _color(Red)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{

	}
};

template<class K, class V>
class RBTree
{
public:
	RBTree()
		:_root(nullptr)
	{

	}

	// ����
	bool Insert(const K& key, const V& value);

	// ���������ĺϷ���
	bool Check();
protected:
	// ����
	void RotateL(RBTreeNode<K, V>*& X);
	// ����
	void RotateR(RBTreeNode<K, V>*& X);
	// ���������ĺϷ���

protected:
	RBTreeNode<K, V>* _root;
};

