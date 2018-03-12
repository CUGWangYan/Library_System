#pragma once
#include <iostream>  
#include <string>
using namespace std;
static const int m = 2;  
static const int key_max = 2 * m - 1;
static const int key_min = m - 1;
static const int child_max = key_max + 1;
static const int child_min = key_min + 1;
template<class T>
class BTree;
template <class T>
class BTnode
{
	friend class BTree<T>; 
public:
	BTnode()
		{
			keyNum = 0;
			parent = nullptr;
			isleaf = true;
			int i;
			for (i = 0; i < child_max; i++) 
			{
				pchild[i] = nullptr;
			}
			for (i = 0; i < key_max; i++) 
			{
				string a ="" ;
				keyvalue[i] = a;
			}
			for (i = 0; i < key_max; i++) {
				index[i] = -1;
			}
		}
private:
	bool isleaf;
	int keyNum; 
	BTnode<T>* parent;  
	BTnode<T>* pchild[child_max];
	T   keyvalue[key_max];
	int index[key_max];
};
template <class T>
class BTree{
private:
	void SplitBlock(BTnode<T>* node_parent, int child_index, BTnode<T>* node_child)
		{
			BTnode<T>* node_right = new BTnode<T>();
			node_right->isleaf = node_child->isleaf;
			node_right->keyNum = key_min;
			int i;
			for (i = 0; i < key_min; i++)
			{
				node_right->keyvalue[i] = node_child->keyvalue[i + child_min];
				node_right->index[i] = node_child->index[i + child_min];
			}
			if (!node_child->isleaf)
			{
				for (i = 0; i < child_min; i++)
				{
					node_right->pchild[i] = node_child->pchild[i + child_min];
					node_child->pchild[i + child_min]->parent = node_right->pchild[i];
				}
			}
			node_child->keyNum = key_min;
			for (i = node_parent->keyNum; i > child_index; i--)
			{
				node_parent->keyvalue[i] = node_parent->keyvalue[i - 1];
				node_parent->index[i] = node_parent->index[i - 1];
				node_parent->pchild[i+1] = node_parent->pchild[i];
				if(node_child->pchild[i] != nullptr)
				node_child->pchild[i]->parent = node_parent->pchild[i];
			}
			node_parent->keyNum++;
			node_parent->pchild[child_index + 1] = node_right;
			node_right->parent = node_parent->pchild[child_index + 1];  
			node_parent->keyvalue[child_index] = node_child->keyvalue[key_min];
			node_parent->index[child_index] = node_child->index[key_min];
		}
	void Notfull_insert(BTnode<T>* node, T value,int n)
		{
			int node_keynum = node->keyNum;
			if (node->isleaf)
			{
				while (node_keynum > 0 && value < node->keyvalue[node_keynum - 1])
				{
					node->keyvalue[node_keynum] = node->keyvalue[node_keynum - 1];
					node->index[node_keynum] = node->index[node_keynum - 1];
					--node_keynum;
				}
				node->keyvalue[node_keynum] = value;
				node->index[node_keynum] = n;
				node->keyNum++;
			}
			else 
			{
				while (node_keynum > 0 && value < node->keyvalue[node_keynum - 1])
				{
					--node_keynum;
				}
				BTnode<T>* node_child = node->pchild[node_keynum];
				if (node_child->keyNum == key_max)
				{
					SplitBlock(node, node_keynum, node_child);
					if (value > node->keyvalue[node_keynum]) 
					{
						node_child = node->pchild[node_keynum + 1];
					}
				}
				Notfull_insert(node_child, value,n);  
			}
		}
	void MergeBlock(BTnode<T>* node_parent, int child_index)
		{
			BTnode<T>* node_child1 = node_parent->pchild[child_index];
			BTnode<T>* node_child2 = node_parent->pchild[child_index + 1];
			node_child1->keyvalue[key_min] = node_parent->keyvalue[child_index];
			node_child1->index[key_min] = node_parent->index[child_index];
			node_child1->keyNum = key_max;
			int i;
			for (i = 0; i < key_min; i++)
			{
				node_child1->keyvalue[child_min + i] = node_child2->keyvalue[i];
				node_child1->index[child_min + i] = node_child2->index[i];
			} 
			if (!node_child1->isleaf)
			{
				for (i = 0; i < child_min; i++)
				{
					node_child1->pchild[i + child_min] = node_child2->pchild[i];
				}
			}
			node_parent->keyNum--;
			for (i = child_index; i < node_parent->keyNum; i++)
			{
				node_parent->keyvalue[i] = node_parent->keyvalue[i + 1];
				node_parent->index[i] = node_parent->index[i + 1]; 
				node_parent->pchild[i + 1] = node_parent->pchild[i + 2];
			}
			delete node_child2;
			node_child2 = nullptr;
		}
	T getprev(BTnode<T>* node,int& n)
		{
			while (!node->isleaf)
			{
				node = node->pchild[node->keyNum];
			}
			node->keyNum--;
			n = node->index[node->keyNum - 1];
			return node->keyvalue[node->keyNum - 1];
		}
	T getnext(BTnode<T>* node,int&n)
		{
			while (!node->isleaf)
			{
				node = node->pchild[0];
			}
			n = node->index[0];
			return node->keyvalue[0];
		}
	BTnode<T>* BTree_find(BTnode<T>* node, T value,int&n)
	{
		if (node == nullptr) 
		{
			return nullptr;
		}
		else
		{
			int i;
			for (i = 0; i < node->keyNum; i++)
			{
				if (value <= node->keyvalue[i])
				{
					break;
				}
			}
			if (i < node->keyNum && value == node->keyvalue[i])
			{
				n = node->index[i];
				return node;
			}
			else
			{
				if (node->isleaf)
				{
					return nullptr;
				}
				else 
				{
					return BTree_find(node->pchild[i], value,n);  
				}
			}
		}
	}
	void printpoint(BTnode<T>* node, int count)
	{
		if (node != nullptr) 
		{
			int i, j;
			for (i = 0; i < node->keyNum; i++)
			{
				if (!node->isleaf)
				{
					printpoint(node->pchild[i], count - 3);
				}
				for (j = count; j >= 0; j--)
				{
					cout << "-";
				}
				cout << "|" << node->keyvalue[i] <<"and index"<<node->index[i]<< "|" << endl;
			}
			if (!node->isleaf)
			{
				printpoint(node->pchild[i], count - 3);
			}
		}
	}
	void BTree_deletebalance(BTnode<T>* node, T value)
	{
		int i;
		for (i = 0; i < node->keyNum && value > node->keyvalue[i]; i++)
		{

		}
		if (i < node->keyNum && value == node->keyvalue[i])
		{
			if (node->isleaf)
			{
				node->keyNum--;
				for (; i < node->keyNum; i++)
				{
					node->keyvalue[i] = node->keyvalue[i + 1];
					node->index[i] = node->index[i + 1];
				}
				return;
			}
			else
			{
				BTnode<T>* node_left = node->pchild[i];
				BTnode<T>* node_right = node->pchild[i + 1];
				if (node_left->keyNum >= child_min)
				{
					int n = -1;
					T prev_replace = getprev(node_left,n);
					BTree_deletebalance(node_left, prev_replace); 
					node->keyvalue[i] = prev_replace;
					node->index[i] = n;
					return;
				}
				else if (node_right->keyNum >= child_min)
				{
					int n = -1;
					T next_replace = getnext(node_right,n); 
					BTree_deletebalance(node_right, next_replace); 
					node->keyvalue[i] = next_replace;
					node->index[i] = n;
					return;
				}
				else
				{ 
					MergeBlock(node, i);
					BTree_deletebalance(node_left, value);
				}
			}
		}
		else  
		{
			BTnode<T>* node_child = node->pchild[i]; 
			BTnode<T>*  node_left = nullptr;
			BTnode<T>*  node_right = nullptr;
			if (node_child->keyNum == key_min)
			{
				if (i >0)
				{
					node_left = node->pchild[i - 1];
				}
				if (i <= node->keyNum - 1)
				{
					node_right = node->pchild[i + 1];
				}
				int j;
				if (node_left && node_left->keyNum >= child_min)
				{ 
					for (j = node_child->keyNum; j > 0; j--)
					{
						node_child->keyvalue[j] = node_child->keyvalue[j - 1];
						node_child->index[j] = node_child->index[j - 1];
					}
					node_child->keyvalue[0] = node->keyvalue[i - 1];
					node_child->index[0] = node->index[i - 1];
					if (!node_left->isleaf)
					{ 
						for (j = node_child->keyNum + 1; j > 0; j--)
						{
							node_child->pchild[j - 1]->parent = node_child->pchild[j]->parent;
							node_child->pchild[j] = node_child->pchild[j - 1];

						}
						node_left->pchild[node_left->keyNum]->parent = node_child->pchild[0];
						node_child->pchild[0] = node_left->pchild[node_left->keyNum];
					}
					node_child->keyNum++;
					node->keyvalue[i - 1] = node_left->keyvalue[node_left->keyNum - 1];
					node->index[i - 1] = node_left->index[node_left->keyNum - 1];
					node_left->keyNum--;
				}
				else if (node_right && node_right->keyNum >= child_min)
				{
					node_child->keyvalue[node_child->keyNum] = node->keyvalue[i];
					node_child->index[node_child->keyNum] = node->index[i];
					node_child->keyNum++; 
					node->keyvalue[i] = node_right->keyvalue[0];
					node->index[i] = node_right->index[0];
					node_right->keyNum--;
					for (j = 0; j < node_right->keyNum; j++)
					{
						node_right->keyvalue[j] = node_right->keyvalue[j + 1];
						node_right->index[j] = node_right->index[j + 1];
					} 
					if (!node_right->isleaf)
					{
						node_right->pchild[0]->parent = node_child->pchild[node_child->keyNum]->parent;
						node_child->pchild[node_child->keyNum] = node_right->pchild[0];
						for (j = 0; j < node_right->keyNum + 1; j++)
						{
							node_right->pchild[j + 1]->parent = node_right->pchild[j]->parent;
							node_right->pchild[j] = node_right->pchild[j + 1];

						}

					}
				}
				else if (node_left) 
				{
					MergeBlock(node, i - 1); 
					node_child = node_left;
				}
				else if (node_right)
				{
					MergeBlock(node, i);
				}
			}
			BTree_deletebalance(node_child, value);
		}
	}
public:
	int contain(T value)
		{
		int n = -1;
			if (BTree_find(root, value,n) != nullptr)
				return n;
			return -1;
		}

