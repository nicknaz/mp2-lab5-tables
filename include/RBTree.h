#pragma once
#include "../include/Logger.h"

template<typename T, typename TValue>
class RBTree {
	template<typename T, typename TValue>
	struct Node
	{
		Node *p1, *p2;
		T key;
		TValue *value;
		bool red;
	};

	Node<T, TValue> *root;
	int nodesCount;
	Logger logger;
private:

public:
	RBTree()
	{
		root = 0;
		nodesCount = 0;
	}

	~RBTree()
	{
	}

	int getNodesCount()
	{
		return nodesCount;
	}
	Node<T, TValue>* NewNode(T key, TValue *value)
	{
		nodesCount++;
		Node<T, TValue> *node = new Node<T, TValue>;
		node->key = key;
		node->value = value;
		node->p1 = nullptr;
		node->p2 = nullptr;
		node->red = true;
		return node;
	}
	void DelNode(Node<T, TValue> *node)
	{
		nodesCount--;
		delete node;
	}

	Node<T, TValue> *Rotate21(Node<T, TValue> *node)
	{
		Node<T, TValue> *p2 = node->p2;
		Node<T, TValue> *p21 = p2->p1;
		p2->p1 = node;
		node->p2 = p21;
		return p2;
	}

	Node<T, TValue> *Rotate12(Node<T, TValue> *node)
	{
		Node<T, TValue> *p1 = node->p1;
		Node<T, TValue> *p12 = p1->p2;
		p1->p2 = node;
		node->p1 = p12;
		return p1;
	}

	void BalanceInsert(Node<T, TValue> **root)
	{
		Node<T, TValue> *p1, *p2, *px1, *px2;
		Node<T, TValue> *node = *root;
		if (node->red) return;
		p1 = node->p1;
		p2 = node->p2;
		if (p1 && p1->red) {
			px2 = p1->p2;             
			if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
			px1 = p1->p1;
			if (px1 && px1->red) {
				node->red = true;
				p1->red = false;
				if (p2 && p2->red) { 
					px1->red = true;
					p2->red = false;
					return;
				}
				*root = Rotate12(node);
				return;
			}
		}
		if (p2 && p2->red) {
			px1 = p2->p1;             
			if (px1 && px1->red) p2 = node->p2 = Rotate12(p2);
			px2 = p2->p2;
			if (px2 && px2->red) {
				node->red = true;
				p2->red = false;
				if (p1 && p1->red) { 
					px2->red = true;
					p1->red = false;
					return;
				}
				*root = Rotate21(node);
				return;
			}
		}
	}

	bool BalanceRemove1(Node<T, TValue> **root)
	{
		Node<T, TValue> *node = *root;
		Node<T, TValue> *p1 = node->p1;
		Node<T, TValue> *p2 = node->p2;
		if (p1 && p1->red) {
			p1->red = false; return false;
		}
		if (p2 && p2->red) {
			node->red = true;
			p2->red = false;
			node = *root = Rotate21(node);
			if (BalanceRemove1(&node->p1)) node->p1->red = false;
			return false;
		}
		unsigned int mask = 0;
		Node<T, TValue> *p21 = p2->p1;
		Node<T, TValue> *p22 = p2->p2;
		if (p21 && p21->red) mask |= 1;
		if (p22 && p22->red) mask |= 2;
		switch (mask)
		{
		case 0: 
			p2->red = true;
			return true;
		case 1:
		case 3: 
			p2->red = true;
			p21->red = false;
			p2 = node->p2 = Rotate12(p2);
			p22 = p2->p2;
		case 2: 
			p2->red = node->red;
			p22->red = node->red = false;
			*root = Rotate21(node);
		}
		return false;
	}

	bool BalanceRemove2(Node<T, TValue> **root)
	{
		Node<T, TValue> *node = *root;
		Node<T, TValue> *p1 = node->p1;
		Node<T, TValue> *p2 = node->p2;
		if (p2 && p2->red) { p2->red = false; return false; }
		if (p1 && p1->red) {
			node->red = true;
			p1->red = false;
			node = *root = Rotate12(node);
			if (BalanceRemove2(&node->p2)) node->p2->red = false;
			return false;
		}
		unsigned int mask = 0;
		Node<T, TValue> *p11 = p1->p1;
		Node<T, TValue> *p12 = p1->p2;
		if (p11 && p11->red) mask |= 1;
		if (p12 && p12->red) mask |= 2;
		switch (mask) {
		case 0:     
			p1->red = true;
			return true;
		case 2:
		case 3:     
			p1->red = true;
			p12->red = false;
			p1 = node->p1 = Rotate21(p1);
			p11 = p1->p1;
		case 1:     
			p1->red = node->red;
			p11->red = node->red = false;
			*root = Rotate12(node);
		}
		return false;
	}

