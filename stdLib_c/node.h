#ifndef NODE_H
#define NODE_H

#include <cmath>
#include <queue>
#include <iomanip>
#include <ostream>

template <typename T>
class Node
{
private:
	Node(Node<T> *const);

	Node(T const *value, signed int (*cmp)(T const *, T const *), Node *const p)
		: _value(value), _cmp(cmp), parent(p)
	{
		left = NULL;
		right = NULL;
		upToDate = false;
		parent = NULL;
	}

	T const *const _value;

	signed int (*const _cmp)(T const *, T const *);

	Node<T> *left;
	Node<T> *right;
	Node<T> *parent;

	bool upToDate;

	unsigned int _height, _size;

	void invalidate()
	{
		if (upToDate)
		{
			upToDate = false;
			if (parent)
				parent->invalidate();
		}
	}

	inline Node *rotateRight()
	{
		Node *newRoot = right;
		right = newRoot->left;
		newRoot->parent = parent;
		parent = newRoot;
		newRoot->left = this;
		newRoot->invalidate();
		invalidate();
		return newRoot;
	}

	inline Node *rotateLeft()
	{
		Node *newRoot = left;
		left = newRoot->right;
		newRoot->parent = parent;
		parent = newRoot;
		newRoot->right = this;
		newRoot->invalidate();
		invalidate();
		return newRoot;
	}

	void update()
	{
		_size = 0;
		_height = 0;
		if (!left && !right)
		{
			upToDate = true;
			_size = 1;
			return;
		}
		else
		{
			if (left)
			{
				_height = left->height();
				_size += left->_size;
			}
			if (right)
			{
				unsigned int heightR = right->height();
				if (heightR > _height)
					_height = heightR;
				_size += right->_size;
			}
		}
		++_height;
		++_size;
		upToDate = true;
	}

public:

	~Node()
	{
	}

	unsigned int height()
	{
		if (upToDate)
			return _height;
		update();
		return _height;
	}
	
	unsigned int size()
	{
		if (upToDate)
			return _size;
		update();
		return _size;
	}

	bool add(T const *value)
	{
		Node *node = this;
		while (true)
		{
			signed int const cmp = _cmp(node->_value, value);
			if (cmp == 0)
				return false;
			else if (cmp < 0)
			{
				if (!node->right)
				{
					node->right = new Node(value, _cmp, node);
					node->right->parent = node;
					node->invalidate();
					return true;
				}
				else
					node = node->right;
			}
			else
			{
				if (!node->left)
				{	
					node->left = new Node(value, _cmp, node);
					node->left->parent = node;
					node->invalidate();
					return true;
				}
				else
					node = node->left;
			}
		}
	}

	Node *balance()
	{
		signed int balance = 0;
		if (right)
		{
			right = right->balance();
			if (right->parent != this)
			{
				right->parent = this;
			}
			balance -= right->height() + 1;
		}
		if (left) 
		{
			left = left->balance();
			if (left->parent != this)
			{
				left->parent = this;
			}
			balance += left->height() + 1;
		}
		if (balance <= -2)
		{
			if (right->left)
				if (!right->right) 
				{
					right = right->rotateLeft();
					// assert right->parent == this;
				}
				else if (right->right->height() < right->left->height())
				{
					right = right->rotateLeft();
					// assert right->parent == this;
				}
			return rotateRight();
		}
		else if (balance >= 2)
		{
			if (left->right)
				if (!left->left) 
				{
					left = left->rotateRight();
					// assert left->parent == this;
				}
				else if (left->left->height() < left->right->height())
				{
					left = left->rotateRight();
					// assert left->parent == this;
				}
			return rotateRight();
		}
		return this;
	}

	static
	Node<T> *create(T *const value, signed int (*cmp)(T const *, T const *))
	{
		return new Node(value, cmp, NULL);
	}

	void free() {
		if (parent) {
			parent->free();
			parent = NULL;
		} 
		else
		{
			if (left)
			{
				left->parent = NULL;
				left->free();
				left = NULL;
			}
			if (right)
			{
				right->parent = NULL;
				right->free();
				right = NULL;
			}
			delete(this);
		}
	}
	
	template<class T>
	friend std::ostream& operator<<(std::ostream &out, Node<T> &node)
	{
		if (node.parent)
			return out << node.parent;
		else
		{
			std::queue<Node<T> *> worklist;
			unsigned nBreak = 2;
			unsigned nBreakNext = 0;
			int h = node.height();
			int widthCorrection = 1 + ((h-1) << 1);
			worklist.push(&node);
			while (!worklist.empty())
			{
				Node<T> *next = worklist.front();
				worklist.pop();

				if (!--nBreak) {
					out << "\n";
					nBreak = nBreakNext;
					nBreakNext = 0;
					widthCorrection = (h-- << 1 / (worklist.size() + 1));
				}
				for (int i = 0; i < (1 << h) + widthCorrection; ++i)
					out << "  ";
				if (next->left)
				{
					worklist.push(next->left);
					++nBreakNext;
				}
				if (next->right)
				{
					worklist.push(next->right);
					++nBreakNext;
				}

				out << *(next->_value);
			}
			if (--nBreak)
				return out;
			return out << std::endl;
		}
	}
};



#endif