	void printpoint()
		{
			printpoint(root, key_max * 5);
		}
	bool BTree_delete(T value)
		{
			if (contain(value)==-1)
			{
				return false;
			}
			if (root->keyNum == 1)
			{
				if (root->isleaf)
				{
					delete root;
					root = nullptr;
					return true;
				}
				else 
				{
					BTnode<T>* node_child1 = root->pchild[0];
					BTnode<T>* node_child2 = root->pchild[1]; 
					if (node_child1->keyNum == key_min && node_child2->keyNum == key_min)
					{
						MergeBlock(root, 0);
						delete root;
						root = node_child1;
					}
				}
			}
			BTree_deletebalance(root, value);
			return true;
		}
	BTree(){root = nullptr;}
	bool BTree_insert(T value,int n)
			{
				if (contain(value)!=-1)  
				{
					return false;
				}
				else
				{
					if (root == nullptr)
					{
						root = new BTnode<T>();
					}
					if (root->keyNum == key_max)
					{
						BTnode<T>* newnode = new BTnode<T>();
						newnode->pchild[0] = root;
						newnode->isleaf = false; 
						SplitBlock(newnode, 0, root); 
						root = newnode;  
					}
					Notfull_insert(root, value,n);  
					return true;
				}
			}
private:
	BTnode<T>* root; 
};