	bool Find(TValue value)
	{
		Node<T, TValue> *node = root;
		while (node) {
			if (node->value == value) return true;
			node = node->value > value ? node->p1 : node->p2;
		}
		return false;
	}

	Node<T, TValue>* GetValue(T key, Node<T, TValue> *root, int &i)
	{
		Node<T, TValue> *node = root;
		//std::cout << "DEBUG: " << node->key << std::endl;

		i++;
		if (node->key == key) return node;
		if (node->p1 != nullptr) {
			Node<T, TValue> *tmp1 = GetValue(key, node->p1, i);
			if (tmp1->key == key) return tmp1;
		}
		if (node->p2 != nullptr) {
			Node<T, TValue> *tmp2 = GetValue(key, node->p2, i);
			return tmp2;
		}

		return node;
	}

	TValue* GetValue(T key)
	{
		Node<T, TValue> *node = root;
		int i = 1;
		//std::cout << "DEBUG: " << node->key << std::endl;
		//if (node->p1 == nullptr)
		//	std::cout << "FAIL\n";
		//std::cout << "DEBUG1: " << node->p1->key << std::endl;
		//std::cout << "DEBUG2: " << node->p2->key << std::endl;
		if (node->key == key) return node->value;
		if (node->p1 != nullptr) {
			Node<T, TValue> *tmp1 = GetValue(key, node->p1, i);
			if (tmp1->key == key) 
			{
				logger.DebugLog("RBTree: Actions for finding a polynomial: " + std::to_string(i));
				return tmp1->value;
			} 
		}
		if (node->p2 != nullptr) {
			Node<T, TValue> *tmp2 = GetValue(key, node->p2, i);
			if (tmp2->key == key) 
			{
				logger.DebugLog("RBTree: Actions for finding a polynomial: " + std::to_string(i));
				return tmp2->value;
			}
		}
		
		std::cout << "Key exist" <<std::endl;
		return nullptr;
	}


	bool Insert(T key, TValue *value, Node<T, TValue> **root)
	{
		Node<T, TValue> *node = *root;
		if (!node) *root = NewNode(key, value);
		else {
			if (key == node->key) 
			{
				//std::cout << "\n\nCHECK_T1!\n\n";
				return true;
			}
			if (Insert(key, value, key < node->key ? &node->p1 : &node->p2))
			{
				//std::cout << "\n\nCHECK_T2!\n\n";
				return true;
			}
			BalanceInsert(root);
		}
		//std::cout << "\n\nCHECK_F!\n\n";
		return false;
	}

	bool GetMin(Node<T, TValue> **root, Node<T, TValue> **res)
	{
		Node<T, TValue> *node = *root;
		if (node->p1) {
			if (GetMin(&node->p1, res)) return BalanceRemove1(root);
		}
		else {
			*root = node->p2;
			*res = node;
			return !node->red;
		}
		return false;
	}

	bool Remove(Node<T, TValue> **root, TValue value)
	{
		Node<T, TValue> *t, *node = *root;
		if (!node) return false;
		if (node->value < value) {
			if (Remove(&node->p2, value)) return BalanceRemove2(root);
		}
		else if (node->value > value) {
			if (Remove(&node->p1, value)) return BalanceRemove1(root);
		}
		else {
			bool res;
			if (!node->p2) {
				*root = node->p1;
				res = !node->red;
			}
			else {
				res = GetMin(&node->p2, root);
				t = *root;
				t->red = node->red;
				t->p1 = node->p1;
				t->p2 = node->p2;
				if (res) res = BalanceRemove2(root);
			}
			DelNode(node);
			return res;
		}
		return 0;
	}

	void Insert(T key, TValue *value)
	{
		Insert(key, value, &root);
		if (root) root->red = false;
		
	}

	void Remove(TValue value)
	{
		Remove(&root, value);
	}




	
};